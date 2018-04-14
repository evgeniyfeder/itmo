package expression;

/* Class for 'abs' operation function */
public class CheckedAbsolute extends AbstractUnaryOperation {

    public CheckedAbsolute(TripleExpression arg) {
        super(arg);
    } /* End of 'Absolute' constructor */

    /* Do operation with integer function */
    protected int doOper(int arg) throws ExpressionException {
        if (arg == Integer.MIN_VALUE)
            throw new ExpressionException("Absolute function overflow");

        if (arg < 0)
            return -arg;
        return arg;
    } /* End of 'doOper' function */
}
