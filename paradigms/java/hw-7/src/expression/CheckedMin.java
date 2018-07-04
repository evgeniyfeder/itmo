package expression;

/* Add operation class type */
public class CheckedMin extends AbstractBinaryOperation {
    /* Constructor function */
    public CheckedMin(TripleExpression newLeft, TripleExpression newRight) {
        super(newLeft, newRight);
    } /* End of 'CheckedMin' function */

    /* Do operation with 2 integer function */
    protected int doOper(int left, int right) throws ExpressionException {
        if (left < right)
            return left;
        return right;
    }
}
