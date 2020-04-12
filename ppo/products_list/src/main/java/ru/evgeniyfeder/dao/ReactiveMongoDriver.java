package ru.evgeniyfeder.dao;

import com.mongodb.rx.client.MongoClient;
import com.mongodb.rx.client.MongoClients;
import com.mongodb.rx.client.MongoCollection;
import com.mongodb.rx.client.Success;
import org.bson.Document;
import rx.Observable;

import static com.mongodb.client.model.Filters.eq;

public class ReactiveMongoDriver {
    private static MongoClient client;

    private static final String DATABASE_NAME = "product_list";
    private static final String USER_COLLECTION = "user";
    private static final String PRODUCT_COLLECTION = "product";

    public ReactiveMongoDriver(String url) {
        client = MongoClients.create(url);
    }

    public Observable<Success> addUser(User user) {
        return client.getDatabase(DATABASE_NAME)
                     .getCollection(USER_COLLECTION)
                     .insertOne(user.toDocument());
    }

    public Observable<Success> addProduct(Product product) {
        return client.getDatabase(DATABASE_NAME)
                     .getCollection(PRODUCT_COLLECTION)
                     .insertOne(product.toDocument());
    }

    public Observable<Product> getAllProducts() {
        return client.getDatabase(DATABASE_NAME)
                     .getCollection(PRODUCT_COLLECTION)
                     .find()
                     .toObservable().map(Product::new);
    }

    public Observable<User> getUser(int id) {
        return client.getDatabase(DATABASE_NAME)
                .getCollection(USER_COLLECTION)
                .find(eq("id", id))
                .toObservable().map(User::new);
    }

}

