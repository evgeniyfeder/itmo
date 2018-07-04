package expression.exceptions;
import expression.*;

/**
 * Created by Evgeniy on 29.03.2017.
 */
public class ExpressionParser implements Parser {
    Tokenizer token = new Tokenizer();

    /* Parse expression */
    public TripleExpression parse(String expr) throws ParseException {
        token.setStr(expr);
        if (!token.nextUnary())
            return null;

        TripleExpression resultExpr = parseMinMax(false);

        if (token.curToken == Tokenizer.Token.RP) {
            throw new ParseException("No opening parenthesis at position " + token.getCurIndex() + token.getErrorString(token.getCurIndex()));
        } else if (token.curToken != Tokenizer.Token.END) {
            throw new ParseException("Unexpected end of expression.");
        }

        return resultExpr;
    } /* End of 'parse' function */

    /* Parse min and max expression token */
    private TripleExpression parseMinMax(boolean isNotFirstRead) throws ParseException {
        TripleExpression leftExpr = parseAddSub(isNotFirstRead);

        while (true) {
            if (token.curToken != Tokenizer.Token.NAME) {
                return leftExpr;
            } if (token.curToken.str.compareTo("min") == 0) {
                leftExpr = new CheckedMin(leftExpr, parseAddSub(true));
            } else if (token.curToken.str.compareTo("max") == 0) {
                leftExpr = new CheckedMax(leftExpr, parseAddSub(true));
            } else {
                return leftExpr;
            }
        }
    } /* End of 'parseFirstPriority' function */

    /* Parse add and sub expression token */
    private TripleExpression parseAddSub(boolean isNotFirstRead) throws ParseException {
        TripleExpression leftExpr = parseMulDiv(isNotFirstRead);

        while (true) {
            switch (token.curToken) {
                case PLUS:
                    leftExpr = new CheckedAdd(leftExpr, parseMulDiv(true));
                    break;
                case MINUS:
                    leftExpr = new CheckedSubtract(leftExpr, parseMulDiv(true));
                    break;
                default:
                    return leftExpr;
            }
        }
    } /* End of 'parseFirstPriority' function */

    /* Parse second priority operation */
    private TripleExpression parseMulDiv(boolean isNotFirstRead) throws ParseException {
        TripleExpression leftExpr = parseUnary(isNotFirstRead);

        while (true) {
            switch (token.curToken) {
                case MUL:
                    leftExpr = new CheckedMultiply(leftExpr, parseUnary(true));
                    break;
                case DIV:
                    leftExpr = new CheckedDivide(leftExpr, parseUnary(true));
                    break;
                default:
                    return leftExpr;
            }
        }
    } /* End of 'parseMulDiv' function */

    /* Parse unary opearations */
    private TripleExpression parseUnary(boolean isNotFirstRead) throws ParseException {
        if (isNotFirstRead)
            token.nextUnary();

        switch (token.curToken) {
            case NUMBER:
                TripleExpression result;
                try {
                    result = new Const(Integer.parseInt(token.curToken.str));
                } catch (NumberFormatException e) {
                    throw new ParseException("Overflow constant " + token.curToken.str + " in place " + token.getCurIndex() + token.getErrorString(token.getCurIndex()));
                }
                token.nextBinary();
                return result;
            case MINUS:
                return new CheckedNegate(parseUnary(true));
            case RP:
                throw new ParseException("Empty brackets ends in index " + token.getCurIndex() + token.getErrorString(token.getCurIndex()));
            case LP:
                int lpIndex = token.getCurIndex();
                result = parseMinMax(true);
                if (token.curToken != Tokenizer.Token.RP)
                    throw new ParseException("No closing parenthesis with opening parenthesis in " + lpIndex + token.getErrorString(lpIndex));
                token.nextBinary();
                return result;
            case NAME:
                switch (token.curToken.str) {
                    case "abs":
                        return new CheckedAbsolute(parseUnary(true));
                    case "sqrt":
                        return new CheckedSqrt(parseUnary(true));
                    case "x":
                    case "y":
                    case "z":
                        TripleExpression res = new Variable(token.curToken.str);
                        token.nextBinary();
                        return res;
                }
        }
        return null;
    } /* End of 'parseUnary' function */

}
