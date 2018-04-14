package expression;

/* Definition of one expression class type */
public abstract class AbstractBinaryOperation implements AnyExpression {
    AnyExpression left, right; /* Left and right part of expression */

    /* Standart class constructor */
    protected AbstractBinaryOperation(AnyExpression newLeft, AnyExpression newRight) {
        left = newLeft;
        right = newRight;
    } /* End of 'AbstractBinaryOperation */

    /* Do operation with double function */
    abstract protected double doOper(double left, double right);

    /* Do operation with 2 integer function */
    abstract protected int doOper(int left, int right);

    /* Count expression from one integer argument */
    public int evaluate(int x, int y, int z) {
        return doOper(left.evaluate(x, y, z), right.evaluate(x, y, z));
    } /* End of 'evaluate' function */

    /* Count expression from one integer argument */
    public int evaluate(int x) {
        return doOper(left.evaluate(x), right.evaluate(x));
    } /* End of 'evaluate' function */

    /* Count expression from one integer argument */
    public strictfp double evaluate(double x) {
        return doOper(left.evaluate(x), right.evaluate(x));
    } /* End of 'evaluate' function */
} /* End of 'AbstractBinaryOperation' */
