/*
Write an efficient algorithm that searches for a value in an m x n matrix. This matrix has the following properties:
    1. Integers in each row are sorted from left to right.
    2. The first integer of each row is greater than the last integer of the previous row.
*/

function at<T>(matrix: T[][], index: number): T {
    let row = Math.floor(index / matrix[0].length);
    let col = index % matrix[0].length;
    return matrix[row][col];
}

export function searchMatrix<T>(matrix: T[][], target: T): boolean {
    let retval = false;
    let m = matrix.length;
    if (m > 0) {
        let n = matrix[0].length;
        if (n > 0) {
            let begin = 0;
            let end = m * n;
            let mid = end;
            while (begin < end) {
                mid = Math.floor((begin + end) / 2);
                let v = at(matrix, mid);
                if (v > target) {
                    end = mid;
                    mid = begin;
                } else if (v < target) {
                    begin = mid + 1;
                    mid = end;
                } else {
                    break;
                }
            }
            if (mid !== (m * n) && at(matrix, mid) === target) {
                retval = true;
            }
        }
    }
    return retval;
}
