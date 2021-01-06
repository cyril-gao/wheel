import { wiggleMaxLength } from "./wiggle.subsequence";

test(
    "check the result value of the call to the function wiggleMaxLength",
    () => {
        let nums = [1, 7, 4, 9, 2, 5];
        let result = wiggleMaxLength(nums);
        expect(result).toBe(6);

        nums = [1, 17, 5, 10, 13, 15, 10, 5, 16, 8];
        result = wiggleMaxLength(nums);
        expect(result).toBe(7);

        nums = [1, 2, 3, 4, 5, 6, 7, 8, 9];
        result = wiggleMaxLength(nums);
        expect(result).toBe(2);

        nums = [];
        result = wiggleMaxLength(nums);
        expect(result).toBe(0);

        nums = [1, 1];
        result = wiggleMaxLength(nums);
        expect(result).toBe(1);
    }
);