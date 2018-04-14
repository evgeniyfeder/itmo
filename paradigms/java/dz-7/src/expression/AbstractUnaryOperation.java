package expression;

/* Definition of one expression class type */
public abstract class AbstractUnaryOperation implements TripleExpression {
    TripleExpression arg; /* Left and right part of expression */

    /* Standart class constructor */
    protected AbstractUnaryOperation(TripleExpression arg) {
        this.arg = arg;
    } /* End of 'AbstractBinaryOperation */

    /* Do operation with integer function */
    abstract protected int doOper(int arg) throws ExpressionException;

    /* Count expression from one integer argument */
    public int evaluate(int x, int y, int z) throws ExpressionException {
        return doOper(arg.evaluate(x, y, z));
    } /* End of 'evaluate' function */
} /* End of 'AbstractBinaryOperation' */
