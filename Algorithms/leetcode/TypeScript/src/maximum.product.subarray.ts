/*
Given an integer array nums, find the contiguous subarray within an array (containing at least one number) which has the largest product.

Example 1:
Input: [2,3,-2,4]
Output: 6
Explanation: [2,3] has the largest product 6.

Example 2:
Input: [-2,0,-1]
Output: 0
Explanation: The result cannot be 2, because [-2,-1] is not a subarray.
*/


function _maxProduct(nums: number[], begin: number, end: number, negatives: number[]): number {
    if (negatives.length % 2 == 0) {
        let product: number;
        if (begin < end) {
            product = 1;
            for (let i = begin; i < end; ++i) {
                product *= nums[i];
            }
        }
        return product;
    } else {
        let separator = negatives[0];
        let retval = nums[separator];
        let left: number = retval;
        let right: number = retval;
        for (let i = begin; i < separator; ++i) {
            if (i !== begin) {
                left *= nums[i];
            } else {
                left = nums[i];
            }
        }
        for (let i = separator + 1, j = i; i < end; ++i) {
            if (i !== j) {
                right *= nums[i];
            } else {
                right = nums[i];
            }
        }
        retval = Math.max(left, right);
        if (begin == separator) {
            left = 1;
        }
        for (let i = 2; i < negatives.length; i += 2) {
            let s2 = negatives[i];
            let v = 1;
            for (let j = separator + 1; j < s2; ++j) {
                v *= nums[j];
            }
            left *= (v * nums[separator]);
            right = Math.floor(right / (v * nums[s2]));
            v = Math.max(left, right);
            if (v > retval) {
                retval = v;
            }
            separator = s2;
        }
        return retval;
    }
};

export function maxProduct(nums: number[]): number {
    let retval: number;
    for (let i = 0; i < nums.length;) {
        let negatives = [];
        let j = i;
        while (j < nums.length && nums[j] !== 0) {
            if (nums[j] < 0) {
                negatives.push(j);
            }
            ++j;
        }
        let r = _maxProduct(nums, i, j, negatives);
        if (j < nums.length && nums[j] === 0) {
            ++j;
            if (r < 0 || r === undefined) {
                r = 0;
            }
        }
        if (retval !== undefined) {
            retval = Math.max(retval, r);
        } else {
            retval = r;
        }
        i = j;
    }
    return retval;
};
