package expression;

/* Add operation class type */
public class CheckedAdd extends AbstractBinaryOperation {
    /* Constructor function */
    public CheckedAdd(TripleExpression newLeft, TripleExpression newRight) {
        super(newLeft, newRight);
    } /* End of 'Add' function */

    /* Do operation with 2 integer function */
    protected int doOper(int left, int right) throws ExpressionException {
        if (left > 0 && right > Integer.MAX_VALUE - left ||
                left < 0 && right < Integer.MIN_VALUE - left) {
            throw new ExpressionException("Summary overflow");
        } else {
            return left + right;
        }
    }
}
