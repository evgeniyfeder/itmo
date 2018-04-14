package ru.itmo.ctddev.feder.expression;

/* Add operation class type */
public class Add extends AbstractExpression {
    /* Constructor function */
    public Add(Expression newLeft, Expression newRight) {
        super(newLeft, newRight);
    } /* End of 'Const' function */

    /* Do operation function */
    protected int doOper(int left, int right) {
        return left + right;
    }
}
