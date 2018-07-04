package ru.itmo.ctddev.feder.expression;

/* Class for 'abs' operation function */
public class Absolute extends AbstractUnaryOperation {

    public Absolute(TripleExpression arg) {
        super(arg);
    } /* End of 'Absolute' constructor */

    /* Do operation with integer function */
    protected int doOper(int arg) {
        return Math.abs(arg);
    } /* End of 'doOper' function */
}
