package main.java.ru.evgeniyfeder.event_counter.statistics;

import java.util.Map;

public interface EventStatistics {
    void incEvent(String name);

    Double getEventStatisticByName(String name);

    Map<String, Double> getAllEventStatistic();

    void printStatistic();
}
