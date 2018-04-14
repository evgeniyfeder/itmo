package ru.itmo.ctddev.feder.expression.test;

import expression.*;

/**
 * Created by dzaba on 19.03.2017.
 */
public class MyTest {
    /* The started function of programme */
    public static void main(String[] args) {
        Expression ex = new Add(
                new Subtract(
                        new Multiply(
                                new Variable("x"),
                                new Variable("x")
                        ),
                        new Multiply(
                                new Variable("x"),
                                new Const(2)
                        )
                ),
                new Const(1)
        );

        System.out.println(ex.evaluate(Integer.parseInt(args[0])));
    } /* End of 'MyTest' function */
}
