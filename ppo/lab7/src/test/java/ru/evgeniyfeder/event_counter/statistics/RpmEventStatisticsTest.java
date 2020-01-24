package test.java.ru.evgeniyfeder.event_counter.statistics;

import main.java.ru.evgeniyfeder.event_counter.clock.SetableClock;
import main.java.ru.evgeniyfeder.event_counter.statistics.RpmEventStatistics;
import org.junit.Test;

import java.time.Duration;
import java.time.Instant;
import java.util.HashMap;
import java.util.Map;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertTrue;

public class RpmEventStatisticsTest {

    private boolean epsEquils(Double a, Double b)
    {
        double EPS = 1e-6;
        return Math.abs(a - b) <= EPS;
    }
    private void assertEpsEquil(Map<String, Double> expected, Map<String, Double> actual)
    {
        assertEquals(expected.keySet(), actual.keySet());

        for (Map.Entry<String, Double> e : expected.entrySet())
        {
            assertTrue(epsEquils(e.getValue(), actual.get(e.getKey())));
        }
    }

    @Test
    public void testGetOne() {
        Instant nowTime = Instant.now();
        SetableClock clock = new SetableClock(nowTime);
        RpmEventStatistics stat = new RpmEventStatistics(clock);

        stat.incEvent("1");
        stat.incEvent("2");

        clock.setNow(nowTime.plus(Duration.ofHours(1)));
        stat.incEvent("1");

        assertTrue(epsEquils(1. / 60., stat.getEventStatisticByName("1")));
        assertTrue(epsEquils(0., stat.getEventStatisticByName("2")));
    }
    
    @Test
    public void testCheckAllStatistic() {
        Instant nowTime = Instant.now();
        SetableClock clock = new SetableClock(nowTime);
        RpmEventStatistics stat = new RpmEventStatistics(clock);

        stat.incEvent("1");

        stat.incEvent("2");
        stat.incEvent("2");

        stat.incEvent("3");
        stat.incEvent("3");
        stat.incEvent("3");

        Map<String, Double> expected = new HashMap<String, Double>()
        {
            {
                put("1", 1. / 60.);
                put("2", 2. / 60.);
                put("3", 3. / 60.);
            }
        };
        assertEpsEquil(stat.getAllEventStatistic(), expected);
    }

    @Test
    public void testDeletingAfterOneHour() {
        Instant nowTime = Instant.now();
        SetableClock clock = new SetableClock(nowTime);
        RpmEventStatistics stat = new RpmEventStatistics(clock);

        stat.incEvent("1");

        clock.setNow(nowTime.plus(Duration.ofHours(2)));
        stat.incEvent("2");
        stat.incEvent("2");

        Map<String, Double> expected = new HashMap<String, Double>()
        {
            {
                put("2", 2. / 60.);
            }
        };
        assertEpsEquil(expected, stat.getAllEventStatistic());

        clock.setNow(nowTime.plus(Duration.ofHours(3)));
        stat.incEvent("3");
        stat.incEvent("3");
        stat.incEvent("3");
        stat.incEvent("1");
        expected = new HashMap<String, Double>()
        {
            {
                put("1", 1. / 60.);
                put("3", 3. / 60.);
            }
        };
        assertEpsEquil(expected, stat.getAllEventStatistic());
    }

}
