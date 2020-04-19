package ru.evgeniyfeder.exchanger.dao;

import ru.evgeniyfeder.exchanger.model.Stock;

public interface StocksDao {
    int addCompanyStocks(String name);

    boolean addStocks(int companyId, int number);
    boolean changeStockPrice(int companyId, double delta);


    Stock getStock(int companyId);
    boolean buyStock(int companyId, int number);
    double sellStock(int companyId, int number);
}
