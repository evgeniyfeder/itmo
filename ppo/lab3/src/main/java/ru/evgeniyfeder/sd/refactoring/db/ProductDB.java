package ru.evgeniyfeder.sd.refactoring.db;

import java.sql.*;

public class ProductDB {
    static private final String createIfNotExistQuery =
            "CREATE TABLE IF NOT EXISTS PRODUCT " +
                    "(ID INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL," +
                    " NAME           TEXT    NOT NULL, " +
                    " PRICE          INT     NOT NULL)";


    private ProductDBStatement executeQuery(String query) throws SQLException {
        Connection c = DriverManager.getConnection(path);
        Statement stmt = c.createStatement();
        return new ProductDBStatement(c, stmt, stmt.executeQuery(query));
    }

    private void executeUpdate(String query) throws SQLException {
        try (Connection c = DriverManager.getConnection(path)) {
            try (Statement stmt = c.createStatement()) {
                stmt.executeUpdate(query);
            }
        }
    }

    public final String path;

    public ProductDB(String path) throws SQLException {
        this.path = path;
        this.executeUpdate(createIfNotExistQuery);
    }

    public ProductDBStatement getAllProduct() throws SQLException {
        return executeQuery("SELECT * FROM PRODUCT");
    }

    public ProductDBStatement getMaxProduct() throws SQLException {
        return executeQuery("SELECT * FROM PRODUCT ORDER BY PRICE DESC LIMIT 1");
    }

    public ProductDBStatement getMinProduct() throws SQLException {
        return executeQuery("SELECT * FROM PRODUCT ORDER BY PRICE LIMIT 1");
    }

    public ProductDBStatement getSumPrice() throws SQLException {
        return executeQuery("SELECT SUM(price) FROM PRODUCT");
    }

    public ProductDBStatement getCountProduct() throws SQLException {
        return executeQuery("SELECT COUNT(*) FROM PRODUCT");
    }

    public void insertOneProduct(String name, long price) throws SQLException {
        String sql = "INSERT INTO PRODUCT (NAME, PRICE) VALUES (" +
                "\"" + name + "\"," + price + ")";
        executeUpdate(sql);
    }
}
