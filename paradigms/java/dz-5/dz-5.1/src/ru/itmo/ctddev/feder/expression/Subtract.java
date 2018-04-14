package ru.itmo.ctddev.feder.expression;

/* Substract operation class type */
public class Subtract extends AbstractExpression {
    /* Constructor function */
    public Subtract(Expression newLeft, Expression newRight) {
        super(newLeft, newRight);
    } /* End of 'Const' function */

    /* Do operation function */
    protected int doOper(int left, int right) {
        return left - right;
    }
}
