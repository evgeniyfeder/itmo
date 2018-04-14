/* Operation class implementation */
function Operation() {
    this.operands = arguments;
}

Operation.prototype.evaluate = function () {
    var operResult = [];
    for (var i = 0; i < this.operands.length; i++) {
        operResult.push(this.operands[i].evaluate.apply(this.operands[i], arguments));
    }
    return this.count.apply(null, operResult);
};

Operation.prototype.diff = function (name) {
    var operResult = [];
    for (var i = 0; i < this.operands.length; i++) {
        var oper = this.operands[i];
        operResult.push(oper);
        operResult.push(oper.diff(name));
    }
    return this.countDiff.apply(null, operResult);
};

Operation.prototype.postfix = Operation.prototype.toString = function () {
    var resString = '(';

    for (var i = 0; i < this.operands.length; i++) {
        resString += this.operands[i].postfix() + ' ';
    }
    return resString + this.operation + ')';
};

Operation.prototype.prefix = function () {
    var resString = '(' + this.operation + ' ';
    for (var i = 0; i < this.operands.length - 1; i++) {
        resString += this.operands[i].prefix() + ' ';
    }
    resString += this.operands[this.operands.length - 1].prefix() + ')';
    return resString;
};

function OperationFactory(operStr, countFunc, countDiffFunc) {
    function Constructor() {
        var args = arguments;
        Operation.apply(this, args);
    }
    var prot = Object.create(Operation.prototype);
    prot.constructor = Constructor;
    prot.operation = operStr;
    prot.count = countFunc;
    prot.countDiff = countDiffFunc;

    Constructor.prototype = prot;
    return Constructor;
}
/* Constant class implementation */
function Const(a) {
    this.value = a;
}

Const.prototype.evaluate = function () {
    return this.value;
};

Const.prototype.diff = function () {
    return ZERO;
};

Const.prototype.postfix = Const.prototype.prefix = Const.prototype.toString = function () {
    return this.value.toString();
};

var ONE = new Const(1);
var ZERO = new Const(0);

/* Variable class implementation */
var vars = ['x', 'y', 'z'];

function Variable(name) {
    this.index = vars.indexOf(name);
}

Variable.prototype.evaluate = function () {
    return arguments[this.index];
};

Variable.prototype.diff = function (name) {
    if (vars[this.index] === name)
        return ONE;
    else
        return ZERO;
};

Variable.prototype.postfix = Variable.prototype.prefix = Variable.prototype.toString = function () {
    return vars[this.index];
};


/***** Operation examples part ******/
var Add = OperationFactory('+',
    function (a, b) { return a + b; },
    function (a, a_dir, b, b_dir) { return new Add(a_dir, b_dir); });

var Subtract = OperationFactory('-',
    function (a, b) { return a - b; },
    function (a, a_dir, b, b_dir) { return new Subtract(a_dir, b_dir); });

var Multiply = OperationFactory('*',
    function (a, b) { return a * b; },
    function (a, a_dir, b, b_dir) { return new Add(new Multiply(a, b_dir), new Multiply(a_dir, b)) });

var Divide = OperationFactory('/',
    function (a, b) { return a / b; },
    function (a, a_dir, b, b_dir) { return new Divide(new Subtract(new Multiply(a_dir, b), new Multiply(a, b_dir)), new Multiply(b, b)); });

var Negate = OperationFactory('negate',
    function (a) { return -a; },
    function (a, a_dir) { return new Negate(a_dir); });

var Sin = OperationFactory('sin',
    function (a) { return Math.sin(a); },
    function (a, a_dir) { return new Multiply(new Cos(a), a_dir); });

var Cos = OperationFactory('cos',
    function (a) { return Math.cos(a); },
    function (a, a_dir) { return new Negate(new Multiply(new Sin(a), a_dir)); });

function applyToConstructor(operConstr, argArray) {
    var newObj = Object.create(operConstr.prototype);
    var ctorRet = operConstr.apply(newObj, argArray);

    return ctorRet !== undefined ? ctorRet: newObj;
}

var OPERATIONS = {
    '+': [Add, 2],
    '-': [Subtract, 2],
    '*': [Multiply, 2],
    '/': [Divide, 2],
    'negate': [Negate, 1],
    'sin' : [Sin, 1],
    'cos' : [Cos, 1]
};

/***** Exception part *****/
function ParserException(message, expr, ind) {
    if (expr === null) {
        this.message = message;
    } else {
        this.message = message + " in index '" + ind + "'\n'" + expr + "'\n";
        for (var i = 0; i < ind + 1; i++)
            this.message += " ";
        this.message += "^\n";
    }
}

ParserException.prototype = Object.create(Error.prototype);
ParserException.prototype.name = "ParserException";
ParserException.prototype.constructor = ParserException;

/**** Helpful function ****/
function isDigit(c) {
    return c >= '0' && c <= '9';

}

function isLetter(c) {
    return c >= 'a' && c <= 'z';

}

function isNumber(expr, ind) {
    return !!((isDigit(expr[ind])) || (expr[ind] === '-' && ind + 1 < expr.length && isDigit(expr[ind + 1])));

}

function startsWith(str, begin, shift) {
    if (str.length - shift < begin.length)
        return false;

    for (var i = 0; i < begin.length; i++)
        if (str[shift + i] !== begin[i])
            return false;
    return true;
}
/**** Tokenizer function ****/
function getToken(expr, ind) {
    var beginInd = ind;

    /* If it's number */
    if (isNumber(expr, ind)) {
        ind++;
        while (ind < expr.length && isDigit(expr[ind])) {
            ind++;
        }
        return [expr.substring(beginInd, ind), ind];
    } else if (expr[ind] === '(' || expr[ind] === ')')
        return [expr[ind], ind + 1];

    /* If it's operation */
    for (var item in OPERATIONS)
        if (startsWith(expr, item, ind)) {
            ind += item.length;
            return [item, ind];
        }

    /* Get unknown token */
    while (isLetter(expr[ind]) || expr[ind] === '_') {
        ind++;
    }
    var name = expr.substring(beginInd, ind);
    if (vars.indexOf(name) !== -1)
        return [name, ind];

    while (ind < expr.length && expr[ind] !== ' ')
        ind++;

    throw new ParserException("Unexpected token '" + expr.substring(beginInd, ind) + "'", expr, beginInd);
}

function missingSpaces(expr, ind) {
    while (ind !== expr.length && expr[ind] === ' ') {
        ind++;
    }
    return ind;
}
/****** Parse function ******/
function parse(expr, parseFunc) {
    var ind = 0;

    expr = expr.trim();
    if (expr === "")
        throw new ParserException("Empty input", null, 0);

    var stack = [];
    var brBalance = 0;
    while (ind !== expr.length) {
        ind = missingSpaces(expr, ind);
        var oldInd = ind;
        var tokenInform = getToken(expr, ind);
        var token = tokenInform[0];
        ind = tokenInform[1];

        if (token === ')') {
            if (--brBalance < 0)
                throw new ParserException("Waiting opening bracket for closing bracket", expr, ind);

            if (stack[stack.length - 1][0] === '(')
                throw new ParserException("Empty brackets", expr, stack[stack.length - 1][1]);

            var res = parseFunc(stack, oldInd);
            token = res[0];
            var args = res[1];

            /* Read operation and check for bad situations */
            if (args.length > OPERATIONS[token][1]) {
                throw new ParserException("Too many arguments for operation '" + token + "'", expr, res[2]);
            } else if (args.length < OPERATIONS[token][1])
                throw new ParserException("Too less arguments for operation '" + token + "'", expr, res[2]);

            stack.push([applyToConstructor(OPERATIONS[token][0], args), oldInd]);
        } else if (token === '(') {
            brBalance++;
            stack.push([token[0], oldInd]);
        }else if (token in OPERATIONS) {
            stack.push([token, oldInd]);
        } else if (vars.indexOf(token) !== -1) {
            stack.push([new Variable(token), oldInd]);
        } else if (isNumber(token, 0)) {
            stack.push([new Const(parseInt(token)), oldInd]);
        }
    }
    if (brBalance !== 0)
        throw new ParserException("Missed closing bracket", expr, ind);
    if (stack.length !== 1)
        throw new ParserException("Extra argument out of brackets", null, 0);
    return stack[0][0];
}

/**** Parser examples ****/
var parsePostfix = function(expr) {
    return parse(expr,
        function (stack, ind) {
            var op = stack.pop();
            if (!(op[0] in OPERATIONS)) {
                throw new ParserException("Waiting for operation before ')'", expr, ind);
            }

            var args = [];
            for (var i = 0; i < OPERATIONS[op[0]][1] && stack[stack.length - 1][0] !== '('; i++) {
                var elem = stack.pop();
                if (!(elem[0] in OPERATIONS))
                    args.push(elem[0]);
                else
                    throw new ParserException("Two operations in one brackets", expr, elem[1]);
            }
            args.reverse();
            var br = stack.pop();
            if (br[0] !== "(")
                throw new ParserException("Waiting for opening bracket after '" + br[0].toString() + "' operand", expr, br[1]);

            return [op[0], args, op[1]];
        });
};

var parsePrefix = function(expr) {
    return parse(expr,
        function (stack) {
            var args = [];
            while (!(stack[stack.length - 1][0] in OPERATIONS || stack[stack.length - 1][0] === '('))
                args.push(stack.pop()[0]);
            var op = stack.pop();
            args.reverse();

            if (!(op[0] in OPERATIONS)) {
                throw new ParserException("Waiting for operation after '('", expr, (stack.length !== 0 ? stack.pop()[1] : 0));
            }

            var br = stack.pop();
            if (br[0] !== "(")
                throw new ParserException("Waiting for opening bracket before '" + op[0] + "' operation", null, 0);

            return [op[0], args, op[1]];
        });
};