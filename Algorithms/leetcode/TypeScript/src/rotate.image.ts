/**
 * You are given an n x n 2D matrix representing an image, rotate the image by 90 degrees (clockwise).
 * You have to rotate the image in-place, which means you have to modify the input 2D matrix directly.
 * DO NOT allocate another 2D matrix and do the rotation, modify matrix in-place instead.
 */
export function rotate(matrix: number[][]): void {
    let topRow = 0;
    let leftCol = 0;
    let bottomRow = matrix.length - 1;
    let rightCol = bottomRow;
    while (topRow < bottomRow) {
        for (let i = 0, ie = bottomRow - topRow; i < ie; ++i) {
            let old1 = matrix[topRow + i][rightCol];
            matrix[topRow + i][rightCol] = matrix[topRow][leftCol + i];
            let old2 = matrix[bottomRow][rightCol - i];
            matrix[bottomRow][rightCol - i] = old1;
            old1 = matrix[bottomRow - i][leftCol];
            matrix[bottomRow - i][leftCol] = old2;
            matrix[topRow][leftCol + i] = old1;
        }
        ++topRow;
        --bottomRow;
        ++leftCol;
        --rightCol;
    }
}


/*
Given an m x n matrix, return all elements of the matrix in spiral order.
*/
export function spiralOrder<T>(matrix: T[][]): T[] {
    let retval = [];
    let m = matrix.length;
    if (m > 0) {
        let n = matrix[0].length;
        if (n > 0) {
            retval = new Array<T>(m * n);
            let outputIndex = 0;
            let topRow = 0;
            let bottomRow = m - 1;
            let leftCol = 0;
            let rightCol = n - 1;
            while (topRow <= bottomRow && leftCol <= rightCol) {
                for (let i = 0, ie = rightCol - leftCol + 1; i < ie; ++i) {
                    retval[outputIndex++] = matrix[topRow][leftCol + i];
                }
                for (let i = 0, ie = bottomRow - topRow - 1; i < ie; ++i) {
                    retval[outputIndex++] = matrix[topRow + 1 + i][rightCol];
                }
                if (topRow < bottomRow) {
                    for (let i = 0, ie = rightCol - leftCol + 1; i < ie; ++i) {
                        retval[outputIndex++] = matrix[bottomRow][rightCol - i];
                    }
                }
                if (leftCol < rightCol) {
                    for (let i = 0, ie = bottomRow - topRow - 1; i < ie; ++i) {
                        retval[outputIndex++] = matrix[bottomRow - 1 - i][leftCol];
                    }
                }
                ++topRow;
                --bottomRow;
                ++leftCol;
                --rightCol;
            }
        }
    }
    return retval;
}


/*
Given a positive integer n, generate an n x n matrix filled with elements
from 1 to n2 in spiral order.
*/

export function generateMatrix(n: number): number[][] {
    if (n > 0) {
        let retval = new Array<number[]>(n);
        for (let i = 0; i < n; ++i) {
            retval[i] = new Array<number>(n);
        }
        let nextNumber = 0;
        let topRow = 0;
        let bottomRow = n - 1;
        let leftCol = 0;
        let rightCol = n - 1;
        while (topRow <= bottomRow && leftCol <= rightCol) {
            for (let i = 0, ie = rightCol - leftCol + 1; i < ie; ++i) {
                retval[topRow][leftCol + i] = ++nextNumber;
            }
            for (let i = 0, ie = bottomRow - topRow - 1; i < ie; ++i) {
                retval[topRow + 1 + i][rightCol] = ++nextNumber;
            }
            if (topRow < bottomRow) {
                for (let i = 0, ie = rightCol - leftCol + 1; i < ie; ++i) {
                    retval[bottomRow][rightCol - i] = ++nextNumber;
                }
            }
            if (leftCol < rightCol) {
                for (let i = 0, ie = bottomRow - topRow - 1; i < ie; ++i) {
                    retval[bottomRow - 1 - i][leftCol] = ++nextNumber;
                }
            }
            ++topRow;
            --bottomRow;
            ++leftCol;
            --rightCol;
        }
        return retval;
    } else {
        throw new Error(`Bad number: ${n}, it must be bigger than 0`);
    }
}
