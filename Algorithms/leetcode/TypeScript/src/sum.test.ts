import { threeSum } from "./sum";

test(
    "check the result value of the call to the function threeSum",
    () => {
        let nums = [-1, 0, 1, 2, -1, -4];
        let result = threeSum(nums);
        expect(result.length).toEqual(2);

        nums = [-6, -5, -4, -3, -2, -1, 1, 2, 3, 4, 5, 6];
        result = threeSum(nums);
        expect(result.length).toEqual(12);

        nums = [-6, -5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 6];
        result = threeSum(nums);
        expect(result.length).toEqual(18);

        expect(threeSum([]).length).toEqual(0);
        expect(threeSum([0]).length).toEqual(0);
        expect(threeSum([0, 0]).length).toEqual(0);
    }
);
