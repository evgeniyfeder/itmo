package expression;

/* Divide operation class type */
public class CheckedDivide extends AbstractBinaryOperation {
    /* Constructor function */
    public CheckedDivide(TripleExpression newLeft, TripleExpression newRight) {
        super(newLeft, newRight);
    } /* End of 'Divide' function */

    /* Do integer operation function */
    protected int doOper(int left, int right) throws ExpressionException {
        if (left == Integer.MIN_VALUE && right == -1) {
            throw new ExpressionException("Divide overflow");
        } else {
            return left / right;
        }
    }
}
