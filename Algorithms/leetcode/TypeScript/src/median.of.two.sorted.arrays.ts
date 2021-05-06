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

export function randomInt(lower: number, upper: number): number {
    let v = Math.floor(Math.random() * (upper - lower + 1));
    return v + lower;
}

export function sortNumber(a: number, b: number) {
    return a < b ? -1 : a > b ? 1 : 0;
}

export function randomSortedNumbers(): number[] {
    let upperLength = 873427;
    let lowerLength = 3573;

    let retval = new Array<number>(randomInt(lowerLength, upperLength));
    for (let i = 0; i < retval.length; ++i) {
        retval[i] = randomInt(1, Number.MAX_SAFE_INTEGER);
    }
    retval.sort(sortNumber);
    return retval;
}
