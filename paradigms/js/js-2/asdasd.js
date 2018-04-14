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
}

Operation.prototype.diff = function (name) {
    var operResult = [];
    for (var i = 0; i < this.operands.length; i++) {
        operResult.push(this.operands[i]);
        operResult.push(this.operands[i].diff(name));
    }
    return this.countDiff.apply(null, operResult);
}

Operation.prototype.toString = function () {
    var resString = '';

    for (var i = 0; i < this.operands.length; i++) {
        resString += this.operands[i].toString() + ' ';
    }
    return resString + this.operation;
}

function OperationFactory(operStr, countFunc, countDiffFunc) {
    function Constructor() {
        Operation.apply(this, arguments);
    }

    Constructor.prototype = Object.create(Operation.prototype);
    Constructor.prototype.operation = operStr;
    Constructor.prototype.constructor = Constructor;
    Constructor.prototype.count = countFunc;
    Constructor.prototype.countDiff = countDiffFunc;
    return Constructor;
}
/* Constant class implementation */
function Const(a) {
    this.value = a;
}

Const.prototype.evaluate = function () {
    return this.value;
}

Const.prototype.diff = function (name) {
    return new Const(0);
}

Const.prototype.toString = function () {
    return this.value.toString();
}

/* Variable class implementation */
var vars = ['x', 'y', 'z'];

function Variable(name) {
    this.index = vars.indexOf(name);
}

Variable.prototype.evaluate = function () {
    return arguments[this.index];
}

Variable.prototype.diff = function (name) {
    if (vars[this.index] === name)
        return new Const(1);
    else
        return new Const(0);
}

Variable.prototype.toString = function () {
    return vars[this.index];
}

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


function applyToConstructor(constructor, argArray) {
    var elem = new Object(constructor.prototype);
    constructor.apply(elem, argArray);
    return elem;
}

/* Is number function */
function is_digit(c) {
    return c >= '0' && c <= '9';
}

function parse(expr) {
    var OPERATIONS = {
        '+': [Add, 2],
        '-': [Subtract, 2],
        '*': [Multiply, 2],
        '/': [Divide, 2],
        'negate': [Negate, 1]
    };
    var stack = [];
    var tokens = expr.split(/\s+/);
    for (var i = 0; i < tokens.length; i++) {
        var token = tokens[i];
        if (token in OPERATIONS) {
            var args = [];
            for (var j = 0; j < OPERATIONS[token][1]; j++)
                args.unshift(stack.pop());
            stack.push(applyToConstructor(OPERATIONS[token][0], args));
        } else if (vars.indexOf(token) !== -1) {
            stack.push(new Variable(token));
        } else if (is_digit(tokens[i][0]) || (tokens[i][0] === '-' && tokens[i].length !== 1)) {
            stack.push(new Const(parseInt(token)));
        }
    }
    return stack.pop();
}