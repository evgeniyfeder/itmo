package ru.evgeniyfeder.sd.refactoring;

import org.eclipse.jetty.server.Server;
import org.eclipse.jetty.servlet.ServletContextHandler;
import org.eclipse.jetty.servlet.ServletHolder;
import ru.evgeniyfeder.sd.refactoring.db.ProductDB;
import ru.evgeniyfeder.sd.refactoring.servlet.AddProductServlet;
import ru.evgeniyfeder.sd.refactoring.servlet.GetProductsServlet;
import ru.evgeniyfeder.sd.refactoring.servlet.QueryServlet;


public class Main {
    public static void main(String[] args) throws Exception {
        ProductDB productDB = new ProductDB("jdbc:sqlite:test.db");

        Server server = new Server(8081);

        ServletContextHandler context = new ServletContextHandler(ServletContextHandler.SESSIONS);
        context.setContextPath("/");
        server.setHandler(context);

        context.addServlet(new ServletHolder(new AddProductServlet(productDB)), "/add-product");
        context.addServlet(new ServletHolder(new GetProductsServlet(productDB)),"/get-products");
        context.addServlet(new ServletHolder(new QueryServlet(productDB)),"/query");

        server.start();
        server.join();
    }
}
