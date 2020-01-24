package main.java.ru.evgeniyfeder.event_counter.clock;

import java.time.Instant;

public class NormalClock implements Clock {
    @Override
    public Instant now() {
        return Instant.now();
    }
}
