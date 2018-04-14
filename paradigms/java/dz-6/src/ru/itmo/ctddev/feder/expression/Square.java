package ru.itmo.ctddev.feder.expression;

/* Class for 'square' operation function */
public class Square extends AbstractUnaryOperation {

    public Square(TripleExpression arg) {
        super(arg);
    } /* End of 'Square' constructor */

    /* Do operation with integer function */
    protected int doOper(int arg) {
        return arg * arg;
    } /* End of 'doOper' function */
}
