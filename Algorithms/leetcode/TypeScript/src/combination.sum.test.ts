import { combinationSum4 } from "./combination.sum";

test(
    "check the result value of the call to the function combinationSum4",
    () => {
        let nums = [1, 2, 3];
        let result = combinationSum4(nums, 4);
        expect(result).toBe(7);

        nums = [1, 2, 3];
        result = combinationSum4(nums, 10);
        expect(result).toBe(274);

        nums = [1, 2, 3, 4];
        result = combinationSum4(nums, 10);
        expect(result).toBe(401);

        nums = [];
        result = combinationSum4(nums, 1);
        expect(result).toBe(0);

        nums = [4, 9];
        result = combinationSum4(nums, 17);
        expect(result).toBe(3);
        result = combinationSum4(nums, 14);
        expect(result).toBe(0);
    }
);