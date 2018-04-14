package test;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class PrefixSinCosTest extends PrefixParserTest {
    public static final Dialect SIN_COS_OBJECT = ObjectExpressionTest.ARITHMETIC_OBJECT.clone()
            .rename("sin", "Sin")
            .rename("cos", "Cos");

    public static class SinCosTests extends FunctionalExpressionTest.ArithmeticTests {{
        unary("sin", Math::sin);
        unary("cos", Math::cos);
        tests(
                f("sin", f("-", vx, vy)),
                f("cos", f("+", vx, vy)),
                f("cos", f("/", f("sin", vz), f("+", vx, vy))),
                f("+", f("cos", f("sin", f("+", vx, c(10)))), f("*", vz, f("*", vy, f("cos", c(0)))))
        );
    }}

    protected PrefixSinCosTest(final int mode, final Language language, final String toString) {
        super(mode, language, toString);
    }

    @Override
    protected void test() {
        super.test();

        testParsing();
    }

    protected void testParsing() {
        printParsingError("Empty input", "");
        printParsingError("Unknown variable", "a");
        printParsingError("Unknown variable 2", "(+ xy zx)");
        printParsingError("Invalid number 1", "-a");
        printParsingError("Invalid number 2", "+3");
        printParsingError("Invalid number 3", "--3");
        printParsingError("Missing )", "(* z (+ x y)");
        printParsingError("Unknown operation", "(@@  x y)");
        printParsingError("Excessive info", "(+ x y) x");
        printParsingError("Empty op", "()");
        printParsingError("Invalid unary (0 args)", "(negate)");
        printParsingError("Invalid unary (2 args)", "(negate x y)");
        printParsingError("Invalid binary (0 args)", "(+)");
        printParsingError("Invalid binary (1 args)", "(+ x)");
        printParsingError("Invalid binary (3 args)", "(+ x y z)");
        printParsingError("Variable op (0 args)", "(x)");
        printParsingError("Variable op (1 args)", "(x 1)");
        printParsingError("Variable op (2 args)", "(x 1 2)");
        printParsingError("Const op (0 args)", "(0)");
        printParsingError("Const op (1 args)", "(0 1)");
        printParsingError("Const op (2 args)", "(0 1 2)");
    }

    private void printParsingError(final String description, final String input) {
        final String message = assertParsingError(input, "", "");
        final int index = message.lastIndexOf("in <eval>");
        ops(input.length());
        System.out.format("%-25s: %s\n", description, message.substring(0, index > 0 ? index : message.length()));
    }

    public static void main(final String... args) {
        test(PrefixSinCosTest.class, PrefixSinCosTest::new, new SinCosTests(), args, SIN_COS_OBJECT, "prefix");
    }
}
