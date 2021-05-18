/*
Given an m x n matrix. If an element is 0, set its entire row and column to 0.
Do it in-place.

Follow up:
    1. A straight forward solution using O(mn) space is probably a bad idea.
    2. A simple improvement uses O(m + n) space, but still not the best solution.
    3. Could you devise a constant space solution?
*/

function clearRow(matrix: number[][], row: number): void {
    for (let j = 0; j < matrix[row].length; ++j) {
        matrix[row][j] = 0;
    }
}

function clearCol(matrix: number[][], col: number): void {
    for (let i = 0; i < matrix.length; ++i) {
        matrix[i][col] = 0;
    }
}

export function setZeroes(matrix: number[][]): void {
    let m = matrix.length;
    if (m > 0) {
        let n = matrix[0].length;
        if (n > 0) {
            let row = undefined, col = undefined;
            for (let i = 0; i < m && row === undefined; ++i) {
                for (let j = 0; j < n; ++j) {
                    if (matrix[i][j] === 0) {
                        row = i;
                        col = j;
                        break;
                    }
                }
            }
            if (row !== undefined) {
                for (let i = row; i < m; ++i) {
                    for (let j = 0; j < n; ++j) {
                        if (matrix[i][j] === 0) {
                            matrix[i][col] = 0;
                            matrix[row][j] = 0;
                        }
                    }
                }
                for (let i = 0; i < m; ++i) {
                    if (i !== row) {
                        if (matrix[i][col] === 0) {
                            clearRow(matrix, i);
                        }
                    }
                }
                for (let j = 0; j < n; ++j) {
                    if (matrix[row][j] === 0) {
                        clearCol(matrix, j);
                    }
                }
                clearRow(matrix, row);
            }
        }
    }
}
