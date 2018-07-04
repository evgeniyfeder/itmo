package expression;

/* Add operation class type */
public class CheckedMax extends AbstractBinaryOperation {
    /* Constructor function */
    public CheckedMax(TripleExpression newLeft, TripleExpression newRight) {
        super(newLeft, newRight);
    } /* End of 'CheckedMax' function */

    /* Do operation with 2 integer function */
    protected int doOper(int left, int right) throws ExpressionException {
        if (left > right)
            return left;
        return right;
    }
}
