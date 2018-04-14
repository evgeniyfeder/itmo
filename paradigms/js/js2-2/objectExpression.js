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
        var args = arguments;
        Operation.apply(this, args);
        return this;
    }

    Constructor.prototype = Object.create(Operation.prototype);
    Constructor.prototype.constructor = Constructor;

    Constructor.prototype.operation = operStr;
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
    return zero;
}

Const.prototype.toString = function () {
    return this.value.toString();
}

var one = new Const(1);
var zero = new Const(0);

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
        return one;
    else
        return zero;
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

var Sqrt = OperationFactory('sqrt',
    function (a) { return Math.sqrt(Math.abs(a)); },
    function (a, a_dir) {
        return new Multiply(
            new Divide(a, new Multiply(new Const(2), new Sqrt(new Multiply(a, new Multiply(a, a))))),
            a_dir);
    });
var Square = OperationFactory('square',
    function (a) { return a * a; },
    function (a, a_dir) { return new Multiply(new Multiply(new Const(2), a), a_dir); });


function applyToConstructor(operConstr, argArray) {
    var args = [null].concat(argArray);
    var factoryFunction = operConstr.bind.apply(operConstr, args);
    return new factoryFunction();
}

function parse(expr) {
    var OPERATIONS = {
        '+': [Add, 2],
        '-': [Subtract, 2],
        '*': [Multiply, 2],
        '/': [Divide, 2],
        'negate': [Negate, 1],
        'square': [Square, 1],
        'sqrt': [Sqrt, 1]
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
        } else if (/-?[0-9]+/.test(token)) {
            stack.push(new Const(parseInt(token)));
        }
    }
    return stack.pop();
}