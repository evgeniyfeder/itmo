package ru.itmo.ctddev.feder.parser;

import ru.itmo.ctddev.feder.expression.TripleExpression;

/**
 * Created by Evgeniy on 29.03.2017.
 */
public interface Parser {
    /* Parse expression */
    TripleExpression parse(String expression);
}
