package expression.exceptions;

import expression.exceptions.ParseException;

/* Tokenizer class */
public class Tokenizer {
    /* Enumerator of tokenizer operations */
    public enum Token {
        ERROR("unknown", false), END("\n", true), NAME("", false), NUMBER("", false),
        PLUS("+", true), MINUS("-", true), MUL("*", true), DIV("\\", true), LP("(", false), RP(")", true);

        public String str;
        public boolean isBinary;
        /* Token operation constructor */
        Token(String str, boolean isBinary) {
            this.str = str;
            this.isBinary = isBinary;
        }
    }; /* End of 'tokens' enumerator */

    public Token curToken;

    private String inputStr;
    private int curIndString = 0;

    public String getInputStr() {
        return inputStr;
    }

    /* Get nice string interpretation */
    String getErrorString(int index) {
        StringBuilder sb = new StringBuilder();
        sb.append('\n' + inputStr + '\n');
        for (int i = 1; i < index; i++) {
            sb.append(' ');
        }
        sb.append('^');
        return sb.toString();
    }

    /* Set String to create token */
    public void setStr(String str) {
        inputStr = str;
        curIndString = 0;
    }

    public int getCurIndex() {
        return curIndString + 1 - curToken.str.length();
    }

    /* Read number in string function */
    private void readNumber() {
        int endInd = curIndString + 1;
        while (endInd < inputStr.length() && Character.isDigit(inputStr.charAt(endInd)))
            endInd++;
        curToken = Token.NUMBER;
        curToken.str = inputStr.substring(curIndString, endInd);
        curIndString = endInd;
    } /* End of 'readNumber' function */

    /* Set operation function */
    private void setEnumOper(char symbol) {
        switch (symbol) {
            case '+':
                curToken = Token.PLUS;
                break;
            case '-':
                curToken = Token.MINUS;
                break;
            case '*':
                curToken = Token.MUL;
                break;
            case '/':
                curToken = Token.DIV;
                break;
            case '(':
                curToken = Token.LP;
                break;
            case ')':
                curToken = Token.RP;
                break;
        }
    }

    /* Get name */
    String readName() {
        int endInd = curIndString;
        while (endInd < inputStr.length() &&
                (Character.isAlphabetic(inputStr.charAt(endInd)) || Character.isDigit(inputStr.charAt(endInd))))
            endInd++;

        String result = inputStr.substring(curIndString, endInd);
        curIndString = endInd;
        return result;
    }
    /*** Fill enumeration types ***/
    /* Get next binary token */
    public boolean nextBinary() throws ParseException {
        /* Skip spaces */
        while (curIndString < inputStr.length() && Character.isWhitespace(inputStr.charAt(curIndString)))
            curIndString++;

        /* If It's end */
        if (curIndString == inputStr.length()) {
            curToken = Token.END;
            return false;
        }

        char beginSym = inputStr.charAt(curIndString);
        switch (beginSym) {
            case '+':
            case '*':
            case '/':
            case '-':
            case ')':
                curIndString++;
                setEnumOper(beginSym);
                break;
            default:
                if (Character.isAlphabetic(beginSym)) {
                    String name = readName();
                    switch (name) {
                        case "min":
                        case "max":
                            curToken = Token.NAME;
                            curToken.str = name;
                            break;
                        default:
                            throw new ParseException("Waiting binary operation. Unknown name '" + name + "' at position "
                                    + (curIndString + 1 - name.length()) + getErrorString(curIndString + 1 - name.length()));
                    }
                } else {
                    /* ERROR */
                    throw new ParseException("Waiting binary operation. Unknown symbol '" + beginSym + "' at position " + (curIndString));
                }
        }
        return true;
    }

    /* Get next unary operation function */
    public boolean nextUnary() throws ParseException {
        /* Skip spaces */
        while (curIndString < inputStr.length() && Character.isWhitespace(inputStr.charAt(curIndString)))
            curIndString++;

        /* If It's end */
        if (curIndString == inputStr.length()) {
            curToken = Token.ERROR;
            return false;
        }

        char beginSym = inputStr.charAt(curIndString);
        switch (beginSym) {
            case ')':
                if (curToken.isBinary)
                    throw new ParseException("Waiting unary operation. Nothing before ')' at index "+ (curIndString + 1) + getErrorString(curIndString + 1));
            case '(':
                curIndString++;
                setEnumOper(beginSym);
                break;
            case '-':
                if (curIndString + 1 < inputStr.length() && !Character.isDigit(inputStr.charAt(curIndString + 1))) {
                    curIndString++;
                    curToken = Token.MINUS;
                    return true;
                }
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
                readNumber();
                break;
            default:
                if (Character.isAlphabetic(beginSym)) {
                    String name = readName();
                    switch(name) {
                        case "abs":
                        case "sqrt":
                        case "x":
                        case "y":
                        case "z":
                            curToken = Token.NAME;
                            curToken.str = name;
                            break;
                        default:
                            throw new ParseException("Waiting unary operation. Unknown name '" + name + "' at position " + (curIndString + 1 - name.length()) + getErrorString(curIndString + 1 - name.length()));
                    }
                } else {
                    throw new ParseException("Waiting unary symbol. Unknown symbol '" + beginSym + "' at position " + (curIndString) + getErrorString(curIndString));
                }
        }
        return true;
    }
} /* End of 'Tokenizer' class */
