import { merge, insert } from "./merge.intervals";

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

test(
    "check the result value of the call to the function insert",
    () => {
        let intervals = [[1, 3], [6, 9]];
        let newInterval = [2, 5];
        let result = insert(intervals, newInterval);
        let expectation = [[1, 5], [6, 9]];
        expect(equals(result, expectation)).toBe(true);

        intervals = [[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]];
        newInterval = [4, 8];
        result = insert(intervals, newInterval);
        expectation = [[1, 2], [3, 10], [12, 16]];
        expect(equals(result, expectation)).toBe(true);

        intervals = [[10, 15], [18, 19]];
        newInterval = [3, 4];
        result = insert(intervals, newInterval);
        expectation = [[3, 4], [10, 15], [18, 19]];
        expect(equals(result, expectation)).toBe(true);

        intervals = [[0, 5], [9, 12]];
        newInterval = [7, 19];
        result = insert(intervals, newInterval);
        expectation = [[0, 5], [7, 19]];
        expect(equals(result, expectation)).toBe(true);

        intervals = [[0, 5], [8, 9]];
        newInterval = [3, 4];
        result = insert(intervals, newInterval);
        expectation = [[0, 5], [8, 9]];
        expect(equals(result, expectation)).toBe(true);

        intervals = [];
        newInterval = [4, 8];
        result = insert(intervals, newInterval);
        expectation = [[4, 8]];
        expect(equals(result, expectation)).toBe(true);

        intervals = [[1, 5]];
        newInterval = [4, 8];
        result = insert(intervals, newInterval);
        expectation = [[1, 8]];
        expect(equals(result, expectation)).toBe(true);

        intervals = [[1, 5]];
        newInterval = [2, 3];
        result = insert(intervals, newInterval);
        expectation = [[1, 5]];
        expect(equals(result, expectation)).toBe(true);

        intervals = [[6, 7], [8, 10], [12, 16]];
        newInterval = [1, 5];
        result = insert(intervals, newInterval);
        expectation = [[1, 5], [6, 7], [8, 10], [12, 16]];
        expect(equals(result, expectation)).toBe(true)

        intervals = [[6, 7], [8, 10], [12, 16]];
        newInterval = [1, 8];
        result = insert(intervals, newInterval);
        expectation = [[1, 10], [12, 16]];
        expect(equals(result, expectation)).toBe(true)

        intervals = [[6, 7], [8, 10], [12, 16]];
        newInterval = [1, 13];
        result = insert(intervals, newInterval);
        expectation = [[1, 16]];
        expect(equals(result, expectation)).toBe(true)

        intervals = [[6, 7], [8, 10], [12, 16]];
        newInterval = [1, 19];
        result = insert(intervals, newInterval);
        expectation = [[1, 19]];
        expect(equals(result, expectation)).toBe(true)

        intervals = [[2, 4], [6, 7], [8, 10], [12, 16]];
        newInterval = [2, 6];
        result = insert(intervals, newInterval);
        expectation = [[2, 7], [8, 10], [12, 16]];
        expect(equals(result, expectation)).toBe(true)

        intervals = [[2, 4], [6, 7], [8, 10], [12, 16]];
        newInterval = [2, 9];
        result = insert(intervals, newInterval);
        expectation = [[2, 10], [12, 16]];
        expect(equals(result, expectation)).toBe(true)

        intervals = [[2, 4], [6, 7], [8, 10], [12, 16]];
        newInterval = [2, 13];
        result = insert(intervals, newInterval);
        expectation = [[2, 16]];
        expect(equals(result, expectation)).toBe(true)

        intervals = [[2, 4], [6, 7], [8, 10], [12, 16]];
        newInterval = [2, 19];
        result = insert(intervals, newInterval);
        expectation = [[2, 19]];
        expect(equals(result, expectation)).toBe(true)

        intervals = [[2, 4], [6, 7], [8, 10], [12, 16]];
        newInterval = [13, 15];
        result = insert(intervals, newInterval);
        expectation = [[2, 4], [6, 7], [8, 10], [12, 16]];
        expect(equals(result, expectation)).toBe(true)

        intervals = [[2, 4], [6, 7], [8, 10], [12, 16]];
        newInterval = [16, 18];
        result = insert(intervals, newInterval);
        expectation = [[2, 4], [6, 7], [8, 10], [12, 18]];
        expect(equals(result, expectation)).toBe(true)

        intervals = [[2, 4], [6, 7], [8, 10], [12, 16]];
        newInterval = [17, 18];
        result = insert(intervals, newInterval);
        expectation = [[2, 4], [6, 7], [8, 10], [12, 16], [17, 18]];
        expect(equals(result, expectation)).toBe(true)
    }
);
