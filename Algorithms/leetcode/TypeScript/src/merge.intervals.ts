/*
Given an array of intervals where intervals[i] = [starti, endi],
merge all overlapping intervals, and return an array of the non-overlapping
intervals that cover all the intervals in the input.

Example 1:
Input: intervals = [[1,3],[2,6],[8,10],[15,18]]
Output: [[1,6],[8,10],[15,18]]
Explanation: Since intervals [1,3] and [2,6] overlaps, merge them into [1,6].

Example 2:
Input: intervals = [[1,4],[4,5]]
Output: [[1,5]]
Explanation: Intervals [1,4] and [4,5] are considered overlapping.
*/

function find(intervals: number[][], begin: number, end: number, comp: (n: number[]) => number): number {
    let mid = end;
    while (begin < end) {
        mid = Math.floor((begin + end) / 2);
        let r = comp(intervals[mid]);
        if (r > 0) {
            end = mid;
            mid = begin;
        } else if (r < 0) {
            begin = mid + 1;
            mid = end;
        } else {
            break;
        }
    }
    return mid;
}

function maxSecondValue(intervals: number[][], begin: number, end: number, initial: number): number {
    let retval = initial;
    for (; begin < end; ++begin) {
        retval = Math.max(retval, intervals[begin][1]);
    }
    return retval;
}

export function merge(intervals: number[][]): number[][] {
    let retval = [];
    intervals.sort(
        (i1, i2) => i1[0] < i2[0] ? -1 : i1[0] > i2[0] ? 1 : i1[1] < i2[1] ? -1 : i1[1] > i2[1] ? 1 : 0
    );
    let candidate = intervals[0];
    for (let i = 1; i < intervals.length;) {
        let j = find(intervals, i, intervals.length, (range: number[]) => range[0] - candidate[1]);
        if (j !== intervals.length) {
            if (intervals[j][0] > candidate[1]) {
                candidate[1] = maxSecondValue(intervals, i, j, candidate[1]);
                if (candidate[1] < intervals[j][0]) {
                    retval.push(candidate);
                    candidate = intervals[j];
                    i = j + 1;
                } else {
                    i = j;
                }
            } else {
                candidate[1] = maxSecondValue(intervals, i, j + 1, candidate[1]);
                i = j + 1;
            }
        } else {
            candidate[1] = maxSecondValue(intervals, i, j, candidate[1]);
            break;
        }
    }
    retval.push(candidate);
    return retval;
}
