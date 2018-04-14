package ru.itmo.ctddev.feder.expression;

/* Multiply operation class type */
public class Multiply extends AbstractExpression {
    /* Constructor function */
    public Multiply(Expression newLeft, Expression newRight) {
        super(newLeft, newRight);
    } /* End of 'Const' function */

    /* Do operation function */
    protected int doOper(int left, int right) {
        return left * right;
    }
}
