package ru.itmo.ctddev.feder.parser;
import ru.itmo.ctddev.feder.expression.*;

/**
 * Created by Evgeniy on 29.03.2017.
 */
public class ExpressionParser implements Parser {
    int curIndString = 0;
    String curToken;

    /* Read number in string function */
    private void readNumber(String str) {
        int endInd = curIndString + 1;
        while (endInd < str.length() && Character.isDigit(str.charAt(endInd)))
            endInd++;
        curToken = str.substring(curIndString, endInd);
        curIndString = endInd;
    } /* End of 'readNumber' function */

    /*** Fill enumeration types ***/
    /* Get expression class by string function */
    private boolean parseToken(String str) {
        /* Skip spaces */
        while (curIndString < str.length() && Character.isWhitespace(str.charAt(curIndString)))
            curIndString++;

        /* If It's end */
        if (curIndString == str.length()) {
            curToken = "\0";
            return false;
        }

        char beginSym = str.charAt(curIndString);
        switch (beginSym) {
            case '+':
            case '*':
            case '/':
            case '(':
            case ')':
            case '-':
                curIndString++;
                curToken = new String(String.valueOf(beginSym));
                return true;
            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                readNumber(str);
                return true;
            default:
                if (Character.isAlphabetic(beginSym)) {
                    int endInd = curIndString;
                    while (endInd < str.length() &&
                            (Character.isAlphabetic(str.charAt(endInd)) || Character.isDigit(str.charAt(endInd))))
                        endInd++;

                    String name = str.substring(curIndString, endInd);
                    switch(name) {
                        case "abs":
                        case "square":
                        case "x":
                        case "y":
                        case "z":
                            curIndString = endInd;
                            curToken = name;
                            return true;
                        default:
                            curToken = "unknown";
                            return true;
                    }

                } else if (beginSym == '<' && curIndString + 1 < str.length()
                        && str.charAt(curIndString + 1) == '<') {
                    curIndString += 2;
                    curToken = "<<";
                    break;
                } else if (beginSym == '>' && curIndString + 1 < str.length()
                        && str.charAt(curIndString + 1) == '>') {
                    curIndString += 2;
                    curToken = ">>";
                } else {
                    curToken = "unknown";
                }
        }
        return true;
    } /* End of 'getExprByStr' function */

    /* Parse expression */
    public TripleExpression parse(String expr) {
        curIndString = 0;
        if (!parseToken(expr))
            return null;

        TripleExpression resultExpr = parseShifts(expr, false);
        return resultExpr;
    } /* End of 'parse' function */

    /* Parse shifts expression token */
    private  TripleExpression parseShifts(String expr, boolean isNotFirstRead) {
        TripleExpression leftExpr = parseAddSub(expr, isNotFirstRead);

        while (true) {
            switch (curToken) {
                case ">>":
                    leftExpr = new RightShift(leftExpr, parseAddSub(expr, true));
                    break;
                case "<<":
                    leftExpr = new LeftShift(leftExpr, parseAddSub(expr, true));
                    break;
                default:
                    return leftExpr;
            }
        }
    } /* End of 'ParseShifts' function */

    /* Parse add and sub expression token */
    private TripleExpression parseAddSub(String expr, boolean isNotFirstRead) {
        TripleExpression leftExpr = parseMulDiv(expr, isNotFirstRead);

        while (true) {
            switch (curToken) {
                case "+":
                    leftExpr = new Add(leftExpr, parseMulDiv(expr, true));
                    break;
                case "-":
                    leftExpr = new Subtract(leftExpr, parseMulDiv(expr, true));
                    break;
                default:
                    return leftExpr;
            }
        }
    } /* End of 'parseFirstPriority' function */

    /* Parse second priority operation */
    private TripleExpression parseMulDiv(String expr, boolean isNotFirstRead) {
        TripleExpression leftExpr = parseUnary(expr, isNotFirstRead);

        while (true) {
            switch (curToken) {
                case "*":
                    leftExpr = new Multiply(leftExpr, parseUnary(expr, true));
                    break;
                case "/":
                    leftExpr = new Divide(leftExpr, parseUnary(expr, true));
                    break;
                default:
                    return leftExpr;
            }
        }
    } /* End of 'parseMulDiv' function */

    /* Parse unary opearations */
    private TripleExpression parseUnary(String expr, boolean isNotFirstRead) {
        if (isNotFirstRead)
            parseToken(expr);

        if (Character.isDigit(curToken.charAt(0))) {
            TripleExpression result = new Const(Integer.parseUnsignedInt(curToken));
            parseToken(expr);
            return result;
        }
        switch (curToken) {
            case "-":
                return new Subtract(new Const(0), parseUnary(expr, true));
            case "(":
                TripleExpression result = parseShifts(expr, true);
                if (curToken != ")")
                    curToken = "undefined";
                parseToken(expr);
                return result;
            case "abs":
                return new Absolute(parseUnary(expr, true));
            case "square":
                return new Square(parseUnary(expr, true));
            case "x":
            case "y":
            case "z":
                TripleExpression res = new Variable(curToken);
                parseToken(expr);
                return res;
            default:
                curToken = "undefinded";
                return null;
        }
    } /* End of 'parseUnary' function */

}
