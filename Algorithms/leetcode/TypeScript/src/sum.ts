/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]]
such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.
*/
function exists<T>(input: T[], begin: number, end: number, target: T): boolean {
    let originalEnd = end;
    let mid = end;
    while (begin < end) {
        mid = Math.floor((begin + end) / 2);
        if (input[mid] > target) {
            end = mid;
            mid = begin;
        } else if (input[mid] < target) {
            begin = mid + 1;
            mid = end;
        } else {
            break;
        }
    }
    return (mid != originalEnd && input[mid] === target);
}

export function threeSum(nums: number[]): number[][] {
    let retval = [];
    if (nums.length > 2) {
        let cache = new Map<number, Set<number>>();
        nums.sort((a, b) => a < b ? -1 : a > b ? 1 : 0);
        for (let i = 0, ie = nums.length - 2; i < ie; ++i) {
            let first = nums[i];
            for (
                let j = i + 1, je = ie + 1, sum = first + nums[j];
                i < je && sum <= 0;
                ++j, sum = first + nums[j]
            ) {
                let left = -sum;
                if (exists(nums, j + 1, nums.length, left)) {
                    let s = cache.get(first);
                    if (!s || !s.has(nums[j])) {
                        retval.push([first, nums[j], left]);
                        if (!s) {
                            s = new Set<number>();
                            s.add(nums[j]);
                            cache.set(first, s);
                        } else {
                            s.add(nums[j]);
                        }
                    }
                }
            }
        }
    }
    return retval;
}
