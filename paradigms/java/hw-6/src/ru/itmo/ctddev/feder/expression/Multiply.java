package ru.itmo.ctddev.feder.expression;

/* Multiply operation class type */
public class Multiply extends AbstractBinaryOperation {
    /* Constructor function */
    public Multiply(TripleExpression newLeft, TripleExpression newRight) {
        super(newLeft, newRight);
    } /* End of 'Multiply' function */

    /* Do integer operation function */
    protected int doOper(int left, int right) {
        return left * right;
    }
}
