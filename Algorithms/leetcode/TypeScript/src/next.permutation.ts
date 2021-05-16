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


/*
The set [1, 2, 3, ..., n] contains a total of n! unique permutations.

By listing and labeling all of the permutations in order, we get the following sequence for n = 3:
1. "123"
2. "132"
3. "213"
4. "231"
5. "312"
6. "321"

Given n and k, return the kth permutation sequence.
*/

function getCandidate(index: number, used: boolean[]): number {
    for (let i = 1, j = 0; i < used.length; ++i) {
        if (!used[i]) {
            if (++j === index) {
                used[i] = true;
                return i;
            }
        }
    }
    throw new Error('Bug');
}

export function getPermutation(n: number, k: number): string {
    if (n > 0 && k > 0) {
        if (n > 1) {
            let result = [];
            let cache = new Array<number>(n);
            cache[0] = cache[1] = 1;
            for (let i = 2; i < n; ++i) {
                cache[i] = i * cache[i - 1];
            }
            let used = new Array<boolean>(n + 1);
            used.fill(false);
            for (let i = n - 1; i > 1; --i) {
                let quotient = Math.floor((k + cache[i] - 1) / cache[i]);
                k = k % cache[i];
                if (k === 0) {
                    k = cache[i];
                }
                result.push(getCandidate(quotient, used));
            }
            result.push(getCandidate(k, used));
            result.push(getCandidate(1, used));
            return result.join('');
        }
        return '1';
    }
    throw new Error(`One of the two input numbers ${n}, ${k} is less than 0`);
}
