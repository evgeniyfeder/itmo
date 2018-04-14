package test;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ClojureFunctionSquareTest extends ClojureFunctionExpressionTest {
    protected ClojureFunctionSquareTest(final boolean testMulti) {
        super(new MultiSquareTests(testMulti));
    }

    public static void main(final String... args) {
        new ClojureFunctionSquareTest(mode(args, ClojureFunctionSquareTest.class, "easy", "hard") == 1).test();
    }
}
