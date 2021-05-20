import { removeDuplicates } from "./remove.duplicates.from.sorted.array.ii";

test(
    "check the result value of the call to the function removeDuplicates",
    () => {
        let nums = [1, 1, 1, 2, 2, 3];
        let expectation = [1, 1, 2, 2, 3];
        let retval = removeDuplicates(nums);
        expect(retval).toEqual(expectation.length);
        for (let i = 0; i < expectation.length; ++i) {
            expect(nums[i]).toEqual(expectation[i]);
        }

        nums = [0, 0, 1, 1, 1, 1, 2, 3, 3];
        expectation = [0, 0, 1, 1, 2, 3, 3];
        retval = removeDuplicates(nums);
        expect(retval).toEqual(expectation.length);
        for (let i = 0; i < expectation.length; ++i) {
            expect(nums[i]).toEqual(expectation[i]);
        }

        nums = [0, 0, 0, 1, 1, 1, 1, 2, 3, 4, 4, 5, 5, 5, 6];
        expectation = [0, 0, 1, 1, 2, 3, 4, 4, 5, 5, 6];
        retval = removeDuplicates(nums);
        expect(retval).toEqual(expectation.length);
        for (let i = 0; i < expectation.length; ++i) {
            expect(nums[i]).toEqual(expectation[i]);
        }
    }
);