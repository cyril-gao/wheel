/*
Given a positive integer n, find the least number of perfect square numbers (for example, 1, 4, 9, 16, ...) which sum to n.

Example 1:
Input: n = 12
Output: 3 
Explanation: 12 = 4 + 4 + 4.

Example 2:
Input: n = 13
Output: 2
Explanation: 13 = 4 + 9.
*/

export function numSquares(n: number): number {
    let retval = 0;
    if (n > 0) {
        let s = Math.floor(Math.sqrt(n));
        let queue: [number, number, number][] = [];
        for (let i = s, j = 0; i >= 1 && j < 16; --i, ++j) {
            let v = i * i;
            queue.push([v, n - v, 1]);
        }
        while (queue.length > 0) {
            let front = queue.shift();
            if (front[1] === 0) {
                retval = front[2];
                break;
            }
            s = Math.floor(Math.sqrt(front[1]));
            for (let i = s, j = 0; i >= 1 && j < 16; --i, ++j) {
                let v = i * i;
                queue.push([v, front[1] - v, front[2] + 1]);
            }
        }
    }
    return retval;
};