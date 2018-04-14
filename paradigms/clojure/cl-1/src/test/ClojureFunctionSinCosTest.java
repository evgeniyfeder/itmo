package test;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ClojureFunctionSinCosTest extends ClojureFunctionExpressionTest {
    protected ClojureFunctionSinCosTest(final boolean testMulti) {
        super(new MultiSinCosTests(testMulti));
    }

    public static void main(final String... args) {
        new ClojureFunctionSinCosTest(mode(args, ClojureFunctionSinCosTest.class, "easy", "hard") == 1).test();
    }
}
