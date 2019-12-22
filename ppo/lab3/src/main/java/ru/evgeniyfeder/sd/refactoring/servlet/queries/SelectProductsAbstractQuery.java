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

abstract public class SelectProductsAbstractQuery implements SelectQuery {
    protected abstract ProductDBStatement askResults(ProductDB productDB) throws SQLException;


    @Override
    public abstract String title();

    @Override
    public void run(ProductDB productDB, HttpServletRequest request, HttpServletResponse response) throws SQLException, IOException {
        try (ProductDBStatement pdbs = this.askResults(productDB)) {
            try (HTMLPrinter html = new HTMLPrinter(response.getWriter())) {
                html.putWithH1(this.title());
                while (pdbs.rs.next()) {
                    String name = pdbs.rs.getString("name");
                    int price = pdbs.rs.getInt("price");
                    html.println(name + "\t" + price);
                }
            }
        }
    }
}
