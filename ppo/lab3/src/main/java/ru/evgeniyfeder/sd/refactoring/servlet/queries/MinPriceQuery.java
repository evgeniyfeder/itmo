package ru.evgeniyfeder.sd.refactoring.servlet.queries;

import ru.evgeniyfeder.sd.refactoring.db.ProductDB;
import ru.evgeniyfeder.sd.refactoring.db.ProductDBStatement;

import java.sql.ResultSet;
import java.sql.SQLException;

public class MinPriceQuery extends SelectProductsAbstractQuery {
    @Override
    protected ProductDBStatement askResults(ProductDB productDB) throws SQLException {
        return productDB.getMinProduct();
    }

    @Override
    public String title() {
        return "Product with min price: ";
    }
}
