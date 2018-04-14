package ru.itmo.ctddev.feder.expression;

/**
 * Created by dzaba on 19.03.2017.
 */
public strictfp class Const implements TripleExpression {
    private final int value;

    /* Constructor function */
    public Const(int newValue) {
        value = newValue;
    } /* End of 'Const' function */

    /* Count expression from one integer argument */
    public int evaluate(int x, int y, int z) {
        return value;
    } /* End of 'evaluate' function */
}
