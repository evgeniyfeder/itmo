package expression;

/**
 * Created by dzaba on 19.03.2017.
 */
public class Variable implements AnyExpression {
    String name;

    /* Constructor function */
    public Variable(String newName) {
        name = newName;
    } /* End of 'Const' function */

    /* Count expression from one double argument */
    public strictfp double evaluate(double x) {
        return x;
    } /* End of 'evaluate' function */

    /* Count expression from one integer argument */
    public int evaluate(int x) {
        return x;
    } /* End of 'evaluate' function */

    /* Count expression from one integer argument */
    public int evaluate(int x, int y, int z) {
        if (name.contentEquals("x"))
            return x;
        else if (name.contentEquals("y"))
            return y;
        else
            return z;
    } /* End of 'evaluate' function */
}
