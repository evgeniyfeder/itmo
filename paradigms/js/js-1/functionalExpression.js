var VARS = ['x', 'y', 'z'];
var CONSTANTS = {
    'pi' : Math.PI,
    'e' : Math.E
};

/* Binary function */
function operation(f) {
    return function () {
        var operands = arguments;
        return function() {
            var operResult =[];
            for (var i = 0; i < operands.length; i++) {
                operResult.push(operands[i].apply(null, arguments));
            }
            return f.apply(null, operResult);
        }
    }
}

/* Get const function */
function cnst(num) {
    return function() {
        return num;
    }
}

/* Get variable function */
function variable(name) {
    var index = VARS.indexOf(name);
    return function () {
        return arguments[index];
    }
}

var add = operation(function (a, b) { return a + b });
var subtract = operation(function (a, b) { return a - b });
var multiply = operation(function (a, b) { return a * b });
var divide = operation(function (a, b) { return a / b });

var negate = operation(function (a) { return -a })

var min3 = operation(function () { return Math.min.apply(null, arguments) });
var max5 = operation(function () { return Math.max.apply(null, arguments) });


/* Set variables */
for (var i = 0; i < VARS.length; i++)
    this[VARS[i]] = variable(VARS[i]);

/* Set constants */
for (var index in CONSTANTS)
    this[index] = cnst(CONSTANTS[index]);

    /* Is number function */
    function is_digit(c) {
        return c >= '0' && c <= '9';
    }


/* Parse string function */
function parse(expr) {
    var tokens = expr.split(/\s+/);

    var OPERATIONS = {
        '+'      : [add, 2],
        '-'      : [subtract, 2],
        '*'      : [multiply, 2],
        '/'      : [divide, 2],
        'negate' : [negate, 1],
        'min3'   : [min3, 3],
        'max5'   : [max5, 5]
    };

    var stack = [];
    var index;
    for (var i = 0; i < tokens.length; i++) {
        var token = tokens[i];
        /* If it's binary operation */
        if (token in OPERATIONS) {
            var args = [];
            for (var j = 0; j < OPERATIONS[token][1]; j++)
                args.push(stack.pop());
            args.reverse();
            stack.push(OPERATIONS[token][0].apply(null, args));
        } else if (is_digit(tokens[i][0]) || (tokens[i][0] === '-' && tokens[i].length !== 1)) { /* Constant */
            stack.push(cnst(parseInt(tokens[i])));
        } else if (VARS.indexOf(tokens[i]) !== -1 || token in CONSTANTS) {
            stack.push(this[tokens[i]]);
        }
    }
    return stack.pop();
}
