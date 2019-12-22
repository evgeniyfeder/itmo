package ru.evgeniyfeder.sd.refactoring.servlet.queries;

import ru.evgeniyfeder.sd.refactoring.db.ProductDB;
import ru.evgeniyfeder.sd.refactoring.db.ProductDBStatement;

import java.sql.ResultSet;
import java.sql.SQLException;

public class SumQuery extends SelectIntegerAbstractQuery {
    @Override
    protected ProductDBStatement askResult(ProductDB productDB) throws SQLException {
        return productDB.getSumPrice();
    }

    @Override
    public String title() {
        return "Summary price: ";
    }
}
