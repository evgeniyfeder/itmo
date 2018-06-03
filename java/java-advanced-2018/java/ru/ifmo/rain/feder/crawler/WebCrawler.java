package ru.ifmo.rain.feder.crawler;

import info.kgeorgiy.java.advanced.crawler.*;

import java.io.IOException;
import java.net.MalformedURLException;
import java.util.*;
import java.util.concurrent.*;

public class WebCrawler implements Crawler {
    private final int perHostLimit;
    private final ExecutorService downloadersPoll; /* Get pages */
    private final ExecutorService extractorsPoll; /* Parse page */
    private final Downloader downloader;

    private class HostData {
        int load;
        Queue<Runnable> tasks = new ArrayDeque<>();
    }
    private final Map<String, HostData> hostDataMap;

    public WebCrawler(Downloader downloader, int downloaders, int extractors, int perHost) {
        this.perHostLimit = perHost;
        this.downloader = downloader;
        this.downloadersPoll = Executors.newFixedThreadPool(downloaders);
        this.extractorsPoll = Executors.newFixedThreadPool(extractors);

        hostDataMap = new ConcurrentHashMap<>();
    }

    private Optional<String> getHost(String url, Map<String, IOException> exceptions) {
        Optional<String> ret = Optional.empty();
        try {
            ret = Optional.of(URLUtils.getHost(url));
        } catch (MalformedURLException e) {
            exceptions.put(url, e);
        }
        return ret;
    }

    private void downloadRec(String url, int stepsLeft, Phaser phaser,
                             final Set<String> result, final Map<String, IOException> exceptions) {
        if (result.contains(url)) { return; }
        result.add(url);

        getHost(url, exceptions).ifPresent(hostName -> {
            Runnable downloaderTask = () -> {
                try {
                    Document downloaded = downloader.download(url);

                    Runnable extractorsTask = () -> {
                        try {
                            if (stepsLeft != 1) {
                                for (String link : downloaded.extractLinks()) {
                                    downloadRec(link, stepsLeft - 1, phaser, result, exceptions);
                                }
                            }
                        } catch (IOException e) {
                            exceptions.put(url, e);
                        } finally {
                            phaser.arrive();
                        }
                    };

                    phaser.register();
                    extractorsPoll.submit(extractorsTask);
                } catch (IOException e) {
                    exceptions.put(url, e);
                }

                /* We have this host */
                hostDataMap.computeIfPresent(hostName, ((s, hostInfo) -> {
                    if (!hostInfo.tasks.isEmpty()) {
                        downloadersPoll.submit(hostInfo.tasks.poll());
                    } else {
                        hostInfo.load = hostInfo.load - 1;
                    }
                    return hostInfo;
                }));
                phaser.arrive();
            };

            phaser.register();

            hostDataMap.compute(hostName, ((s, hostInfo) -> {
                if (hostInfo == null) {
                    hostInfo = new HostData();
                }
                if (hostInfo.load >= perHostLimit) {
                    hostInfo.tasks.add(downloaderTask);
                } else {
                    hostInfo.load = hostInfo.load + 1;
                    downloadersPoll.submit(downloaderTask);
                }
                return hostInfo;
            }));
        });
    }

    @Override
    public Result download(String url, int depth) {
        Set<String> result = new ConcurrentSkipListSet<>();
        Map<String, IOException> exceptions = new ConcurrentHashMap<>();

        Phaser phaser = new Phaser(1);
        downloadRec(url, depth, phaser, result, exceptions);
        phaser.arriveAndAwaitAdvance();

        result.removeAll(exceptions.keySet());
        return new Result(new ArrayList<>(result), exceptions);
    }

    @Override
    public void close() {
        extractorsPoll.shutdownNow();
        downloadersPoll.shutdownNow();
    }


    private static int getArg(String[] args, int index, int noExist) {
        return args.length > index ? Integer.parseInt(args[index]) : noExist;
    }

    public static void main(String[] args) {
        try {
            if (args.length <= 2) {
                System.out.println("Two parametres expected");
                return;
            }

            int downloads = getArg(args, 1, 8);
            int extractors = getArg(args, 2, 8);
            int perHost = getArg(args, 3, 4);
            int depth = getArg(args, 4, 2);

            Downloader downloader = new CachingDownloader();
            WebCrawler webCrawler = new WebCrawler(downloader, downloads, extractors, perHost);
            Result result = webCrawler.download(args[0], depth);
            System.out.println("Downloaded size: " + result.getDownloaded().size() + ", errors size: " + result.getErrors().size());
        } catch (IOException e) {
            System.out.println(e.getMessage());
        }
    }


}