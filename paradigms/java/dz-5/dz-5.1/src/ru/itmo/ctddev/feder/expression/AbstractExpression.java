package ru.itmo.ctddev.feder.expression;

/* Definition of one expression class type */
public abstract class AbstractExpression implements Expression {
    Expression left, right; /* Left and right part of expression */

    /* Standart class constructor */
    protected AbstractExpression(Expression newLeft, Expression newRight) {
        left = newLeft;
        right = newRight;
    } /* End of 'AbstractExpression */

    /* Do operation function */
    abstract protected int doOper(int left, int right);

    /* Count expression from one integer argument */
    public int evaluate(int x) {
        if (left != null && right != null)
            return doOper(left.evaluate(x), right.evaluate(x));
        else
            return doOper(x, 0);
    } /* End of 'evaluate' function */
}
