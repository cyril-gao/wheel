/*
Given an unsorted array, find the maximum difference between the successive elements in its sorted form.

Return 0 if the array contains less than 2 elements.

Example 1:
Input: [3,6,9,1]
Output: 3
Explanation: The sorted form of the array is [1,3,6,9], either
             (3,6) or (6,9) has the maximum difference 3.

Example 2:
Input: [10]
Output: 0
Explanation: The array contains less than 2 elements, therefore return 0.
*/


export function maximumGap(nums: number[]): number {
    let retval = 0;
    if (nums.length > 1) {
        let sortedNums = nums.sort((a, b) => a > b ? 1 : b > a ? -1 : 0);
        for (let i = 0; i < sortedNums.length;) {
            let j = i + 1;
            while (j < sortedNums.length && sortedNums[j] == sortedNums[i]) {
                ++j;
            }
            if (j < sortedNums.length) {
                let diff = sortedNums[j] - sortedNums[i];
                if (diff > retval) {
                    retval = diff;
                }
            }
            i = j;
        }
    }
    return retval;
};
