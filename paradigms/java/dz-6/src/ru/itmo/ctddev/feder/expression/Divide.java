package ru.itmo.ctddev.feder.expression;

/* Divide operation class type */
public class Divide extends AbstractBinaryOperation {
    /* Constructor function */
    public Divide(TripleExpression newLeft, TripleExpression newRight) {
        super(newLeft, newRight);
    } /* End of 'Divide' function */

    /* Do integer operation function */
    protected int doOper(int left, int right) {
        return left / right;
    }
}
