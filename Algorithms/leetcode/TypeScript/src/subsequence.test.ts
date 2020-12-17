import { numDistinct } from "./subsequence";

test(
    "check the result value of the call to the function numDistinct",
    () => {
        let result = numDistinct("rabbbit", "rabbit");
        expect(result).toEqual(3);

        result = numDistinct("babgbag", "bag");
        expect(result).toEqual(5);

        result = numDistinct("babgbag", "gab");
        expect(result).toEqual(0);
    }
);
