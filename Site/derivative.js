function Token (type, value, args) {
    this.type = type;
    this.value = value;
    this.args = args;
}

function funcRes (bool, type, args) {
    this.bool = bool;
    this.type = type;
    this.args = args;
}

function isDigit (char) {
    if (char >= "0" && char <= "9") {
        return true;
    }
    return false;
}

function isOperator (char) {
    if (char == "-" || char == "+" || char == "~" || char == "*" || char == "/") {
        return true;
    }
    return false;
}

function isFunc (string, beg) {
    if (string.substring(beg, beg+3) == "pow") {
        return new funcRes(true, "pow", 2);
    }
    else if (string.substring(beg, beg+3) == "sin") {
        return new funcRes(true, "sin", 1);
    }
    else if (string.substring(beg, beg+3) == "cos") {
        return new funcRes(true, "cos", 1);
    }
    else if (string.substring(beg, beg+3) == "tan") {
        return new funcRes(true, "tan", 1);
    }
    else if (string.substring(beg, beg+3) == "sec") {
        return new funcRes(true, "sec", 1);
    }
    else if (string.substring(beg, beg+3) == "csc") {
        return new funcRes(true, "csc", 1);
    }
    else if (string.substring(beg, beg+3) == "cot") {
        return new funcRes(true, "cot", 1);
    }
    else if (string.substring(beg, beg+6) == "arcsin") {
        return new funcRes(true, "arcsin", 1);
    }
    else if (string.substring(beg, beg+6) == "arccos") {
        return new funcRes(true, "arccos", 1);
    }
    else if (string.substring(beg, beg+6) == "arctan") {
        return new funcRes(true, "arctan", 1);
    }
    else if (string.substring(beg, beg+6) == "arcsec") {
        return new funcRes(true, "arcsec", 1);
    }
    else if (string.substring(beg, beg+6) == "arccsc") {
        return new funcRes(true, "arccsc", 1);
    }
    else if (string.substring(beg, beg+6) == "arccot") {
        return new funcRes(true, "arccot", 1);
    }
    else if (string.substring(beg, beg+4) == "sinh") {
        return new funcRes(true, "sinh", 1);
    }
    else if (string.substring(beg, beg+4) == "cosh") {
        return new funcRes(true, "cosh", 1);
    }
    else if (string.substring(beg, beg+4) == "tanh") {
        return new funcRes(true, "tanh", 1);
    }
    else if (string.substring(beg, beg+4) == "sech") {
        return new funcRes(true, "sech", 1);
    }
    else if (string.substring(beg, beg+4) == "csch") {
        return new funcRes(true, "csch", 1);
    }
    else if (string.substring(beg, beg+3) == "log") {
        return new funcRes(true, "log", 2);
    }
    else if (string.substring(beg, beg+2) == "ln") {
        return new funcRes(true, "ln", 1);
    }
    else if (string.substring(beg, beg+3) == "fact") {
        return new funcRes(true, "fact", 1);
    }
    else if (string.substring(beg, beg+3) == "sum") {
        return new funcRes(true, "sum", 3);
    }
    return new funcRes(false, "", 0);
}

function isConst (string, beg) {
    if (string[beg] == "e") {
        return new funcRes(true, "e", 0);
    }
    else if (string.substring(beg, beg+2) == "gr") {
        return new funcRes(true, "gr", 0);
    }
    else if (string.substring(beg, beg+2) == "pi") {
        return new funcRes(true, "pi", 0);
    }
    return new funcRes(false, "", 0);
}

function isAlpha (char) {
    if ((char >= "a" && char <= "z") || (char >= "A" && char <= "Z")) {
        return true;
    }
    return false;
}

function isVar (string, beg) {
    if (isAlpha(string[beg])) {
        if (string[beg+1] == "_" && isAlpha(string[beg+2])) {
            return new funcRes(true, string.substring(beg, beg+3), 0);
        }
        return new funcRes(true, string[beg], 0);
    }
    return new funcRes(false, "", 0);
}

function parse (string) {
    var i = 0;
    var total = 0;
    var array = [];
    while (i < string.length) {
        var results = [isDigit(string[i]), isOperator(string[i]), isAlpha(string[i])];
        console.log(results[0]);
        console.log(results[1]);
        console.log(results[2]);
        console.log(string[i] == "(" || string[i] == ")" || string[i] == ",");
        if (results[0]) {
            while (isDigit(string[i]) && i < string.length) {
               i += 1;
            }
            console.log("number");
            array.push(new Token("Number", parseInt(string.substring(total, i)), 0));
        }
        else if (results[1]) {
            console.log("operator");
            array.push(new Token("Operator", string[i]), 0);
            i += 1;
        }
        else if (results[2]) {
            var local = [isFunc(string, i), isConst(string, i), isVar(string, i)];
            if (local[0].bool) {
                console.log("function");
                array.push(new Token("Function", local[0].type, local[0].args));
                i += local[0].type.length;
            }
            else if (local[1].bool) {
                console.log("constant");
                array.push(new Token("Constant", local[1].type, local[1].args));
                i += local[1].type.length;
            }
            else if (local[2].bool) {
                console.log("variable");
                array.push(new Token("Variable", local[2].type, local[2].args));
                i += local[2].type.length;
            }
        }
        else if (string[i] == "(" || string[i] == ")" || string[i] == ",") {
            console.log("punctuation");
            array.push(new Token("Punctuation", string[i], 0));
            i += 1;
        }
        else {
            console.log("Some error ocurred on parsing");
            break;
        }
        total = i;
    }
    return array;
}

function main () {
    var txtName = document.getElementById("txtName");
    var formula = txtName.value;
    var array = parse(formula);
    var nestedDiv = document.getElementById("result");
    nestedDiv.textContent = array[1].value;
}
//function toPrefix(array) {}

//function derivate(array) {}

//function toString(array) {}
