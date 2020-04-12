package ru.evgeniyfeder.server;

import io.netty.handler.codec.http.HttpResponseStatus;
import io.reactivex.netty.protocol.http.server.HttpServer;
import ru.evgeniyfeder.dao.Currency;
import ru.evgeniyfeder.dao.Product;
import ru.evgeniyfeder.dao.ReactiveMongoDriver;
import ru.evgeniyfeder.dao.User;
import rx.Observable;

import java.util.List;
import java.util.Map;

public class Server {
    static String MONGODB_URL = "mongodb://localhost:27017";
    static ReactiveMongoDriver driver = new ReactiveMongoDriver(MONGODB_URL);

    public static void main(final String[] args) {
        HttpServer
                .newServer(8080)
                .start((req, resp) -> {

                    String action = req.getDecodedPath().substring(1);

                    Observable<String> responseMessage;
                    try {
                        responseMessage = process(action, req.getQueryParameters());
                    } catch (RuntimeException e) {
                        responseMessage = Observable.just(e.getMessage());
                        resp.setStatus(HttpResponseStatus.BAD_REQUEST);
                    }

                    return resp.writeString(responseMessage);
                })
                .awaitShutdown();
    }

    private static Observable<String> process(String action, Map<String, List<String>> queryParameters) {
        Observable<String> res;

        switch (action) {
            case "register": // id, currency
                res = processRegister(queryParameters);
                break;
            case "add_product": // name, value, currency
                res = processAddProduct(queryParameters);
                break;
            case "list": // id
                res = processListProducts(queryParameters);
                break;
            default:
                throw new RuntimeException("Wrong action");
        }

        return res;
    }

    public static Observable<String> processListProducts(Map<String, List<String>> queryParameters) {
        int id = Integer.parseInt(queryParameters.get("id").get(0));

        return driver.getUser(id).map(User::getCurrency)
                .flatMap(currency -> driver.getAllProducts()
                                           .map(product -> product.changeCurrency(currency))
                                           .map(product -> product.toString() + "\n"));
    }

    public static Observable<String> processAddProduct(Map<String, List<String>> queryParameters) {
        String name = queryParameters.get("name").get(0);
        double value = Double.parseDouble(queryParameters.get("value").get(0));
        Currency currency = Currency.valueOf(queryParameters.get("currency").get(0));

        return driver.addProduct(new Product(name, value, currency))
                .map(success -> String.format("Product with name '%s' inserted with code '%s'", name, success.toString()));
    }

    public static Observable<String> processRegister(Map<String, List<String>> queryParameters) {
        int id = Integer.parseInt(queryParameters.get("id").get(0));
        Currency currency = Currency.valueOf(queryParameters.get("currency").get(0));

        return driver.addUser(new User(id, currency))
                .map(success -> String.format("User with id '%d' inserted with code '%s'", id, success.toString()));

    }
}
