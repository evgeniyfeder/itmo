package ru.evgeniyfeder.sd.refactoring.servlet.queries;

import ru.evgeniyfeder.sd.refactoring.db.ProductDB;
import ru.evgeniyfeder.sd.refactoring.db.ProductDBStatement;
import ru.evgeniyfeder.sd.refactoring.html.HTMLPrinter;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.sql.ResultSet;
import java.sql.SQLException;

abstract public class SelectIntegerAbstractQuery implements SelectQuery {
    protected abstract ProductDBStatement askResult(ProductDB productDB) throws SQLException;

    @Override
    public abstract String title();

    @Override
    public void run(ProductDB productDB, HttpServletRequest request, HttpServletResponse response) throws SQLException, IOException {
        try (ProductDBStatement pdbs = this.askResult(productDB)) {
            try (HTMLPrinter html = new HTMLPrinter(response.getWriter())) {
                html.println(this.title());
                if (pdbs.rs.next()) {
                    html.print(pdbs.rs.getInt(1));
                }
            }
        }
    }
}
