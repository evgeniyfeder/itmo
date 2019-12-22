package ru.evgeniyfeder.sd.refactoring.db;

import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class ProductDBStatement implements AutoCloseable {
    public ResultSet rs;
    private Connection c;
    private Statement stmt;

    public ProductDBStatement(Connection c, Statement stmt, ResultSet rs)
    {
        this.rs = rs;
        this.c = c;
        this.stmt = stmt;
    }

    @Override
    public void close() throws SQLException {
        rs.close();
        stmt.close();
        c.close();
    }
}
