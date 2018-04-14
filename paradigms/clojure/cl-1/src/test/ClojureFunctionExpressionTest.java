package test;

import java.util.Optional;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ClojureFunctionExpressionTest extends BaseJavascriptTest<ClojureEngine> {
    public static final Dialect PARSED = dialect(
            "(variable \"%s\")",
            "(constant %s.0)",
            (op, args) -> "(" + op + " " + String.join(" ", args) + ")"
    )
            .rename("+", "add")
            .rename("-", "subtract")
            .rename("*", "multiply")
            .rename("/", "divide");

    public static final Dialect UNPARSED = dialect(
            "%s",
            "%s.0",
            (op, args) -> "("+ op + " " + String.join(" ", args) + ")"
    );

    protected ClojureFunctionExpressionTest(final Language language, final Optional<String> evaluate) {
        super(new ClojureEngine("expression.clj", evaluate), language, true);
    }

    protected ClojureFunctionExpressionTest(final AbstractTests tests) {
        this(new Language(PARSED, UNPARSED, tests), Optional.empty());
    }

    @Override
    protected String parse(final String expression) {
        return "(parseFunction \"" + expression + "\")";
    }

    public static void main(final String... args) {
        new ClojureFunctionExpressionTest(new MultiTests(mode(args, ClojureFunctionExpressionTest.class, "easy", "hard") == 1)).test();
    }
}
