/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

How many possible unique paths are there?
*/

export function uniquePaths(m: number, n: number): number {
    let cache = new Array<number[]>(m);
    for (let i = 0; i < m; ++i) {
        cache[i] = new Array<number>(n);
        cache[i].fill(i !== 0 ? 0 : 1);
    }
    for (let i = 0; i < m; ++i) {
        cache[i][0] = 1;
    }
    for (let i = 1; i < m; ++i) {
        for (let j = 1; j < n; ++j) {
            cache[i][j] = cache[i][j - 1] + cache[i - 1][j];
        }
    }
    return cache[m - 1][n - 1];
}


/*
A robot is located at the top-left corner of a m x n grid (marked 'Start' in the diagram below).

The robot can only move either down or right at any point in time. The robot is trying to reach the bottom-right corner of the grid (marked 'Finish' in the diagram below).

Now consider if some obstacles are added to the grids. How many unique paths would there be?

An obstacle and space is marked as 1 and 0 respectively in the grid.
*/

export function uniquePathsWithObstacles(obstacleGrid: number[][]): number {
    let m = obstacleGrid.length;
    let n = obstacleGrid[0].length;
    let cache = new Array<number[]>(m);
    for (let i = 0; i < m; ++i) {
        cache[i] = new Array<number>(n);
        cache[i].fill(0);
    }
    for (let j = 0; j < n; ++j) {
        if (obstacleGrid[0][j] === 0) {
            cache[0][j] = 1;
        } else {
            break;
        }
    }
    if (cache[0][0] > 0) {
        for (let i = 1; i < m; ++i) {
            if (obstacleGrid[i][0] === 0) {
                cache[i][0] = 1;
            } else {
                break;
            }
        }
        for (let i = 1; i < m; ++i) {
            for (let j = 1; j < n; ++j) {
                if  (obstacleGrid[i][j] === 0) {
                    cache[i][j] = cache[i][j - 1] + cache[i - 1][j];
                }
            }
        }
        return cache[m - 1][n - 1];
    } else {
        return 0;
    }
}


/*
Given a m x n grid filled with non-negative numbers, find a path from top left to bottom right,
which minimizes the sum of all numbers along its path.

Note: You can only move either down or right at any point in time.

Example 1:
Input: grid = [[1,3,1],[1,5,1],[4,2,1]]
Output: 7
Explanation: Because the path 1 → 3 → 1 → 1 → 1 minimizes the sum.

Example 2:
Input: grid = [[1,2,3],[4,5,6]]
Output: 12
*/

export function minPathSum(grid: number[][]): number {
    let m = grid.length;
    let n = grid[0].length;
    let cache = new Array<number[]>(m);
    for (let i = 0; i < m; ++i) {
        cache[i] = [...grid[i]];
    }
    for (let j = 1; j < n; ++j) {
        cache[0][j] += cache[0][j - 1];
    }
    for (let i = 1; i < m; ++i) {
        cache[i][0] += cache[i - 1][0];
    }
    for (let i = 1; i < m; ++i) {
        for (let j = 1; j < n; ++j) {
            cache[i][j] += Math.min(cache[i][j - 1], cache[i - 1][j]);
        }
    }
    return cache[m - 1][n - 1];
}
