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


/*
Given a set of non-overlapping intervals, insert a new interval into the intervals (merge if necessary).

You may assume that the intervals were initially sorted according to their start times.

Example 1:
Input: intervals = [[1,3],[6,9]], newInterval = [2,5]
Output: [[1,5],[6,9]]

Example 2:
Input: intervals = [[1,2],[3,5],[6,7],[8,10],[12,16]], newInterval = [4,8]
Output: [[1,2],[3,10],[12,16]]
Explanation: Because the new interval [4,8] overlaps with [3,5],[6,7],[8,10].

Example 3:
Input: intervals = [], newInterval = [5,7]
Output: [[5,7]]

Example 4:
Input: intervals = [[1,5]], newInterval = [2,3]
Output: [[1,5]]

Example 5:
Input: intervals = [[1,5]], newInterval = [2,7]
Output: [[1,7]]
*/

function copy(source: number[][], begin: number, end: number, target: number[][]): void {
    for (; begin < end; ++begin) {
        target.push([...source[begin]]);
    }
}

export function insert(intervals: number[][], newInterval: number[]): number[][] {
    let retval = [];
    let end = intervals.length;
    let firstPosition = find(intervals, 0, end, (range: number[]) => range[0] - newInterval[0]);
    if (firstPosition !== end) {
        let secondPosition = find(intervals, firstPosition, end, (range: number[]) => range[0] - newInterval[1]);
        if (intervals[firstPosition][0] === newInterval[0]) {
            copy(intervals, 0, firstPosition, retval);
            if (secondPosition !== end) {
                if (intervals[secondPosition][0] === newInterval[1]) {
                    retval.push([newInterval[0], intervals[secondPosition][1]]);
                    copy(intervals, secondPosition + 1, end, retval);
                } else {
                    retval.push([newInterval[0], Math.max(newInterval[1], intervals[secondPosition - 1][1])]);
                    copy(intervals, secondPosition, end, retval);
                }
            } else {
                retval.push([newInterval[0], Math.max(newInterval[1], intervals[secondPosition - 1][1])]);
            }
        } else {
            let range = [...newInterval];
            let previousPosition = firstPosition - 1;
            if (previousPosition >= 0) {
                if (intervals[previousPosition][1] < newInterval[0]) {
                    copy(intervals, 0, firstPosition, retval);
                } else {
                    range[0] = intervals[previousPosition][0];
                    copy(intervals, 0, previousPosition, retval);
                }
            }
            if (secondPosition !== end) {
                if (intervals[secondPosition][0] === newInterval[1]) {
                    range[1] = intervals[secondPosition][1];
                    retval.push(range);
                    copy(intervals, secondPosition + 1, end, retval);
                } else {
                    previousPosition = secondPosition - 1;
                    if (previousPosition >= 0) {
                        range[1] = Math.max(newInterval[1], intervals[previousPosition][1]);
                    }
                    retval.push(range);
                    copy(intervals, secondPosition, end, retval);
                }
            } else {
                range[1] = Math.max(newInterval[1], intervals[secondPosition - 1][1]);
                retval.push(range);
            }
        }
    } else {
        --firstPosition;
        if (firstPosition >= 0) {
            if (intervals[firstPosition][1] < newInterval[0]) {
                copy(intervals, 0, end, retval);
                retval.push(newInterval);
            } else {
                copy(intervals, 0, firstPosition, retval);
                retval.push([intervals[firstPosition][0], Math.max(intervals[firstPosition][1], newInterval[1])]);
            }
        } else {
            retval.push([...newInterval]);
        }
    }
    return retval;
}
