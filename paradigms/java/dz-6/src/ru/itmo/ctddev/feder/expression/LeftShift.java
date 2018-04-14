package ru.itmo.ctddev.feder.expression;

/* Left shift operation class type */
public class LeftShift extends AbstractBinaryOperation {
    /* Constructor function */
    public LeftShift(TripleExpression newLeft, TripleExpression newRight) {
        super(newLeft, newRight);
    } /* End of 'LeftShift' function */

    /* Do operation with 2 integer function */
    protected int doOper(int left, int right) {
        return left << right;
    }
}
