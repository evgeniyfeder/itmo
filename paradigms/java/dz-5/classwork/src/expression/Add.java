package expression;

/* Add operation class type */
public class Add extends AbstractBinaryOperation {
    /* Constructor function */
    public Add(AnyExpression newLeft, AnyExpression newRight) {
        super(newLeft, newRight);
    } /* End of 'Const' function */

    /* Do operation with double function */
    protected strictfp double doOper(double left, double right) {
        return left + right;
    }

    /* Do operation with 2 integer function */
    protected int doOper(int left, int right) {
        return left + right;
    }
}
