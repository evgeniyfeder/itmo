package expression;

/* Definition of one expression class type */
public abstract class AbstractBinaryOperation implements TripleExpression {
    TripleExpression left, right; /* Left and right part of expression */

    /* Standart class constructor */
    protected AbstractBinaryOperation(TripleExpression newLeft, TripleExpression newRight) {
        left = newLeft;
        right = newRight;
    } /* End of 'AbstractBinaryOperation */

    /* Do operation with 2 integer function */
    abstract protected int doOper(int left, int right) throws ExpressionException;

    /* Count expression from one integer argument */
    public int evaluate(int x, int y, int z)throws ExpressionException {
        return doOper(left.evaluate(x, y, z), right.evaluate(x, y, z));
    } /* End of 'evaluate' function */
} /* End of 'AbstractBinaryOperation' */
