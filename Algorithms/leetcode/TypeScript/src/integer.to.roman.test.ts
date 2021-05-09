import { intToRoman } from "./integer.to.roman"

test(
    "check the result value of the call to the function intToRoman",
    () => {
        expect(intToRoman(3)).toEqual('III');
        expect(intToRoman(4)).toEqual('IV');
        expect(intToRoman(9)).toEqual('IX');
        expect(intToRoman(58)).toEqual('LVIII');
        expect(intToRoman(1994)).toEqual("MCMXCIV");
    }
)
