/*
Given a sorted array nums, remove the duplicates in-place such that duplicates appeared at most twice and return the new length.

Do not allocate extra space for another array; you must do this by modifying the input array in-place with O(1) extra memory.
*/

export function removeDuplicates<T>(nums: T[]): number {
    let nextIndex = nums.length;
    if (nums.length > 1) {
        nextIndex = 0;
        for (let i = 0; i < nums.length;) {
            let v = nums[i];
            let j = i;
            let count = 0;
            while (j < nums.length && nums[j] === v) {
                ++count;
                if (count <= 2) {
                    nums[nextIndex++] = v;
                }
                ++j;
            }
            i = j;
        }
    }
    return nextIndex;
}
