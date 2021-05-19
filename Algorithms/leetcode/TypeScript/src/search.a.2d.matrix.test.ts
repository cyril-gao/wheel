import { searchMatrix } from './search.a.2d.matrix';

test(
    "check the result value of the call to the function searchMatrix",
    () => {
        let matrix = [[1, 3, 5, 7], [10, 11, 16, 20], [23, 30, 34, 60]];
        let existent = [...matrix[1], ...matrix[2], ...matrix[0]];
        for (let e of existent) {
            expect(searchMatrix(matrix, e)).toBe(true);
        }

        let nonexistent = [0, 2, 4, 6, 8, 9, 12, 13, 14, 15, 17, 18, 19, 21, 22, 35, 37, 50, 55, 61];
        for (let n of nonexistent) {
            expect(searchMatrix(matrix, n)).toBe(false);
        }
    }
);
