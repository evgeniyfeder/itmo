package ru.itmo.ctddev.feder.expression;

/* Subtract operation class type */
public class Subtract extends AbstractBinaryOperation {
    /* Constructor function */
    public Subtract(TripleExpression newLeft, TripleExpression newRight) {
        super(newLeft, newRight);
    } /* End of 'Subtract' function */

    /* Do integer operation function */
    protected int doOper(int left, int right) {
        return left - right;
    }
}
