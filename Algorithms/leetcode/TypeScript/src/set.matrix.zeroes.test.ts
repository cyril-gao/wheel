import { setZeroes } from "./set.matrix.zeroes";

function equals<T>(m1: T[][], m2: T[][]): boolean {
    let retval = m1.length === m2.length && m1[0].length === m2[0].length;
    if (retval) {
        for (let i = 0; i < m1.length && retval; ++i) {
            for (let j = 0; j < m1[0].length; ++j) {
                if (m1[i][j] !== m2[i][j]) {
                    retval = false;
                    break;
                }
            }
        }
    }
    return retval;
}

test(
    "check the result value of the call to the function setZeroes",
    () => {
        let matrix = [[1, 1, 1], [1, 0, 1], [1, 1, 1]];
        let expectation = [[1, 0, 1], [0, 0, 0], [1, 0, 1]];
        setZeroes(matrix);
        expect(equals(matrix, expectation)).toBe(true);

        matrix = [[0, 1, 2, 0], [3, 4, 5, 2], [1, 3, 1, 5]];
        expectation = [[0, 0, 0, 0], [0, 4, 5, 0], [0, 3, 1, 0]];
        setZeroes(matrix);
        expect(equals(matrix, expectation)).toBe(true);
    }
);
