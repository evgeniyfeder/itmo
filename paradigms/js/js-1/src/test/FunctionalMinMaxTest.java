package test;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class FunctionalMinMaxTest extends FunctionalPieTest {
    public static class MinMaxTests extends PieTests {{
        any("min3", 3, args -> args.stream().mapToDouble(a -> a).min().orElse(0));
        any("max5", 5, args -> args.stream().mapToDouble(a -> a).max().orElse(0));
        tests(
                f("min3", n("x"), n("y"), n("z")),
                f("max5", n("x"), n("y"), n("z"), n("pi"), n("e"))
        );
    }}

    protected FunctionalMinMaxTest(final Language language, final boolean testParsing) {
        super(language, testParsing);
    }

    public static void main(final String... args) {
        test(FunctionalMinMaxTest.class, FunctionalMinMaxTest::new, args, new MinMaxTests());
    }
}
