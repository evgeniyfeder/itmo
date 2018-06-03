package ru.ifmo.rain.feder.mapper;

import info.kgeorgiy.java.advanced.mapper.ParallelMapper;

import java.util.*;
import java.util.function.Function;

public class ParallelMapperImpl implements ParallelMapper {
    private List<Thread> threads;
    private final Queue<Task> waitingThreads;


    private class Counter {
        private int cnt;
        private int needSize;

        Counter(int needSize) {
            this.needSize = needSize;
        }

        void increment() {
            cnt++;
        }

        boolean check() {
            return cnt >= needSize;
        }
    }

    private class Task {
        Runnable task;
        final Counter counter;

        Task(Runnable task, Counter counter) {
            this.task = task;
            this.counter = counter;
        }
    }

    private void doTask() throws InterruptedException {
        Task task;
        synchronized (waitingThreads) {
            while (waitingThreads.isEmpty()) {
                waitingThreads.wait();
            }

            task = waitingThreads.poll();
        }


        task.task.run();

        synchronized (task.counter) {
            task.counter.increment();
            if (task.counter.check()) {
                task.counter.notify();
            }
        }
    }

    public ParallelMapperImpl(int numThreads) {
        threads = new ArrayList<>();
        waitingThreads = new LinkedList<>();

        for (int i = 0; i < numThreads; i++) {
            threads.add(new Thread(() -> {
                try {
                    while (!Thread.interrupted()) {
                        doTask();
                    }
                } catch (InterruptedException ignored) {} finally {
                    Thread.currentThread().interrupt();
                }
            }));
            threads.get(i).start();
        }
    }

    @Override
    public <T, R> List<R> map(Function<? super T, ? extends R> function, List<? extends T> list) throws InterruptedException {
        final Counter cnt = new Counter(list.size());
        List<R> resultList = new ArrayList<>(Collections.nCopies(list.size(), null));

        for (int i = 0; i < list.size(); i++) {
            final int finalCurElemInd = i;
            synchronized (waitingThreads) {
                waitingThreads.add(new Task(() -> resultList.set(finalCurElemInd, function.apply(list.get(finalCurElemInd))), cnt));
                waitingThreads.notify();
            }
        }

        synchronized (cnt) {
            while (!cnt.check()) {
                cnt.wait();
            }
        }

        return resultList;
    }

    @Override
    public void close() {
        threads.forEach(Thread::interrupt);

        for (Thread thread : threads) {
            try {
                thread.join();
            } catch (InterruptedException ignored) {
            }
        }
    }
}
