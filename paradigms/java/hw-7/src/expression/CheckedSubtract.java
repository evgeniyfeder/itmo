package expression;

/* CheckedSubtract operation class type */
public class CheckedSubtract extends AbstractBinaryOperation {
    /* Constructor function */
    public CheckedSubtract(TripleExpression newLeft, TripleExpression newRight) {
        super(newLeft, newRight);
    } /* End of 'CheckedSubtract' function */

    /* Do integer operation function */
    protected int doOper(int left, int right) throws ExpressionException {
        if (left >= 0 && right < 0 && left > Integer.MAX_VALUE + right ||
                left < 0 && right >= 0 && -right < Integer.MIN_VALUE - left)
            throw new ExpressionException("Substract overflow");
        else
            return left - right;
    }
}
