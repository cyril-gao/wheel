import { findMin } from "./find.minimum.in.rotated.sorted.array";

test(
    "check the result value of the call to the function findMin",
    () => {
        let nums = [0, 0, 0, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4];
        for (let i = -1; i < nums.length; ++i) {
            let v = findMin(nums);
            expect(v).toEqual(0);
            v = nums.pop();
            nums.unshift(v);
        }
        nums = [1, 3, 5];
        for (let i = -1; i < nums.length; ++i) {
            let v = findMin(nums);
            expect(v).toEqual(1);
            v = nums.pop();
            nums.unshift(v);
        }
        nums = [0, 1, 2, 2, 2];
        for (let i = -1; i < nums.length; ++i) {
            let v = findMin(nums);
            expect(v).toEqual(0);
            v = nums.pop();
            nums.unshift(v);
        }
        nums = [0, 0, 1, 1, 2, 2, 2, 3, 3, 3, 4, 5, 6];
        for (let i = -1; i < nums.length; ++i) {
            let v = findMin(nums);
            expect(v).toEqual(0);
            v = nums.pop();
            nums.unshift(v);
        }
        nums = [0, 1, 1, 2, 2, 2, 3, 3, 3, 3, 4, 5, 6, 6, 6, 6];
        for (let i = -1; i < nums.length; ++i) {
            let v = findMin(nums);
            expect(v).toEqual(0);
            v = nums.pop();
            nums.unshift(v);
        }
        nums = [0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16];
        for (let i = -1; i < nums.length; ++i) {
            let v = findMin(nums);
            expect(v).toEqual(0);
            v = nums.pop();
            nums.unshift(v);
        }
    }
);
