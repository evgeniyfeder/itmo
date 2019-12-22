package ru.evgeniyfeder.sd.refactoring.servlet;

import ru.evgeniyfeder.sd.refactoring.db.ProductDB;
import ru.evgeniyfeder.sd.refactoring.db.ProductDBStatement;
import ru.evgeniyfeder.sd.refactoring.html.HTMLPrinter;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.Statement;

public class GetProductsServlet extends HttpServlet {
    ProductDB db;

    public GetProductsServlet(ProductDB db) {
        this.db = db;
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        try {
            try (ProductDBStatement pdbs = db.getAllProduct()) {
                try(HTMLPrinter html = new HTMLPrinter(response.getWriter())) {
                    while (pdbs.rs.next()) {
                        String name = pdbs.rs.getString("name");
                        int price = pdbs.rs.getInt("price");

                        html.println(name + "\t" + price);
                    }
                }
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

        response.setContentType("text/html");
        response.setStatus(HttpServletResponse.SC_OK);
    }
}
