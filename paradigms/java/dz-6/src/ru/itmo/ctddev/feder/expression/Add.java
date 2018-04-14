package ru.itmo.ctddev.feder.expression;

/* Add operation class type */
public class Add extends AbstractBinaryOperation {
    /* Constructor function */
    public Add(TripleExpression newLeft, TripleExpression newRight) {
        super(newLeft, newRight);
    } /* End of 'Add' function */

    /* Do operation with 2 integer function */
    protected int doOper(int left, int right) {
        return left + right;
    }
}
