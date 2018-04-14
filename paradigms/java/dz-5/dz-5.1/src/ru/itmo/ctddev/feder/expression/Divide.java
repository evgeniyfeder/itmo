package ru.itmo.ctddev.feder.expression;

/* Divide operation class type */
public class Divide extends AbstractExpression {
    /* Constructor function */
    public Divide(Expression newLeft, Expression newRight) {
        super(newLeft, newRight);
    } /* End of 'Const' function */

    /* Do operation function */
    protected int doOper(int left, int right) {
        return left / right;
    }
}
