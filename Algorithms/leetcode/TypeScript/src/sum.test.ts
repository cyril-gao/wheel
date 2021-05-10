import { threeSum, threeSumClosest, fourSum } from "./sum";

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

test(
    "check the result value of the call to the function threeSumClosest",
    () => {
        let nums = [0, 2, 1, -3];
        let result = threeSumClosest(nums, 1);
        expect(result).toEqual(0);

        nums = [0, 0, 0];
        result = threeSumClosest(nums, 1);
        expect(result).toEqual(0);

        nums = [0, 1, 2];
        result = threeSumClosest(nums, 0);
        expect(result).toEqual(3);

        nums = [-1, 0, 1, 1, 55];
        result = threeSumClosest(nums, 3);
        expect(result).toEqual(2);
    }
);

test(
    "check the result value of the call to the function fourSum",
    () => {
        let nums = [1, 0, -1, 0, -2, 2];
        let result = fourSum(nums, 0);
        expect(result.length).toEqual(3);

        nums = [2, 2, 2, 2, 2, 2, 2];
        result = fourSum(nums, 8);
        expect(result.length).toEqual(1);

        nums = [0, 1, 2];
        result = fourSum(nums, 0);
        expect(result.length).toEqual(0);

        nums = [-1, 0, 1, 1, 55];
        result = fourSum(nums, 1);
        expect(result.length).toEqual(1);
    }
);
