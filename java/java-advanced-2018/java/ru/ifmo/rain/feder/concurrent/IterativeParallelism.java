package ru.ifmo.rain.feder.concurrent;

import info.kgeorgiy.java.advanced.concurrent.ListIP;

import java.util.*;
import java.util.function.Function;
import java.util.function.Predicate;
import java.util.stream.Collectors;
import java.util.stream.Stream;

import info.kgeorgiy.java.advanced.mapper.ParallelMapper;
import ru.ifmo.rain.feder.mapper.ParallelMapperImpl;

public class IterativeParallelism implements ListIP {
    private ParallelMapper mapper;

    public IterativeParallelism() {
        mapper = null;
    }

    public IterativeParallelism(ParallelMapper mapper) {
        this.mapper = mapper;
    }

    private <T, R> R countFunc(int threadsNum, List<? extends T> list,
                               Function<Stream<? extends T>, ? extends R> map,
                               Function<Stream<? extends R>, ? extends R> reduce) throws InterruptedException {
        threadsNum = Math.min(threadsNum, list.size());

        final List<Thread> threads = new ArrayList<>(threadsNum);
        final List<R> results;

        final int blockSize = list.size() / threadsNum;
        final int extra = list.size() % threadsNum;

        int windowLeft = 0;
        List<Stream<? extends T>> listParts = new ArrayList<>();
        for (int j = 0; j < threadsNum; j++) {
            final int left = windowLeft;
            final int right = left + blockSize + (j < extra ? 1 : 0);

            listParts.add(list.subList(left, right).stream());

            windowLeft = right;
        }

        if (mapper != null) {
            results = mapper.map(map, listParts);
        } else {
            results = new ArrayList<>(Collections.nCopies(threadsNum, null));

            for (int j = 0; j < threadsNum; j++) {
                final int pos = j;
                threads.add(new Thread(() -> results.set(pos, map.apply(
                        listParts.get(pos)))));

                threads.get(j).start();
            }

            InterruptedException exception = null;
            for (int j = 0; j < threadsNum; j++) {
                try {
                    threads.get(j).join();
                } catch (InterruptedException e) {
                    if (exception == null) {
                        exception = e;
                    } else {
                        exception.addSuppressed(e);
                    }
                }
            }

            if (exception != null) {
                throw exception;
            }
        }
        return reduce.apply(results.stream());
    }

    @Override
    public String join(int i, List<?> list) throws InterruptedException {
        return countFunc(i, list,
                x -> x.map(Object::toString).collect(Collectors.joining()),
                x -> x.collect(Collectors.joining()));
    }

    @Override
    public <T> List<T> filter(int i, List<? extends T> list, Predicate<? super T> predicate) throws InterruptedException {
        return countFunc(i, list,
                (x) -> x.filter(predicate).collect(Collectors.toList()),
                (x) -> x.flatMap(List::stream).collect(Collectors.toList()));
    }

    @Override
    public <T, U> List<U> map(int i, List<? extends T> list, Function<? super T, ? extends U> function) throws InterruptedException {
        return countFunc(i, list,
                (x) -> x.map(function).collect(Collectors.toList()),
                (x) -> x.flatMap(List::stream).collect(Collectors.toList()));
    }

    @Override
    public <T> T maximum(int i, List<? extends T> list, Comparator<? super T> comparator) throws InterruptedException {
        final Function<Stream<? extends T>, ? extends T> countMax = x -> x.max(comparator).orElse(null);
        return countFunc(i, list, countMax, countMax);
    }

    @Override
    public <T> T minimum(int i, List<? extends T> list, Comparator<? super T> comparator) throws InterruptedException {
        final Function<Stream<? extends T>, ? extends T> countMin = x -> x.min(comparator).orElse(null);
        return countFunc(i, list, countMin, countMin);
    }

    @Override
    public <T> boolean all(int i, List<? extends T> list, Predicate<? super T> predicate) throws InterruptedException {
        return countFunc(i, list, (x) -> x.allMatch(predicate), (x) -> x.allMatch((y) -> y));
    }

    @Override
    public <T> boolean any(int i, List<? extends T> list, Predicate<? super T> predicate) throws InterruptedException {
        return countFunc(i, list, (x) -> x.anyMatch(predicate), (x) -> x.anyMatch((y) -> y));
    }
}
