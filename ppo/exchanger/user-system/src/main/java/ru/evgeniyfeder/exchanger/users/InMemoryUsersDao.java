package ru.evgeniyfeder.exchanger.users;

import ru.evgeniyfeder.exchanger.client.StocksClient;
import ru.evgeniyfeder.exchanger.model.Stock;
import ru.evgeniyfeder.exchanger.model.User;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class InMemoryUsersDao implements UsersDao {
    private final List<User> users = new ArrayList<User>();
    private final StocksClient client;

    public InMemoryUsersDao(StocksClient client) {
        this.client = client;
    }

    @Override
    public int addUser(String name) {
        int nextId = users.size();
        users.add(new User(nextId, name, 0, new HashMap<>()));
        return nextId;
    }

    @Override
    public boolean addMoney(int userId, double money) {
        if (userId >= users.size()) {
            return false;
        }

        User user = users.get(userId);
        users.set(userId, new User(user.getId(), user.getName(),
                                   user.getMoneyRub() + money,
                                   user.getStocks()));
        return true;
    }

    @Override
    public List<Stock> getUserStocks(int userId) {
        if (userId >= users.size())
            return null;

        List<Stock> res = new ArrayList<>();
        User user = users.get(userId);
        for (Map.Entry<Integer, Integer> idAndCount : user.getStocks().entrySet()) {
            int id = idAndCount.getKey();
            res.add(new Stock(id, client.getStockPrice(id), idAndCount.getValue()));
        }

        return res;
    }

    @Override
    public Double getUserMoney(int userId) {
        if (userId >= users.size())
            return null;

        List<Stock> stocks = getUserStocks(userId);

        double res = users.get(userId).getMoneyRub();
        for (Stock s : stocks) {
            res += s.getNumber() * s.getPriceRub();
        }
        return res;
    }

    @Override
    public boolean buyStock(int userId, int companyId, int count) {
        if (userId >= users.size())
            return false;

        User user = users.get(userId);
        double cost = client.getStockPrice(companyId);
        if (cost * count >= user.getMoneyRub())
            return false;

        boolean bought = client.buyStocks(companyId, count);

        if (bought) {
            user.getStocks().put(companyId, user.getStocks().getOrDefault(companyId, 0) + count);
            user.changeMoneyRub(-cost * count);

            return true;
        } else {
            return false;
        }
    }

    @Override
    public boolean soldStock(int userId, int companyId, int count) {
        if (userId >= users.size())
            return false;

        User user = users.get(userId);
        double cost = client.getStockPrice(companyId);
        if (user.getStocks().getOrDefault(companyId, 0) < count)
            return false;

        boolean sold = client.sellStocks(companyId, count);

        if (sold) {
            user.getStocks().put(companyId, user.getStocks().getOrDefault(companyId, 0) - count);
            user.changeMoneyRub(cost * count);
            return true;
        } else {
            return false;
        }
    }
}
