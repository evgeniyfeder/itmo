package main.java.ru.evgeniyfeder.event_counter.clock;

import java.time.Instant;

public interface Clock {
    Instant now();
}
