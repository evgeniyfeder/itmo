package ru.evgeniyfeder.exchanger.users;


import ru.evgeniyfeder.exchanger.model.Stock;

import java.util.List;

public interface UsersDao {
    int addUser(String name);
    boolean addMoney(int userId, double money);

    List<Stock> getUserStocks(int userId);

    Double getUserMoney(int userId);
    boolean buyStock(int userId, int companyId, int count);
    boolean soldStock(int userId, int companyId, int count);
}
