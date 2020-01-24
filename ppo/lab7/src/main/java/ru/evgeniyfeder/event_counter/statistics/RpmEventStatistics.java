package main.java.ru.evgeniyfeder.event_counter.statistics;

import javafx.util.Pair;
import main.java.ru.evgeniyfeder.event_counter.clock.Clock;

import java.time.Instant;
import java.time.temporal.ChronoUnit;
import java.util.HashMap;
import java.util.LinkedList;
import java.util.Map;
import java.util.Queue;

public class RpmEventStatistics implements EventStatistics {
    private Clock clock;

    private Map<String, Integer> freqCounter = new HashMap<>();
    private Queue<Pair<String, Instant>> eventQueue = new LinkedList<>();

    private static long MINUTES_IN_HOUR = ChronoUnit.HOURS.getDuration().toMinutes();

    public RpmEventStatistics(Clock clock) {
        this.clock = clock;
    }

    private boolean canBeRemoved(Instant nowTime)
    {
        if (eventQueue.isEmpty())
            return false;
        return ChronoUnit.HOURS.between(eventQueue.element().getValue(), nowTime) >= 1;
    }

    private void RemoveOldElements(Instant nowTime)
    {
        while (canBeRemoved(nowTime))
        {
            String removingEvent = eventQueue.poll().getKey();

            int freq = freqCounter.get(removingEvent);
            if (freq > 1) {
                freqCounter.put(removingEvent, freq - 1);
            } else {
                freqCounter.remove(removingEvent);
            }
        }
    }

    @Override
    public void incEvent(String name) {
        Instant now = clock.now();

        RemoveOldElements(now);

        eventQueue.add(new Pair<String, Instant>(name, now));

        int curFreq = freqCounter.getOrDefault(name, 0);
        freqCounter.put(name, curFreq + 1);
    }

    @Override
    public Double getEventStatisticByName(String name) {
        Instant now = clock.now();

        RemoveOldElements(now);
        return (double)freqCounter.getOrDefault(name, 0) / MINUTES_IN_HOUR;
    }

    @Override
    public Map<String, Double> getAllEventStatistic() {
        Instant now = clock.now();
        RemoveOldElements(now);

        Map<String, Double> result = new HashMap<>();
        for (Map.Entry<String, Integer> e : freqCounter.entrySet())
        {
            result.put(e.getKey(), (double)e.getValue() / MINUTES_IN_HOUR);
        }

        return result;
    }

    @Override
    public void printStatistic() {
        Map<String, Double> statistic = getAllEventStatistic();
        System.out.println(statistic);
    }
}
