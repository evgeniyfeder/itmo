package ru.ifmo.rain.feder.hello;

import info.kgeorgiy.java.advanced.hello.HelloServer;
import info.kgeorgiy.java.advanced.hello.Util;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.PortUnreachableException;
import java.net.SocketException;
import java.util.Objects;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.RejectedExecutionException;
import java.util.concurrent.TimeUnit;

public class HelloUDPServer implements HelloServer {
    private ExecutorService workers;
    private ExecutorService receiver;
    private DatagramSocket socket;

    private final static int WAIT_TIME = 10;

    static public void main(String[] args) {
        int port, threadsNum;
        try {
            port = Integer.parseInt(Objects.requireNonNull(args[0]));
            threadsNum = Integer.parseInt(Objects.requireNonNull(args[1]));
        } catch (Exception e) {
            System.out.println("ERROR: Аrguments expected: <port> <threadsNum>");
            return;
        }

        new HelloUDPServer().start(port, threadsNum);
    }

    @Override
    public void start(int port, int threadsNum) {
        try {
            workers = Executors.newFixedThreadPool(threadsNum);
            socket = new DatagramSocket(port);
            receiver = Executors.newSingleThreadExecutor();

            receiver.submit(() -> {
                try {
                    byte[] data = new byte[socket.getReceiveBufferSize()];
                    DatagramPacket input = new DatagramPacket(data, socket.getReceiveBufferSize());

                    while (!Thread.interrupted()) {

                        socket.receive(input);
                        workers.submit(() -> receive(input));
                    }
                } catch (RejectedExecutionException e) {
                    System.out.println("ERROR: the task cannot be scheduled for execution." + e);
                } catch (PortUnreachableException e) {
                    System.out.println("ERROR: the socket is connected to a currently unreachable destination. " + e);
                } catch (SocketException e) {
                    System.out.println("ERROR: Error with socket." + e);
                } catch (IOException e) {
                    System.out.println("ERROR: I/O error with socket." + e);
                }

            });
        } catch (SocketException e) {
            System.out.println("ERROR: the socket could not be opened," +
                    "or the socket could not bind to the specified local port." + e);
        }
    }

    private void receive(DatagramPacket input) {
        try {
            String result = new String(("Hello, " + input).getBytes(Util.CHARSET), 0, input.getLength(), Util.CHARSET);
            socket.send(new DatagramPacket(result.getBytes(Util.CHARSET), result.length(), input.getSocketAddress()));
        } catch (PortUnreachableException e) {
            System.out.println("ERROR: the socket is connected to a currently unreachable destination. " + e);
        } catch (SocketException e) {
            System.out.println("ERROR: Error with socket." + e);
        } catch (IOException e) {
            System.out.println("ERROR: I/O error with socket." + e);
        }
    }

    @Override
    public void close() {
        receiver.shutdownNow();
        workers.shutdownNow();
        socket.close();

        try {
            workers.awaitTermination(WAIT_TIME, TimeUnit.SECONDS);
        } catch (InterruptedException ignored) {
        }
    }
}
