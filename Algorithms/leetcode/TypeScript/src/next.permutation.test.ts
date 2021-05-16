import { nextPermutation, getPermutation } from './next.permutation';

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

test(
    "check the result value of the call to the function getPermutation",
    () => {
        let expectation = [
            '1234',
            '1243',
            '1324',
            '1342',
            '1423',
            '1432',
            '2134',
            '2143',
            '2314',
            '2341',
            '2413',
            '2431',
            '3124',
            '3142',
            '3214',
            '3241',
            '3412',
            '3421',
            '4123',
            '4132',
            '4213',
            '4231',
            '4312',
            '4321'
        ];
        for (let k = 0; k < expectation.length; ++k) {
            expect(getPermutation(4, k + 1)).toEqual(expectation[k]);
        }
    }
);
