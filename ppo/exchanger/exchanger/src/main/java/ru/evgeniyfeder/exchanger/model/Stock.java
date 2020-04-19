package ru.evgeniyfeder.exchanger.model;

public class Stock {
    private final int id;
    private final String name;
    private final double priceRub;
    private final int number;

    public Stock(int id, String name, double priceRub, int number) {
        this.id = id;
        this.name = name;
        this.priceRub = priceRub;
        this.number = number;
    }

    public int getId() {
        return id;
    }

    public double getPriceRub() {
        return priceRub;
    }

    public int getNumber() {
        return number;
    }

    public String getName() {
        return name;
    }

}
