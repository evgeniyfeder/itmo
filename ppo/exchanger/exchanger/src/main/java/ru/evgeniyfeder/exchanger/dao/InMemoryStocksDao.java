package ru.evgeniyfeder.exchanger.dao;

import ru.evgeniyfeder.exchanger.model.Stock;

import java.util.ArrayList;
import java.util.List;

public class InMemoryStocksDao implements StocksDao {
    private final List<Stock> stocks = new ArrayList<>();

    @Override
    public int addCompanyStocks(String name) {
        int newId = stocks.size();
        stocks.add(new Stock(newId, name, 0, 0));
        return newId;
    }

    @Override
    public boolean addStocks(int companyId, int number) {
        if (companyId >= stocks.size() || number <= 0)
            return false;

        Stock stock = stocks.get(companyId);
        stocks.set(companyId, new Stock(stock.getId(), stock.getName(),
                                        stock.getPriceRub(), stock.getNumber() + number));
        return true;
    }

    @Override
    public boolean changeStockPrice(int companyId, double delta) {
        if (companyId >= stocks.size())
            return false;

        Stock stock = stocks.get(companyId);
        stocks.set(companyId, new Stock(stock.getId(), stock.getName(),
                stock.getPriceRub() + delta, stock.getNumber()));
        return true;
    }

    @Override
    public Stock getStock(int companyId) {
        if (companyId >= stocks.size())
            return null;

        return stocks.get(companyId);
    }

    @Override
    public boolean buyStock(int companyId, int number) {
        if (companyId >= stocks.size() || number <= 0)
            return false;

        Stock stock = stocks.get(companyId);
        assert stock.getNumber() - number >= 0;
        stocks.set(companyId, new Stock(stock.getId(), stock.getName(),
                stock.getPriceRub(), stock.getNumber() + number));
        return true;
    }

    @Override
    public double sellStock(int companyId, int number) {
        if (companyId >= stocks.size() || number <= 0)
            return 0;

        Stock stock = stocks.get(companyId);
        stocks.set(companyId, new Stock(stock.getId(), stock.getName(),
                stock.getPriceRub(), stock.getNumber() + number));
        return stock.getPriceRub() * number;
    }
}
