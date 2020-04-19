package ru.evgeniyfeder.exchanger.client;

import ru.evgeniyfeder.exchanger.model.Stock;

import java.io.IOException;
import java.net.URI;
import java.net.URISyntaxException;
import java.net.http.HttpClient;
import java.net.http.HttpRequest;
import java.net.http.HttpResponse;
import java.time.Duration;

public class StocksClientImpl implements StocksClient {
    HttpClient client = HttpClient.newBuilder()
                            .connectTimeout(Duration.ofSeconds(2))
                            .build();

    private final String host;
    private final int port;

    public StocksClientImpl(String host, int port) {
        this.host = host;
        this.port = port;
    }

    @Override
    public boolean buyStocks(int companyId, int count) {
        String requestURI = String.format("%s:%d/buy_stock?id=%d&number=%d", host, port, companyId, count);
        HttpRequest request = null;
        try {
            request = HttpRequest.newBuilder()
                    .uri(new URI(requestURI))
                    .GET()
                    .build();

            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
            return response.statusCode() == 200;
        } catch (URISyntaxException | InterruptedException | IOException e) {
            e.printStackTrace();
        }

        return false;
    }

    @Override
    public Double getStockPrice(int companyId) {
        String requestURI = String.format("%s:%s/get_stock_price?id=%d", host, port, companyId);
        HttpRequest request = null;
        try {
            request = HttpRequest.newBuilder()
                    .uri(new URI(requestURI))
                    .GET()
                    .build();

            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
            if (response.statusCode() == 200)
                return Double.parseDouble(response.body());
        } catch (URISyntaxException | InterruptedException | IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public Integer getStockCount(int companyId) {
        String requestURI = String.format("%s:%s/get_stock_count?id=%d", host, port, companyId);
        HttpRequest request = null;
        try {
            request = HttpRequest.newBuilder()
                    .uri(new URI(requestURI))
                    .GET()
                    .build();

            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
            if (response.statusCode() == 200)
                return Integer.parseInt(response.body());
        } catch (URISyntaxException | InterruptedException | IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public Integer addCompany(String name) {
        String requestURI = String.format("%s:%s/add_company?name=%s", host, port, name);
        HttpRequest request;
        try {
            request = HttpRequest.newBuilder()
                    .uri(new URI(requestURI))
                    .GET()
                    .build();

            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
            if (response.statusCode() == 200)
                return Integer.parseInt(response.body());
        } catch (URISyntaxException | InterruptedException | IOException e) {
            e.printStackTrace();
        }
        return null;
    }

    @Override
    public void changeCost(int id, double delta) {
        String requestURI = String.format("%s:%s/change_stock_cost?id=%d&delta=%f", host, port, id, delta);
        HttpRequest request = null;
        try {
            request = HttpRequest.newBuilder()
                    .uri(new URI(requestURI))
                    .GET()
                    .build();

            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
        } catch (URISyntaxException | InterruptedException | IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void addStocks(int id, int number) {
        String requestURI = String.format("%s:%s/add_stocks?id=%d&number=%d", host, port, id, number);
        HttpRequest request = null;
        try {
            request = HttpRequest.newBuilder()
                    .uri(new URI(requestURI))
                    .GET()
                    .build();

            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
        } catch (URISyntaxException | InterruptedException | IOException e) {
            e.printStackTrace();
        }
    }


    @Override
    public boolean sellStocks(int companyId, int count) {
        String requestURI = String.format("%s:%d/sell_stock?id=%d&number=%d", host, port, companyId, count);
        HttpRequest request = null;
        try {
            request = HttpRequest.newBuilder()
                    .uri(new URI(requestURI))
                    .GET()
                    .build();

            HttpResponse<String> response = client.send(request, HttpResponse.BodyHandlers.ofString());
            return response.statusCode() == 200;
        } catch (URISyntaxException | InterruptedException | IOException e) {
            e.printStackTrace();
        }
        return false;
    }
}
