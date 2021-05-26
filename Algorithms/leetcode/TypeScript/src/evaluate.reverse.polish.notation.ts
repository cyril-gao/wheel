/*
Evaluate the value of an arithmetic expression in Reverse Polish Notation.

Valid operators are +, -, *, and /. Each operand may be an integer or another expression.

Note that division between two integers should truncate toward zero.

It is guaranteed that the given RPN expression is always valid. That means the expression would always evaluate to a result, and there will not be any division by zero operation.
*/

export function evalRPN(tokens: string[]): number {
    let retval = 0;
    let stack = [];
    for (let i = 0; i < tokens.length; ++i) {
        let v = parseInt(tokens[i]);
        if (!isNaN(v)) {
            stack.push(v);
        } else {
            if (stack.length >= 2) {
                let v2 = stack.pop();
                let v1 = stack.pop();
                if (tokens[i] === '+') {
                    v = v1 + v2;
                } else if (tokens[i] === '-') {
                    v = v1 - v2;
                } else if (tokens[i] === '*') {
                    v = v1 * v2;
                } else if (tokens[i] === '/') {
                    let flag = (v1 * v2) >= 0 ? 1 : -1;
                    v = Math.floor(Math.abs(v1) / Math.abs(v2));
                    if (v !== 0) {
                        v *= flag;
                    }
                } else {
                    throw new Error(`unsupported operator: ${tokens[i]}`);
                }
                stack.push(v);
            } else {
                throw new Error(`Bad input: ${tokens}`);
            }
        }
    }
    if (stack.length === 1) {
        retval = stack[0];
    } else {
        throw new Error(`Bad input: ${tokens}`);
    }
    return retval;
}
