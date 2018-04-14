package expression.parser;

import expression.TripleExpression;
import expression.exceptions.ParseException;

public interface Parser {
    TripleExpression parse(String expression) throws ParseException;
}
