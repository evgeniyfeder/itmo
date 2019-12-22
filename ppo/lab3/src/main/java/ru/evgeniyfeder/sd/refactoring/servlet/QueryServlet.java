package ru.evgeniyfeder.sd.refactoring.servlet;

import ru.evgeniyfeder.sd.refactoring.db.ProductDB;
import ru.evgeniyfeder.sd.refactoring.servlet.queries.*;

import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;

public class QueryServlet extends HttpServlet {
    ProductDB db;

    public QueryServlet(ProductDB db) {
        this.db = db;
    }

    @Override
    protected void doGet(HttpServletRequest request, HttpServletResponse response) throws IOException {
        String command = request.getParameter("command");

        SelectQuery query = null;

        try {
            if ("max".equals(command)) {
                query = new MaxPriceQuery();
            } else if ("min".equals(command)) {
                query = new MinPriceQuery();
            } else if ("sum".equals(command)) {
                query = new SumQuery();
            } else if ("count".equals(command)) {
                query = new CountQuery();
            } else {
                response.getWriter().println("Unknown command: " + command);
            }

            if (query != null) {
                query.run(db, request, response);
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        }

        response.setContentType("text/html");
        response.setStatus(HttpServletResponse.SC_OK);
    }

}
