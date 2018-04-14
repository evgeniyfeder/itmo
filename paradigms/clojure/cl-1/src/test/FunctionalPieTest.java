package test;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class FunctionalPieTest extends FunctionalExpressionTest {
    public static class PieTests extends ArithmeticTests {{
        nullary("pi", vars -> Math.PI);
        nullary("e", vars -> Math.E);
        nullary("x", vars -> vars[0]);
        nullary("y", vars -> vars[1]);
        nullary("z", vars -> vars[2]);
        tests(
                f("+", n("pi"), vx),
                f("-", vy, n("e")),
                f("*", n("x"), n("y")),
                f("/", n("y"), n("z"))
        );
    }}

    protected FunctionalPieTest(final Language language, final boolean testParsing) {
        super(language, testParsing);
    }

    public static void main(final String... args) {
        test(FunctionalPieTest.class, FunctionalPieTest::new, args, new PieTests());
    }
}
