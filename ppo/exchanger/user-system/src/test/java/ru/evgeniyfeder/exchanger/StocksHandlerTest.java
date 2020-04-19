package ru.evgeniyfeder.exchanger;

import org.junit.Assert;
import org.junit.Before;
import org.junit.ClassRule;
import org.junit.Test;
import org.testcontainers.containers.FixedHostPortGenericContainer;
import org.testcontainers.containers.GenericContainer;
import org.testcontainers.shaded.com.fasterxml.jackson.annotation.JsonTypeInfo;
import ru.evgeniyfeder.exchanger.client.StocksClient;
import ru.evgeniyfeder.exchanger.client.StocksClientImpl;
import ru.evgeniyfeder.exchanger.model.Stock;
import ru.evgeniyfeder.exchanger.users.InMemoryUsersDao;

import java.net.URI;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.util.List;

public class StocksHandlerTest {

    @ClassRule
    public static GenericContainer simpleWebServer
            = new FixedHostPortGenericContainer("exchanger-app:1.0-SNAPSHOT")
            .withFixedExposedPort(8080, 8080)
            .withExposedPorts(8080);

    private InMemoryUsersDao usersDao;

    @Before
    public void before() {
        StocksClient client = new StocksClientImpl("http://127.0.0.1", 8080);
        usersDao = new InMemoryUsersDao(client);

        int id = client.addCompany("itmo");
        client.addStocks(id, 100);
        client.changeCost(id, 100);

        id = client.addCompany("adqwasd");
        client.addStocks(id, 1);
        client.changeCost(id, 10);

        id = client.addCompany("asdaeqweq");
        client.addStocks(id, 5);
        client.changeCost(id, 1000);
    }

    @Test
    public void testAddUser() throws Exception {
        Assert.assertEquals(0, usersDao.addUser("Petya"));
        Assert.assertEquals(1, usersDao.addUser("Vasya"));
    }

    @Test
    public void testBuyAndSellStock() throws Exception {
        Assert.assertEquals(0, usersDao.addUser("Petya"));

        Assert.assertTrue(usersDao.addMoney(0, 5));
        Assert.assertFalse(usersDao.buyStock(0, 1,  1));
        Assert.assertTrue(usersDao.addMoney(0, 15));

        Assert.assertTrue(usersDao.buyStock(0, 1,  1));
        Assert.assertEquals(20, usersDao.getUserMoney(0), 0.0001);

        Assert.assertTrue(usersDao.soldStock(0, 1, 1));
        Assert.assertEquals(20, usersDao.getUserMoney(0), 0.0001);

        Assert.assertFalse(usersDao.soldStock(0, 1, 1));
    }

    @Test
    public void testGetStocks() throws Exception {
        Assert.assertEquals(0, usersDao.addUser("Petya"));

        Assert.assertTrue(usersDao.addMoney(0, 100000));
        Assert.assertTrue(usersDao.buyStock(0, 0,  10));
        Assert.assertTrue(usersDao.buyStock(0, 2,  10));

        Assert.assertEquals(100000, usersDao.getUserMoney(0), 0.1);

        List<Stock> stocks = usersDao.getUserStocks(0);

        Assert.assertEquals(2, stocks.size());
        Assert.assertEquals(0, stocks.get(0).getId());
        Assert.assertEquals(2, stocks.get(1).getId());
        Assert.assertEquals(100, stocks.get(0).getPriceRub(), 0.1);
        Assert.assertEquals(1000, stocks.get(1).getPriceRub(), 0.1);
        Assert.assertEquals(10, stocks.get(0).getNumber());
        Assert.assertEquals(10, stocks.get(1).getNumber());
    }
}
