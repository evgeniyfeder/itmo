package test;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class PrefixParserTest extends ObjectExpressionTest {
    public static final String INSERTIONS = "xyz()+*/@ABC";
    public static final Dialect PREFIX = dialect(
            "%s",
            "%s",
            (op, args) -> "(" + op + " " + String.join(" ", args) + ")"
    );

    public PrefixParserTest(final int mode, final Language language, final String toString) {
        super(mode, language);
        engine.toStringMethod = toString;
    }

    @Override
    protected String parse(final String expression) {
        return "parsePrefix('" + expression + "')";
    }

    @Override
    protected void test(final String parsed, final String unparsed) {
        super.test(parsed, unparsed);
        super.test(removeSpaces(parsed), unparsed);

        for (int i = 0; i < 1 + Math.min(10, 200 / unparsed.length()); i++) {
            final int index = randomInt(unparsed.length());
            final char c = unparsed.charAt(index);
            if (!Character.isDigit(c) && !Character.isWhitespace(c) && c != '-'){
                assertParsingError(unparsed.substring(0, index), "<SYMBOL REMOVED>", unparsed.substring(index + 1));
            }
            final char newC = INSERTIONS.charAt(randomInt(INSERTIONS.length()));
            if (!Character.isDigit(c) && c != '-') {
                assertParsingError(unparsed.substring(0, index), "<SYMBOL INSERTED -->", newC + unparsed.substring(index));
            }
        }
    }

    private String removeSpaces(final String expression) {
        return expression.replace(" (", "(").replace(") ", ")");
    }

    protected String assertParsingError(final String prefix, final String comment, final String suffix) {
        try {
            engine.parse(parse(prefix + suffix));
            throw new AssertionError("Parsing error expected for " + prefix + comment + suffix);
        } catch (final EngineException e) {
            return e.getCause().getMessage();
        }
    }

    public static void main(final String... args) {
        test(PrefixParserTest.class, new FunctionalExpressionTest.ArithmeticTests(), args, ARITHMETIC_OBJECT);
    }

    public static void test(final Class<?> type, final AbstractTests tests, final String[] args, final Dialect parsed) {
        final int mode = mode(args, type, "easy", "hard");
        new PrefixParserTest(mode, new Language(parsed, PREFIX, tests), "prefix").run();
    }
}
