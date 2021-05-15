/*
Given an array of non-negative integers nums, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Your goal is to reach the last index in the minimum number of jumps.

You can assume that you can always reach the last index.

Example 1:
Input: nums = [2,3,1,1,4]
Output: 2
Explanation: The minimum number of jumps to reach the last index is 2. Jump 1 step from index 0 to 1, then 3 steps to the last index.

Example 2:
Input: nums = [2,3,0,1,4]
Output: 2
*/

export function minimumJump(nums: number[]): number {
    let retval = 0;
    if (nums.length > 1) {
        let jumpFurthest = nums[0];
        ++retval;
        for (let begin = 1, last = nums.length - 1; jumpFurthest < last;) {
            ++retval;
            let nextJumpFurthest = 0;
            for (let i = begin; i <= jumpFurthest; ++i) {
                nextJumpFurthest = Math.max(nextJumpFurthest, i + nums[i]);
            }
            begin = jumpFurthest + 1;
            jumpFurthest = nextJumpFurthest;
        }
    }
    return retval;
}

/*
Given an array of non-negative integers nums, you are initially positioned at the first index of the array.

Each element in the array represents your maximum jump length at that position.

Determine if you are able to reach the last index.
*/

export function canJump(nums: number[]): boolean {
    let retval = true;
    if (nums.length > 1) {
        let last = nums.length - 1;
        let jumpFurthest = nums[0];
        for (let i = 1; jumpFurthest >= i && jumpFurthest < last;) {
            let nextFurthest = 0;
            for (let j = i; j <= jumpFurthest; ++j) {
                nextFurthest = Math.max(nextFurthest, j + nums[j]);
            }
            i = jumpFurthest + 1;
            jumpFurthest = nextFurthest;
        }
        retval = (jumpFurthest >= last);
    }
    return retval;
}
