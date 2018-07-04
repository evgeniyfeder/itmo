package ru.itmo.ctddev.feder.expression;

/* Right shift operation class type */
public class RightShift extends AbstractBinaryOperation {
    /* Constructor function */
    public RightShift(TripleExpression newLeft, TripleExpression newRight) {
        super(newLeft, newRight);
    } /* End of 'RightShift' function */

    /* Do operation with 2 integer function */
    protected int doOper(int left, int right) {
        return left >> right;
    }
}
