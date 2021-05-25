/*
Given two sorted arrays nums1 and nums2 of size m and n respectively,
return the median of the two sorted arrays.

Example 1:
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

Example 3:
Input: nums1 = [0,0], nums2 = [0,0]
Output: 0.00000

Example 4:
Input: nums1 = [], nums2 = [1]
Output: 1.00000

Example 5:
Input: nums1 = [2], nums2 = []
Output: 2.00000
*/

function binarySearch<T>(input: T[], begin: number, end: number, target: T): number {
    let retval = end;
    while (begin < end) {
        retval = Math.floor((begin + end) / 2);
        if (input[retval] > target) {
            end = retval;
            retval = begin;
        } else if (input[retval] < target) {
            begin = retval + 1;
            retval = end;
        } else {
            break;
        }
    }
    return retval;
}

export function searchSortedArrays<T>(
    input1: T[], b1: number, e1: number,
    input2: T[], b2: number, e2: number,
    sequenceNumber: number
): T {
    while (b1 < e1 && b2 < e2) {
        let m1 = Math.floor((b1 + e1) / 2);
        let m2 = Math.floor((b2 + e2) / 2);
        if (input1[m1] <= input2[m2]) {
            let i = binarySearch(input2, b2, m2, input1[m1]);
            let sn = m1 - b1 + i - b2;
            if (sn < sequenceNumber) {
                sequenceNumber -= (sn + 1);
                b1 = m1 + 1;
                b2 = i;
            } else if (sn > sequenceNumber) {
                e1 = m1;
                e2 = i;
            } else {
                return input1[m1];
            }
        } else {
            let i = binarySearch(input1, b1, m1, input2[m2]);
            let sn = m2 - b2 + i - b1;
            if (sn < sequenceNumber) {
                sequenceNumber -= (sn + 1);
                b1 = i;
                b2 = m2 + 1;
            } else if (sn > sequenceNumber) {
                e1 = i;
                e2 = m2;
            } else {
                return input2[m2];
            }
        }
    }
    if (b1 < e1) {
        return input1[b1 + sequenceNumber];
    }
    if (b2 < e2) {
        return input2[b2 + sequenceNumber];
    }
    throw new Error('Bad sequence number');
}

function findMedian(nums: number[]): number {
    let retval = 0;
    if (nums.length > 0) {
        let half = Math.floor(nums.length / 2);
        retval = nums[half];
        if ((nums.length % 2) === 0) {
            retval += nums[half - 1];
            retval /= 2;
        }
    }
    return retval;
}

export function findMedianSortedArrays(nums1: number[], nums2: number[]): number {
    if (nums1.length > 0 && nums2.length > 0) {
        let n = nums1.length + nums2.length;
        let half = Math.floor(n / 2);
        let retval = searchSortedArrays(nums1, 0, nums1.length, nums2, 0, nums2.length, half);
        if ((n % 2) === 0) {
            retval += searchSortedArrays(nums1, 0, nums1.length, nums2, 0, nums2.length, half - 1);
            retval /= 2;
        }
        return retval;
    } else {
        if (nums1.length > 0) {
            return findMedian(nums1);
        }
        if (nums2.length > 0) {
            return findMedian(nums2);
        }
        return 0;
    }
};


/*
There is an array input sorted in non-decreasing order (not necessarily with distinct values).

Before being passed to your function, input is rotated at an unknown pivot index k (0 <= k < input.length)
such that the resulting array is [input[k], input[k+1], ..., input[n-1], input[0], input[1], ..., input[k-1]] (0-indexed).
For example, [0,1,2,4,4,4,5,6,6,7] might be rotated at pivot index 5 and become [4,5,6,6,7,0,1,2,4,4].

Given the array input after the rotation and an integer target, return true if target is in input, or false if it is not in input.

You must decrease the overall operation steps as much as possible.
*/

function searchRotatedSortedArray<T>(input: T[], begin: number, end: number, target: T): boolean {
    let retval = false;
    if (begin < end) {
        if ((end - begin) > 1) {
            if (target < input[begin]) {
                let mid = Math.floor((begin + end) / 2);
                if (input[begin] < input[mid]) {
                    retval = searchRotatedSortedArray(input, mid + 1, end, target);
                } else {
                    retval = searchRotatedSortedArray(input, mid, end, target);
                    if (!retval) {
                        retval = searchRotatedSortedArray(input, begin + 1, mid, target);
                    }
                }
            } else if (target > input[begin]) {
                let mid = Math.floor((begin + end) / 2);
                if (input[begin] < input[mid]) {
                    ++mid;
                    let i = binarySearch(input, begin + 1, mid, target);
                    if (i !== mid && input[i] === target) {
                        retval = true;
                    }
                    if (!retval) {
                        retval = searchRotatedSortedArray(input, mid, end, target);
                    }
                } else {
                    retval = searchRotatedSortedArray(input, begin + 1, mid, target);
                    if (!retval && input[begin] === input[mid]) {
                        retval = searchRotatedSortedArray(input, mid, end, target);
                    }
                }
            } else {
                retval = true;
            }
        } else {
            retval = (input[begin] === target);
        }
    }
    return retval;
}

export function search<T>(input: T[], target: T): boolean {
    return searchRotatedSortedArray(input, 0, input.length, target);
}
