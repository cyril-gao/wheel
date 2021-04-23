import { removeKdigits } from "./remove.k.digits";

test(
    "check the result value of the call to the function removeKdigits",
    () => {
        let num = "1432219";
        let result = removeKdigits(num, 3);
        expect(result).toEqual("1219");

        num = "10200";
        result = removeKdigits(num, 1);
        expect(result).toEqual("200");
        result = removeKdigits(num, 2);
        expect(result).toEqual("0");

        num = "10240000";
        result = removeKdigits(num, 4);
        expect(result).toEqual("0");

        num = "101432219";
        result = removeKdigits(num, 4);
        expect(result).toEqual("1219");

        num = "100145321219";
        result = removeKdigits(num, 6);
        expect(result).toEqual("1119");

        num = "132476589";
        result = removeKdigits(num, 5);
        expect(result).toEqual("1245");

        num = "5337";
        result = removeKdigits(num, 2);
        expect(result).toEqual("33");
    }
);
