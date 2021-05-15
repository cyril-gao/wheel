import { merge } from "./merge.intervals";

function equals(m1: number[][], m2: number[][]): boolean {
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
    "check the result value of the call to the function merge",
    () => {
        let intervals = [[1, 3], [2, 6], [8, 10], [15, 18]];
        let result = merge(intervals);
        let expectation = [[1, 6], [8, 10], [15, 18]];
        expect(equals(result, expectation)).toBe(true);

        intervals = [[1, 4], [4, 5]];
        result = merge(intervals);
        expectation = [[1, 5]];
        expect(equals(result, expectation)).toBe(true);

        intervals = [[1, 4], [0, 2], [3, 5]];
        result = merge(intervals);
        expectation = [[0, 5]];
        expect(equals(result, expectation)).toBe(true);
    }
);
