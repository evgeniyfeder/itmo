package test;

import test.BaseJavascriptTest.Expr;
import test.BaseJavascriptTest.TExpr;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class Language {
    private final BaseJavascriptTest.Dialect parsed;
    private final BaseJavascriptTest.Dialect unparsed;

    protected AbstractTests abstractTests;

    protected List<Expr<TExpr>> tests = new ArrayList<>();

    public Language(final BaseJavascriptTest.Dialect parsed, final BaseJavascriptTest.Dialect unparsed, final AbstractTests tests) {
        this.parsed = parsed;
        this.unparsed = unparsed;

        abstractTests = tests;
        this.tests.addAll(tests.renderTests(parsed, unparsed));
    }

    private boolean safe(final char ch) {
        return !Character.isLetterOrDigit(ch) && "+-*/.".indexOf(ch) == -1;
    }

    protected String addSpaces(final String expression, final Random random) {
        String spaced = expression;
        for (int n = StrictMath.min(10, 200 / expression.length()); n > 0;) {
            final int index = random.nextInt(spaced.length() + 1);
            final char c = index == 0 ? 0 : spaced.charAt(index - 1);
            final char nc = index == spaced.length() ? 0 : spaced.charAt(index);
            if ((safe(c) || safe(nc)) && c != '\'' && nc != '\'' && c != '"' && nc != '"') {
                spaced = spaced.substring(0, index) + " " + spaced.substring(index);
                n--;
            }
        }
        return spaced;
    }

    public Expr<TExpr> randomTest(final Random random, final int size) {
        return abstractTests.randomTest(random, size, parsed, unparsed);
    }
}
