package ru.itmo.ctddev.feder.expression;

/**
 * Created by dzaba on 19.03.2017.
 */
public class Const extends AbstractExpression {
    int value;

    /* Constructor function */
    public Const(int newValue) {
        super(null, null);
        value = newValue;
    } /* End of 'Const' function */

    /* Do operation function */
    protected int doOper(int left, int right) {
        return value;
    }
}
