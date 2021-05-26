import { evalRPN } from "./evaluate.reverse.polish.notation";

test(
    "check the result value of the call to the function evalRPN",
    () => {
        let tokens = ["2", "1", "+", "3", "*"];
        let result = evalRPN(tokens);
        expect(result).toEqual(9);

        tokens = ["4", "13", "5", "/", "+"];
        result = evalRPN(tokens);
        expect(result).toEqual(6);

        tokens = ["10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+"];
        result = evalRPN(tokens);
        expect(result).toEqual(22);
    }
);
