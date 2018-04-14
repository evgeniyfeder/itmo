package expression;

/* CheckedMultiply operation class type */
public class CheckedMultiply extends AbstractBinaryOperation {
    /* Constructor function */
    public CheckedMultiply(TripleExpression newLeft, TripleExpression newRight) {
        super(newLeft, newRight);
    } /* End of 'CheckedMultiply' function */

    /* Do integer operation function */
    protected int doOper(int left, int right) throws ExpressionException {
        if (left > 0 && right > 0 && left > Integer.MAX_VALUE / right ||
                left > 0 && right < 0 && right < Integer.MIN_VALUE / left ||
                left < 0 && right > 0 && left < Integer.MIN_VALUE / right ||
                left < 0 && right < 0 && left < Integer.MAX_VALUE / right) {
            throw new ExpressionException("Multiply overflow");
        } else {
            return left * right;
        }
    }
}
