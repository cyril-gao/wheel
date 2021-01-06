/*
Given an integer array with all positive numbers and no duplicates,
find the number of possible combinations that add up to a positive integer target.

Example:
nums = [1, 2, 3]
target = 4

The possible combination ways are:
(1, 1, 1, 1)
(1, 1, 2)
(1, 2, 1)
(1, 3)
(2, 1, 1)
(2, 2)
(3, 1)

Note that different sequences are counted as different combinations.

Therefore the output is 7.
*/


// https://leetcode.com/problems/combination-sum-iv/
export function combinationSum4(nums: number[], target: number): number {
    let retval = 0;
    if (nums.length > 0) {
        nums.sort((a, b) => { if (a < b) { return -1; } else if (a > b) { return 1; } else { return 0; } });
        let numSet = new Set<number>(nums);
        let cache = [];
        for (let i = 0; i < nums[0]; ++i) {
            cache[i] = 0;
        }
        cache[nums[0]] = 1;
        for (let i = nums[0] + 1; i <= target; ++i) {
            let v = numSet.has(i) ? 1 : 0;
            for (let j of nums) {
                if (j < i) {
                    v += cache[i - j];
                } else {
                    break;
                }
            }
            cache[i] = v;
        }
        retval = cache[target];
    }
    return retval;
};
