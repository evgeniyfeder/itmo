package ru.itmo.ctddev.feder.expression;

/**
 * Created by dzaba on 19.03.2017.
 */
public class Variable extends AbstractExpression {
    String name;

    /* Constructor function */
    public Variable(String newName) {
        super(null, null);
        name = newName;
    } /* End of 'Const' function */

    /* Do operation function */
    protected int doOper(int left, int right) {
        return left;
    }
}
