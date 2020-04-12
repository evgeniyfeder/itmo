package seachers;

import org.junit.Test;

import scala.concurrent.duration.Duration;
import searchers.SearchSiteInfo;
import searchers.Searcher;

import java.util.HashMap;
import java.util.concurrent.TimeUnit;

import static org.junit.Assert.*;

public class SearcherTest {
    private static final String LOCALHOST = "127.0.0.1";
    private static final int PORT1 = 12345;
    private static final int PORT2 = 23456;

    private static final Duration NO_TIMEOUT = Duration.create(0, TimeUnit.MILLISECONDS);
    private static final Duration DEFAULT_TIMEOUT = Duration.create(1000, TimeUnit.MILLISECONDS);
    private static final Duration LONG_TIMEOUT = Duration.create(2000, TimeUnit.MILLISECONDS);

    @Test
    public void oneSearchSiteAndCheckData()
    {
        try (SearcherStubServer server = new SearcherStubServer(PORT1, NO_TIMEOUT)) {
            Searcher searcher = new Searcher();
            searcher.AddSearchSite(new SearchSiteInfo(LOCALHOST, "1", PORT1));

            HashMap<String, String> searchResult = searcher.search("ppo", DEFAULT_TIMEOUT);

            assertEquals(1, searchResult.entrySet().size());
            assertTrue(searchResult.containsKey("1"));
            assertEquals(SearcherStubServer.genResponse("ppo"), searchResult.get("1"));
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Test
    public void twoSearchSite()
    {
        try (SearcherStubServer server1 = new SearcherStubServer(PORT1, NO_TIMEOUT)) {
            try (SearcherStubServer server2 = new SearcherStubServer(PORT2, NO_TIMEOUT)) {
                Searcher searcher = new Searcher();
                searcher.AddSearchSite(new SearchSiteInfo(LOCALHOST, "1", PORT1));
                searcher.AddSearchSite(new SearchSiteInfo(LOCALHOST, "2", PORT2));

                HashMap<String, String> searchResult = searcher.search("ppo", DEFAULT_TIMEOUT);

                assertEquals(2, searchResult.entrySet().size());
                assertTrue(searchResult.containsKey("1"));
                assertTrue(searchResult.containsKey("2"));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Test
    public void twoSearchSiteOneLong()
    {
        try (SearcherStubServer server1 = new SearcherStubServer(PORT1, LONG_TIMEOUT)) {
            try (SearcherStubServer server2 = new SearcherStubServer(PORT2, NO_TIMEOUT)) {
                Searcher searcher = new Searcher();
                searcher.AddSearchSite(new SearchSiteInfo(LOCALHOST, "1", PORT1));
                searcher.AddSearchSite(new SearchSiteInfo(LOCALHOST, "2", PORT2));

                HashMap<String, String> searchResult = searcher.search("ppo", DEFAULT_TIMEOUT);

                assertEquals(1, searchResult.entrySet().size());
                assertTrue(searchResult.containsKey("2"));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }
}
