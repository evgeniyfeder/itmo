package test;

import java.util.function.IntConsumer;
import java.util.stream.IntStream;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class FunctionalVariablesTest extends FunctionalExpressionTest {
    public static class VariablesTests extends ArithmeticTests {
        protected final AbstractTests.AbstractExpression vu = variable("u", 3);
        protected final AbstractTests.AbstractExpression vv = variable("v", 4);
        protected final AbstractTests.AbstractExpression vw = variable("w", 5);

        VariablesTests() {
            tests(
                    vu,
                    vv,
                    vw,
                    f("*", vu, f("+", vw, vw))
            );
        }
    }

    public static final int N = 3;

    protected void test(final TExpr f) {
        loop(x ->
                loop(y ->
                        loop(z ->
                                loop(u ->
                                        loop(v ->
                                                loop(w -> {
                                                    final double[] vars = new double[]{x, y, z, u, v, w};
                                                    evaluate(vars, f.evaluate(vars), EPS);
                                                })
                                        )
                                )
                        )
                )
        );
    }

    protected void loop(final IntConsumer c) {
        IntStream.range(0, N).forEach(c);
    }

    protected FunctionalVariablesTest(final Language language, final boolean testParsing) {
        super(language, testParsing);
    }

    public static void main(final String... args) {
        test(FunctionalVariablesTest.class, FunctionalVariablesTest::new, args, new VariablesTests());
    }
}
