package ru.ifmo.rain.feder.hello;

import info.kgeorgiy.java.advanced.hello.HelloClient;
import info.kgeorgiy.java.advanced.hello.Util;

import java.io.IOException;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.ArrayList;
import java.util.List;
import java.util.Objects;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.TimeUnit;
import java.util.regex.Pattern;

public class HelloUDPClient implements HelloClient {
    private static int TIMEOUT = 1000; // milliseconds

    public static void main(String[] args) {
        String host, prefix;
        int port, threadsNum, requestsNum;

        try {
            host = args[0];
            port = Integer.parseInt(Objects.requireNonNull(args[1]));
            prefix = args[2];
            threadsNum = Integer.parseInt(Objects.requireNonNull(args[3]));
            requestsNum = Integer.parseInt(Objects.requireNonNull(args[4]));
        } catch (Exception e) {
            System.out.println("ERROR: Arguments expected: <host> <port> <prefix> <threadsNum> <requestsNum>");
            return;
        }
        new HelloUDPClient().run(host, port, prefix, threadsNum, requestsNum);
    }

    @Override
    public void run(String host, int port, String prefix, int threadsNum, int requestsNum) {
        InetSocketAddress socketAddress = new InetSocketAddress(host, port);

        ExecutorService workers = Executors.newFixedThreadPool(threadsNum);
        for (int i = 0; i < threadsNum; ++i) {
            final int threadId = i;

            workers.submit(new Thread(() -> {
                try (DatagramSocket socket = new DatagramSocket()) {

                    byte[] dataResponse = new byte[socket.getReceiveBufferSize()];
                    DatagramPacket response = new DatagramPacket(dataResponse, socket.getReceiveBufferSize());

                    for (int requestId = 0; requestId < requestsNum; ++requestId) {
                        String request = String.format("%s%d_%d", prefix, threadId, requestId);
                        byte[] dataRequest = request.getBytes(StandardCharsets.UTF_8);
                        DatagramPacket packet = new DatagramPacket(dataRequest, request.length(), socketAddress);

                        socket.setSoTimeout(TIMEOUT);
                        while (true) {
                            try {
                                socket.send(packet);
                                socket.receive(response);

                                String answerString = new String(response.getData(), response.getOffset(), response.getLength(), StandardCharsets.UTF_8);
                                if (answerString.matches(".*" + Pattern.quote(request) + "(|\\p{Space}.*)")) {
                                    System.out.println("Answer is : " + answerString);
                                    break;
                                }
                            } catch (SocketTimeoutException e) {
                                System.out.println("ERROR: timeout has expired(Timeout is " + TIMEOUT + " milliseconds). " + e);
                            } catch (PortUnreachableException e) {
                                System.out.println("ERROR: the socket is connected to a currently unreachable destination. " + e);
                            } catch (IOException e) {
                                System.out.println("ERROR: I/O error while send. " + e);
                            }
                        }
                    }
                } catch (SocketException e) {
                    System.out.println("ERROR: Socket could not be opened, or the socket could not bind to the specified local port. " + e);
                }
            }));
        }
        workers.shutdown();

        try {
            workers.awaitTermination(threadsNum * requestsNum, TimeUnit.MINUTES);
        } catch (InterruptedException ignored) {
        }
    }
}
