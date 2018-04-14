package expression;

/* Multiply operation class type */
public class Multiply extends AbstractBinaryOperation {
    /* Constructor function */
    public Multiply(AnyExpression newLeft, AnyExpression newRight) {
        super(newLeft, newRight);
    } /* End of 'Const' function */

    /* Do integer operation function */
    protected int doOper(int left, int right) {
        return left * right;
    }

    /* Do double operation function */
    protected strictfp double doOper(double left, double right) {
        return left * right;
    }
}
