import { Solution } from "./random.pick.index";

test(
    "check the result value of the call to the function maximumGap",
    () => {
        let nums = [1, 2, 3, 3, 3];
        let solution = new Solution(nums);
        let result = solution.pick(3);
        expect(result === 2 || result === 3 || result === 4).toBeTruthy();

        result = solution.pick(1);
        expect(result).toEqual(0);

        result = solution.pick(2);
        expect(result).toEqual(1);
    }
);
