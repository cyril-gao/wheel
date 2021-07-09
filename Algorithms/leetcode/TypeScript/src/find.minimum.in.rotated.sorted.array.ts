/*
Suppose an array of length n sorted in ascending order is rotated between 1 and n times.
For example, the array nums = [0,1,4,4,5,6,7] might become:
    [4,5,6,7,0,1,4] if it was rotated 4 times.
    [0,1,4,4,5,6,7] if it was rotated 7 times.

Notice that rotating an array [a[0], a[1], a[2], ..., a[n-1]] 1 time results in the array
[a[n-1], a[0], a[1], a[2], ..., a[n-2]].

Given the sorted rotated array nums that may contain duplicates, return the minimum element of this array.
*/

function _findMin<T>(input: T[], begin: number, end: number): T {
    let retval = input[begin];
    let n = end - begin;
    if (n > 1) {
        let last = end - 1;
        if (input[begin] >= input[last]) {
            let mid = Math.floor((begin + end) / 2);
            if (input[mid] > input[last]) {
                retval = _findMin(input, mid + 1, end);
            } else if (input[mid] === input[last]) {
                if (input[begin] > input[last]) {
                    retval = _findMin(input, begin + 1, mid + 1);
                } else {
                    let lr = retval;
                    if (begin + 1 < mid) {
                        lr = _findMin(input, begin + 1, mid);
                    }
                    let rr = retval;
                    if (mid + 1 < end) {
                        rr = _findMin(input, mid + 1, end);
                    }
                    retval = lr <= rr ? lr : rr;
                }
            } else {
                retval = _findMin(input, begin + 1, mid + 1);
            }
        }
    }
    return retval;
}

export function findMin<T>(input: T[]): T {
    return _findMin(input, 0, input.length);
}
