/*
Given a triangle array, return the minimum path sum from top to bottom.

For each step, you may move to an adjacent number of the row below. More formally,
if you are on index i on the current row, you may move to either index i or index
i + 1 on the next row.

Example 1:

Input: triangle = [[2],[3,4],[6,5,7],[4,1,8,3]]
Output: 11
Explanation: The triangle looks like:
   2
  3 4
 6 5 7
4 1 8 3
The minimum path sum from top to bottom is 2 + 3 + 5 + 1 = 11 (underlined above).

Example 2:
Input: triangle = [[-10]]
Output: -10
*/

export function minimumTotal(triangle: number[][]): number {
    let retval = Number.POSITIVE_INFINITY;
    if (triangle.length > 1) {
        let n = triangle[triangle.length - 1].length;
        let cache = new Array<Array<number>>(2);
        for (let i = 0; i < cache.length; ++i) {
            cache[i] = new Array<number>(n);
            cache[i].fill(Number.POSITIVE_INFINITY);
        }
        let current = 0;
        for (let i = 0; i < triangle[0].length; ++i) {
            cache[current][i] = triangle[0][i];
        }
        for (let i = 1; i < triangle.length; ++i) {
            let previous = current;
            current = (current + 1) % 2;
            for (let j = 0, jLast = triangle[i].length - 1; j < triangle[i].length; ++j) {
                if (j > 0 && j < jLast) {
                    cache[current][j] = Math.min(cache[previous][j - 1], cache[previous][j]) + triangle[i][j];
                } else {
                    if (j === 0) {
                        cache[current][j] = cache[previous][j] + triangle[i][j];
                    } else {
                        cache[current][j] = cache[previous][j - 1] + triangle[i][j];
                    }
                }
            }
        }
        retval = Math.min(...cache[current]);
    } else if (triangle.length === 1) {
        retval = Math.min(...triangle[0]);
    }
    return retval;
}
