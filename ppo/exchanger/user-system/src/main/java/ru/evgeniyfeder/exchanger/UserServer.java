package ru.evgeniyfeder.exchanger;

import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import java.util.Collections;

@SpringBootApplication
public class UserServer {
    public static void main(String[] args) {
        SpringApplication app = new SpringApplication(UserServer.class);
        app.setDefaultProperties(Collections.singletonMap("server.port", "8081"));
        app.run(args);

    }
}
