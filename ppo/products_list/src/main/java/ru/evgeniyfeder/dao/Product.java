package ru.evgeniyfeder.dao;

import org.bson.Document;

public class Product {
    private final String name;
    private final double value;
    private final Currency currency;

    public Product(String name, double value, Currency currency) {
        this.name = name;
        this.value = value;
        this.currency = currency;
    }

    public Product(Document doc) {
        this(doc.getString("name"), doc.getDouble("value"), Currency.valueOf(doc.getString("currency")));
    }
    public Document toDocument() {
        return new Document("name", name).
                append("value", value).
                append("currency", currency.toString());
    }

    public Product changeCurrency(Currency newCurrency) {
        return new Product(name, Currency.convert(value, currency, newCurrency), newCurrency);
    }

    public String getName() {
        return name;
    }

    public double getValue(Currency need) {
        return Currency.convert(value, currency, need);
    }

    @Override
    public String toString() {
        return "Product{" +
                "name=" + name +
                ", value=" + value +
                ", currency=" + currency +
                '}';
    }
}
