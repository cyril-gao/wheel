/*
Given an integer array nums, return all the triplets [nums[i], nums[j], nums[k]]
such that i != j, i != k, and j != k, and nums[i] + nums[j] + nums[k] == 0.

Notice that the solution set must not contain duplicate triplets.
*/

function binarySearch<T>(input: T[], begin: number, end: number, target: T): number {
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
    return mid;
}

function exists<T>(input: T[], begin: number, end: number, target: T): boolean {
    let position = binarySearch(input, begin, end, target);
    return (position !== end && input[position] === target);
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


/*
Given an array nums of n integers and an integer target,
find three integers in nums such that the sum is closest to target.
Return the sum of the three integers. You may assume that each input
would have exactly one solution.
*/

class Result
{
    private result1 = undefined;
    private diff1 = Infinity;
    private result2 = undefined;
    private diff2 = Infinity;

    constructor(
        private readonly nums: number[],
        private readonly target: number
    ) {}

    updateByValue(first: number, second: number, third: number): void {
        let sum = first + second + third;
        if (sum >= this.target) {
            let diff = sum - this.target;
            if (diff < this.diff1) {
                this.diff1 = diff;
                this.result1 = sum;
            }
        } else {
            let diff = this.target - sum;
            if (diff < this.diff2) {
                this.diff2 = diff;
                this.result2 = sum;
            }
        }
    }

    update(first: number, second: number, secondIndex: number, thirdIndex: number): void {
        if (thirdIndex != this.nums.length) {
            this.updateByValue(first, second, this.nums[thirdIndex]);
        }
        --thirdIndex;
        if (thirdIndex > secondIndex) {
            this.updateByValue(first, second, this.nums[thirdIndex]);
        }
    }

    get value(): number {
        if (this.diff1 !== Infinity) {
            if (this.diff2 !== Infinity) {
                return this.diff1 <= this.diff2 ? this.result1 : this.result2;
            }
            return this.result1;
        } else {
            return this.result2;
        }
    }
}

export function threeSumClosest(nums: number[], target: number): number {
    if (nums.length > 2) {
        nums.sort((a, b) => a < b ? -1 : a > b ? 1 : 0);
        let result = new Result(nums, target);
        for (let i = 0, ie = nums.length - 2; i < ie; ++i) {
            let first = nums[i];
            for (let j = i + 1, je = ie + 1; j < je; ++j) {
                let second = nums[j];
                let k = binarySearch(nums, j + 1, nums.length, target - first - second);
                result.update(first, second, j, k);
            }
        }
        return result.value;
    } else {
        if (nums.length === 1) {
            return nums[0];
        } else if (nums.length === 2) {
            let retval = nums[0] + nums[1];
            let diff = Math.abs(target - retval);
            if (diff > Math.abs(target - nums[0])) {
                diff = Math.abs(target - nums[0]);
                retval = nums[0];
            }
            if (diff > Math.abs(target - nums[1])) {
                retval = nums[1];
            }
            return retval;
        }
    }
}


/*
Given an array nums of n integers, return an array of all the unique quadruplets [nums[a], nums[b], nums[c], nums[d]] such that:
- 0 <= a, b, c, d < n
- a, b, c, and d are distinct.
- nums[a] + nums[b] + nums[c] + nums[d] == target
You may return the answer in any order.
*/

export function fourSum(nums: number[], target: number): number[][] {
    let retval = [];
    if (nums.length > 3) {
        nums.sort((a, b) => a < b ? -1 : a > b ? 1 : 0);
        let cache = new Map<number, Map<number, Set<number>>>();
        for (let i = 0, ie = nums.length - 3; i < ie; ++i) {
            let first = nums[i];
            for (let j = i + 1, je = ie + 1; j < je; ++j) {
                let second = nums[j];
                for (let k = j + 1, ke = je + 1; k < ke; ++k) {
                    let third = nums[k];
                    let remains = target - (first + second + third);
                    let p = binarySearch(nums, k + 1, nums.length, remains);
                    if (p != nums.length && nums[p] === remains) {
                        let h1 = cache.get(first);
                        if (h1 === undefined || !h1.has(second)) {
                            let set = new Set<number>();
                            set.add(third);
                            let map = new Map<number, Set<number>>();
                            map.set(second, set);
                            if (h1 === undefined) {
                                cache.set(first, map);
                            } else {
                                h1.set(second, set);
                            }
                            retval.push([first, second, third, remains]);
                        } else {
                            let h2 = h1.get(second);
                            if (!h2.has(third)) {
                                retval.push([first, second, third, remains]);
                                h2.add(third);
                            }
                        }
                    }
                }
            }
        }
    }
    return retval;
};