package expression;

/* Substract operation class type */
public class Subtract extends AbstractBinaryOperation {
    /* Constructor function */
    public Subtract(AnyExpression newLeft, AnyExpression newRight) {
        super(newLeft, newRight);
    } /* End of 'Const' function */

    /* Do integer operation function */
    protected int doOper(int left, int right) {
        return left - right;
    }

    /* Do double operation function */
    protected strictfp double doOper(double left, double right) {
        return left - right;
    }
}
