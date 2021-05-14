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
