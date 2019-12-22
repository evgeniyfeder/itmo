package ru.evgeniyfeder.sd.refactoring.servlet.queries;

import ru.evgeniyfeder.sd.refactoring.db.ProductDB;
import ru.evgeniyfeder.sd.refactoring.db.ProductDBStatement;

import java.sql.ResultSet;
import java.sql.SQLException;

public class CountQuery extends SelectIntegerAbstractQuery {
    @Override
    protected ProductDBStatement askResult(ProductDB productDB) throws SQLException {
        return productDB.getCountProduct();
    }

    @Override
    public String title() {
        return "Number of products: ";
    }
}
