package expression;

/* Class for negate operation function */
public class CheckedNegate extends AbstractUnaryOperation {
    public CheckedNegate(TripleExpression arg) {
        super(arg);
    } /* End of 'CheckedNegate' constructor */

    /* Do operation with integer function */
    protected int doOper(int arg) throws ExpressionException {
        if (arg == Integer.MIN_VALUE) {
            throw new ExpressionException("Negate overflow");
        }
        return -arg;
    } /* End of 'doOper' function */
}
