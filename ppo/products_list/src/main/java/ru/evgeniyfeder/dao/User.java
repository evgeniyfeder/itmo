package ru.evgeniyfeder.dao;

import org.bson.Document;

public class User {
    private final int id;
    private final Currency currency;

    public User(int id, Currency currency) {
        this.id = id;
        this.currency = currency;
    }

    public User(Document doc) {
        this(doc.getInteger("id"), Currency.valueOf(doc.getString("currency")));
    }

    public Document toDocument() {
        return new Document("id", id).append("currency", currency.toString());
    }

    public int getId() {
        return id;
    }

    public Currency getCurrency() {
        return currency;
    }

    @Override
    public String toString() {
        return "User{" +
                "id=" + id +
                ", currency=" + currency +
                '}';
    }
}
