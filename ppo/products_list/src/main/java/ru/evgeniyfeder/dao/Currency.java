package ru.evgeniyfeder.dao;

public enum Currency {
    RUB(1), EUR(0.012), USD(0.013);

    private final double cost;
    Currency(double cost) {
        this.cost = cost;
    }

    static double convert(double value, Currency from, Currency to) {
        return value * to.cost / from.cost;
    }
}
