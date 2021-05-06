import { nextPermutation } from './next.permutation';

test(
    "check the result value of the call to the function nextPermutation",
    () => {
        let nums = [1, 2, 3];
        nextPermutation(nums);
        expect(nums).toEqual([1, 3, 2]);

        nums = [1, 3, 2];
        nextPermutation(nums);
        expect(nums).toEqual([2, 1, 3]);

        nums = [3, 2, 1];
        nextPermutation(nums);
        expect(nums).toEqual([1, 2, 3]);

        nums = [1, 1, 5];
        nextPermutation(nums);
        expect(nums).toEqual([1, 5, 1]);

        nums = [6, 3, 4, 7, 2, 1];
        nextPermutation(nums);
        expect(nums).toEqual([6, 3, 7, 1, 2, 4]);

        nums = [6, 3, 4, 7, 1, 2, 1];
        nextPermutation(nums);
        expect(nums).toEqual([6, 3, 4, 7, 2, 1, 1]);

        nums = [6, 3, 4, 7, 1, 2];
        nextPermutation(nums);
        expect(nums).toEqual([6, 3, 4, 7, 2, 1]);
    }
);
