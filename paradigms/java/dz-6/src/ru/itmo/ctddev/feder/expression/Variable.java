package ru.itmo.ctddev.feder.expression;

/**
 * Created by dzaba on 19.03.2017.
 */
public class Variable implements TripleExpression {
    String name;

    /* Constructor function */
    public Variable(String newName) {
        name = newName;
    } /* End of 'Variable' function */

    /* Count expression from one integer argument */
    public int evaluate(int x, int y, int z) {
        if (name.contentEquals("x"))
            return x;
        else if (name.contentEquals("y"))
            return y;
        else
            return z;
    } /* End of 'evaluate' function */
} /* End ща 'Variable' function */
