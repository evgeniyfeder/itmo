package test;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ClojureFunctionSinhCoshTest extends ClojureFunctionExpressionTest {
    protected ClojureFunctionSinhCoshTest(final boolean testMulti) {
        super(new MultiSinhCoshTests(testMulti));
    }

    public static void main(final String... args) {
        new ClojureFunctionSinhCoshTest(mode(args, ClojureFunctionSinhCoshTest.class, "easy", "hard") == 1).test();
    }
}
