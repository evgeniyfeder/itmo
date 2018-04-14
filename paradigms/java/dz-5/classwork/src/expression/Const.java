package expression;

/**
 * Created by dzaba on 19.03.2017.
 */
public strictfp class Const implements AnyExpression {
    private final double value;

    /* Constructor function */
    public Const(double newValue) {
        value = newValue;
    } /* End of 'Const' function */

    /* Constructor function */
    public Const(int newValue) {
        value = newValue;
    } /* End of 'Const' function */

    /* Count expression from one double argument */
    public strictfp double evaluate(double x) {
        return value;
    } /* End of 'evaluate' function */

    /* Count expression from one integer argument */
    public int evaluate(int x) {
        return (int)value;
    } /* End of 'evaluate' function */

    /* Count expression from one integer argument */
    public int evaluate(int x, int y, int z) {
        return (int)value;
    } /* End of 'evaluate' function */
}
