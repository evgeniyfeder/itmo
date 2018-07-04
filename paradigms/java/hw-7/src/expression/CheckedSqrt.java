package expression;

/* Class for negate operation function */
public class CheckedSqrt extends AbstractUnaryOperation {
    public CheckedSqrt(TripleExpression arg) {
        super(arg);
    } /* End of 'CheckedSqrt' constructor */

    /* Do operation with integer function */
    protected int doOper(int arg) throws ExpressionException {
        if (arg < 0)
            throw new ExpressionException("Sqrt argument < 0");

        int left = -1, right = 46341; // 46341 * 46341 > Integer.MAX_INT

        while (right - left > 1) {
            int middle = left + (right - left) / 2;
            if (middle * middle <= arg)
                left = middle;
            else
                right = middle;
        }

        return left;
    } /* End of 'doOper' function */
}
