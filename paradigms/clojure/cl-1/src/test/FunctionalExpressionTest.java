package test;

import expression.BaseTest;

import java.util.function.BiFunction;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class FunctionalExpressionTest extends BaseJavascriptTest<Engine> {
    public static final Dialect PURE_FUNCTIONS = dialect(
            "variable('%s')",
            "cnst(%s)",
            (op, args) -> op + "(" + String.join(", ", args) + ")"
    );
    public static final Dialect ARITHMETIC_FUNCTIONS = PURE_FUNCTIONS.clone()
            .rename("+", "add")
            .rename("-", "subtract")
            .rename("/", "divide")
            .rename("*", "multiply");

    public static final Dialect POLISH = dialect(
            "%s",
            "%s",
            (op, args) -> String.join(" ", args) + " " + op
    );

    public static class ArithmeticTests extends AbstractTests {
        protected final AbstractTests.AbstractExpression vx = variable("x", 0);
        protected final AbstractTests.AbstractExpression vy = variable("y", 1);
        protected final AbstractTests.AbstractExpression vz = variable("z", 2);

        public ArithmeticTests() {
            binary("+", (a, b) -> a + b);
            binary("-", (a, b) -> a - b);
            binary("*", (a, b) -> a * b);
            binary("/", (a, b) -> a / b);
            unary("negate", a -> -a);

            tests(
                    c(10),
                    vx,
                    vy,
                    vz,
                    f("+", vx, c(2)),
                    f("-", c(3), vy),
                    f("*", c(4), vz),
                    f("/", c(5), vz),
                    f("/", f("negate", vx), c(2)),
                    f("/", vx, f("*", vy, vz)),
                    f("+", f("+", f("*", vx, vx), f("*", vy, vy)), f("*", vz, vz)),
                    f("-", f("+", f("*", vx, vx), f("*", c(5), f("*", vz, f("*", vz, vz)))), f("*", vy, c(8)))
            );
        }
    }

    protected FunctionalExpressionTest(final Language language, final boolean testParsing) {
        super(new JSEngine("functionalExpression.js", ""), language, testParsing);
    }

    @Override
    protected String parse(final String expression) {
        return "parse('" + expression + "')";
    }

    public static void main(final String... args) {
        test(FunctionalExpressionTest.class, FunctionalExpressionTest::new, args, new ArithmeticTests());
    }

    protected static <T extends BaseTest> void test(final Class<T> type, final BiFunction<Language, Boolean, T> cons, final String[] args, final AbstractTests tests) {
        test(type, cons, tests, args, ARITHMETIC_FUNCTIONS);
    }

    protected static <T extends BaseTest> void test(final Class<T> type, final BiFunction<Language, Boolean, T> cons, final AbstractTests tests, final String[] args, final Dialect parsed) {
        cons.apply(
                new Language(parsed, POLISH, tests),
                mode(args, type, "easy", "hard") == 1
        ).run();
        System.out.println("Mode: " + args[0]);
    }
}
