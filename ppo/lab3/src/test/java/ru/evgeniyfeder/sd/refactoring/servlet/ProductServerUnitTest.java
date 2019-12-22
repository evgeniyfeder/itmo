package ru.evgeniyfeder.sd.refactoring.servlet;

import static org.junit.Assert.assertEquals;
import static org.mockito.Mockito.*;

import org.junit.Before;
import org.junit.Test;
import ru.evgeniyfeder.sd.refactoring.db.ProductDB;
import ru.evgeniyfeder.sd.refactoring.db.ProductDBStatement;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.io.StringWriter;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;

public class ProductServerUnitTest {
    ProductDB productDB;

    HttpServletRequest request;
    HttpServletResponse response;
    StringWriter stringWriter;

    @Before
    public void setUp() throws IOException, SQLException {
        productDB = mock(ProductDB.class);

        Connection c = mock(Connection.class);
        Statement s = mock(Statement.class);
        ResultSet rs = mock(ResultSet.class);

        when(rs.next()).thenReturn(true).thenReturn(true).thenReturn(false);
        when(rs.getString("name")).thenReturn("iphone").thenReturn("iphone2");
        when(rs.getInt("price")).thenReturn(100).thenReturn(200);

        when(productDB.getAllProduct()).thenReturn(new ProductDBStatement(c, s, rs));

        rs = mock(ResultSet.class);
        when(rs.next()).thenReturn(true).thenReturn(false);
        when(rs.getString("name")).thenReturn("iphone2");
        when(rs.getInt("price")).thenReturn(200);
        when(productDB.getMaxProduct()).thenReturn(new ProductDBStatement(c, s, rs));

        rs = mock(ResultSet.class);
        when(rs.next()).thenReturn(true).thenReturn(false);
        when(rs.getString("name")).thenReturn("iphone");
        when(rs.getInt("price")).thenReturn(100);
        when(productDB.getMinProduct()).thenReturn(new ProductDBStatement(c, s, rs));

        rs = mock(ResultSet.class);
        when(rs.next()).thenReturn(true).thenReturn(false);
        when(rs.getInt(1)).thenReturn(300);
        when(productDB.getSumPrice()).thenReturn(new ProductDBStatement(c, s, rs));

        rs = mock(ResultSet.class);
        when(rs.next()).thenReturn(true).thenReturn(false);
        when(rs.getInt(1)).thenReturn(3);
        when(productDB.getCountProduct()).thenReturn(new ProductDBStatement(c, s, rs));

        GetProductsServlet x = new GetProductsServlet(productDB);
        request = mock(HttpServletRequest.class);
        response = mock(HttpServletResponse.class);


        stringWriter = new StringWriter();
        PrintWriter writer = new PrintWriter(stringWriter);
        when(response.getWriter()).thenReturn(writer);
    }

    @Test
    public void testGet() throws IOException {
        new GetProductsServlet(productDB).doGet(request, response);

        assertEquals(stringWriter.toString(),
                "<html><body>\n" +
                        "iphone\t100</br>\n" +
                        "iphone2\t200</br>\n" +
                        "</body></html>\n");
    }

    @Test
    public void testMax() throws IOException {
        when(request.getParameter("command")).thenReturn("max");
        new QueryServlet(productDB).doGet(request, response);

        assertEquals(stringWriter.toString(),
                "<html><body>\n" +
                        "<h1>Product with max price: </h1>\n" +
                        "iphone2\t200</br>\n" +
                        "</body></html>\n");
    }

    @Test
    public void testMin() throws IOException {
        when(request.getParameter("command")).thenReturn("min");
        new QueryServlet(productDB).doGet(request, response);

        assertEquals(stringWriter.toString(),
                "<html><body>\n" +
                        "<h1>Product with min price: </h1>\n" +
                        "iphone\t100</br>\n" +
                        "</body></html>\n");
    }

    @Test
    public void testCount() throws IOException {
        when(request.getParameter("command")).thenReturn("count");
        new QueryServlet(productDB).doGet(request, response);

        assertEquals(stringWriter.toString(),
                "<html><body>\n" +
                        "Number of products: </br>\n" +
                        "3\n" +
                        "</body></html>\n");
    }

    @Test
    public void testSum() throws IOException {
        when(request.getParameter("command")).thenReturn("sum");
        new QueryServlet(productDB).doGet(request, response);

        assertEquals(stringWriter.toString(),
                "<html><body>\n" +
                        "Summary price: </br>\n" +
                        "300\n" +
                        "</body></html>\n");
    }
}
