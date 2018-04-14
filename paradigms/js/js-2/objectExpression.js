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

/* Set operations */
function Add(a, b) {
    Operation.call(this, a, b);
    this.operation = '+'
}

Add.prototype = Object.create(Operation.prototype);
Add.prototype.constructor = Add;
Add.prototype.count = function (a, b) {
    return a + b;
}
Add.prototype.countDiff = function (a, a_dir, b, b_dir) {
    return new Add(a_dir, b_dir);
}

function Subtract(a, b) {
    Operation.call(this, a, b);
    this.operation = '-'
}

Subtract.prototype = Object.create(Operation.prototype);
Subtract.prototype.constructor = Subtract;
Subtract.prototype.count = function (a, b) {
    return a - b;
}
Subtract.prototype.countDiff = function (a, a_dir, b, b_dir) {
    return new Subtract(a_dir, b_dir);
}

function Multiply(a, b) {
    Operation.call(this, a, b);
    this.operation = '*'
}

Multiply.prototype = Object.create(Operation.prototype);
Multiply.prototype.constructor = Multiply;
Multiply.prototype.count = function (a, b) {
    return a * b;
}
Multiply.prototype.countDiff = function (a, a_dir, b, b_dir) {
    return new Add(new Multiply(a, b_dir), new Multiply(a_dir, b));
}

function Divide(a, b) {
    Operation.call(this, a, b);
    this.operation = '/'
}

Divide.prototype = Object.create(Operation.prototype);
Divide.prototype.constructor = Divide;
Divide.prototype.count = function (a, b) {
    return a / b;
}
Divide.prototype.countDiff = function (a, a_dir, b, b_dir) {
    return new Divide(new Subtract(new Multiply(a_dir, b), new Multiply(a, b_dir)), new Multiply(b, b));
}

function Negate(a) {
    Operation.call(this, a);
    this.operation = 'negate'
}

Negate.prototype = Object.create(Operation.prototype);
Negate.prototype.constructor = Negate;
Negate.prototype.count = function (a) {
    return -a;
}
Negate.prototype.countDiff = function (a, a_dir) {
    return new Negate(a_dir);
}

function Sqrt(a) {
    Operation.call(this, a);
    this.operation = 'sqrt'
}

Sqrt.prototype = Object.create(Operation.prototype);
Sqrt.prototype.constructor = Sqrt;
Sqrt.prototype.count = function (a) {
    return Math.sqrt(Math.abs(a));
}
Sqrt.prototype.countDiff = function (a, a_dir) {
    return new Multiply(new Divide(a, new Multiply(new Const(2), new Sqrt(new Multiply(a, new Multiply(a, a))))), a_dir);
}

function Square(a) {
    Operation.call(this, a);
    this.operation = 'square'
}

Square.prototype = Object.create(Operation.prototype);
Square.prototype.constructor = Square;
Square.prototype.count = function (a) {
    return a * a;
}
Square.prototype.countDiff = function (a, a_dir) {
    return new Multiply(new Multiply(new Const(2), a), a_dir);
}


function applyToConstructor(constructor, argArray) {
    var args = [null].concat(argArray);
    var factoryFunction = constructor.bind.apply(constructor, args);
    return new factoryFunction();
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
        'negate': [Negate, 1],
        'sqrt' : [Sqrt, 1],
        'square' : [Square, 1]
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