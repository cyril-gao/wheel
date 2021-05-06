/*
Implement next permutation, which rearranges numbers into the lexicographically next greater permutation of numbers.

If such an arrangement is not possible, it must rearrange it as the lowest possible order (i.e., sorted in ascending order).

The replacement must be in place and use only constant extra memory.
*/

export function nextPermutation(nums: number[]): void {
    if (nums.length > 1) {
        let i = nums.length - 1;
        let j = i - 1;
        while (j >= 0 && nums[j] >= nums[i]) {
            i = j;
            --j;
        }
        if (j >= 0) {
            let k = j;
            for (let next = k + 1; next < nums.length && nums[next] > nums[j]; k = next, ++next) {}
            let smallValue = nums[j];
            nums[j] = nums[k];
            for (let next = k + 1; next < nums.length && nums[next] > smallValue;) {
                nums[k] = nums[next];
                k = next++;
            }
            nums[k] = smallValue;
            for (j = nums.length - 1; i < j; ++i, --j) {
                let tmp = nums[i];
                nums[i] = nums[j];
                nums[j] = tmp;
            }
        } else {
            nums.sort((a, b) => a < b ? -1 : a > b ? 1 : 0);
        }
    }
}
