package ru.evgeniyfeder.exchanger.model;

import java.util.Map;

public class User {
    private final int id;
    private final String name;
    private double moneyRub;
    private final Map<Integer, Integer> stocks;

    public User(int id, String name, double moneyRub, Map<Integer, Integer> stocks) {
        this.id = id;
        this.name = name;
        this.moneyRub = moneyRub;
        this.stocks = stocks;
    }

    public int getId() {
        return id;
    }

    public String getName() {
        return name;
    }

    public double getMoneyRub() {
        return moneyRub;
    }

    public Map<Integer, Integer> getStocks() {
        return stocks;
    }

    public void changeMoneyRub(double delta) {
        moneyRub += delta;
    }
}
