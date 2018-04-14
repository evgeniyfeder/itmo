package test;

/**
 * @author Georgiy Korneev (kgeorgiy@kgeorgiy.info)
 */
public class ObjectSinhCoshTest extends ObjectExpressionTest {
    public static final Dialect SINH_COSH_OBJECT = ObjectExpressionTest.ARITHMETIC_OBJECT.clone()
            .rename("sinh", "Sinh")
            .rename("cosh", "Cosh");

    public static class SinhCoshTests extends FunctionalExpressionTest.ArithmeticTests {{
        unary("sinh", Math::sinh);
        unary("cosh", Math::cosh);
        tests(
                f("sinh", f("-", vx, vy)),
                f("cosh", f("+", vx, vy)),
                f("cosh", f("/", f("sinh", vz), f("+", vx, vy))),
                f("+", vx, f("cosh", f("sinh", c(2)))),
                f("+", f("cosh", f("sinh", f("-", vx, c(3)))), f("*", vz, f("*", vy, f("cosh", c(0)))))
        );
    }}

    protected ObjectSinhCoshTest(final int mode, final Language language) {
        super(mode, language);
        simplifications.addAll(list(
                new int[]{10, 15, 1},
                new int[]{10, 10, 1},
                new int[]{51, 51, 52},
                new int[]{1, 1, 1},
                new int[]{28, 1, 1}
        ));
    }

    public static void main(final String... args) {
        test(ObjectSinhCoshTest.class, ObjectSinhCoshTest::new, new SinhCoshTests(), args, SINH_COSH_OBJECT);
    }
}
