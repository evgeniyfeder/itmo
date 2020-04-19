package ru.evgeniyfeder.exchanger.client;

import ru.evgeniyfeder.exchanger.model.Stock;

public interface StocksClient {
    boolean buyStocks(int companyId, int count);
    boolean sellStocks(int companyId, int count);

    Double getStockPrice(int companyId);
    Integer getStockCount(int companyId);

    Integer addCompany(String name);
    void changeCost(int id, double delta);
    void addStocks(int id, int number);
}
