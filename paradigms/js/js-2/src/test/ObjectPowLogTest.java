package test;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ObjectPowLogTest extends ObjectExpressionTest {
    public static final Dialect POW_LOG_OBJECT = ObjectExpressionTest.ARITHMETIC_OBJECT.clone()
            .rename("pow", "Power")
            .rename("log", "Log");

    public static class PowLogTests extends FunctionalExpressionTest.ArithmeticTests {{
        binary("pow", Math::pow);
        binary("log", (a, b) -> Math.log(Math.abs(b)) / Math.log(Math.abs(a)));
        tests(
                f("pow", vx, vy),
                f("log", vx, vy),
                f("pow", vx, f("-", vy, vz)),
                f("log", f("-", vx, vz), f("-", vy, vz))
        );
    }}

    protected ObjectPowLogTest(final int mode, final Language language) {
        super(mode, language);
    }

    public static void main(final String... args) {
        test(ObjectPowLogTest.class, ObjectPowLogTest::new, new PowLogTests(), new String[]{"easy"}, POW_LOG_OBJECT);
    }
}
