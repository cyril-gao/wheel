import { rotate, spiralOrder, generateMatrix, rotateArray } from "./rotate.image";

test(
    "check the result value of the call to the function rotate",
    () => {
        let matrix = [
            [1, 2, 3],
            [4, 5, 6],
            [7, 8, 9]
        ];
        let result = [
            [7, 4, 1],
            [8, 5, 2],
            [9, 6, 3]
        ];
        rotate(matrix);
        for (let i = 0; i < result.length; ++i) {
            for (let j = 0; j < result[0].length; ++j) {
                expect(matrix[i][j]).toEqual(result[i][j]);
            }
        }

        matrix = [
            [5, 1, 9, 11],
            [2, 4, 8, 10],
            [13, 3, 6, 7],
            [15, 14, 12, 16]
        ];
        result = [
            [15, 13, 2, 5],
            [14, 3, 4, 1],
            [12, 6, 8, 9],
            [16, 7, 10, 11]
        ];
        rotate(matrix);
        for (let i = 0; i < result.length; ++i) {
            for (let j = 0; j < result[0].length; ++j) {
                expect(matrix[i][j]).toEqual(result[i][j]);
            }
        }
    }
);

test(
    "check the result value of the call to the function spiralOrder",
    () => {
        let matrix = [
            [1, 2, 3],
            [4, 5, 6],
            [7, 8, 9]
        ];
        let result = spiralOrder(matrix);
        let expectation = [1, 2, 3, 6, 9, 8, 7, 4, 5];
        expect(result.length).toEqual(expectation.length);
        for (let i = 0; i < result.length; ++i) {
            expect(result[i]).toEqual(expectation[i]);
        }

        matrix = [
            [1, 2, 3, 4, 5],
            [6, 7, 8, 9, 10],
            [11, 12, 13, 14, 15]
        ];
        result = spiralOrder(matrix);
        expectation = [1, 2, 3, 4, 5, 10, 15, 14, 13, 12, 11, 6, 7, 8, 9];
        expect(result.length).toEqual(expectation.length);
        for (let i = 0; i < result.length; ++i) {
            expect(result[i]).toEqual(expectation[i]);
        }

        matrix = [
            [1, 2, 3],
            [4, 5, 6],
            [7, 8, 9],
            [10, 11, 12],
            [13, 14, 15]
        ];
        result = spiralOrder(matrix);
        expectation = [1, 2, 3, 6, 9, 12, 15, 14, 13, 10, 7, 4, 5, 8, 11];
        expect(result.length).toEqual(expectation.length);
        for (let i = 0; i < result.length; ++i) {
            expect(result[i]).toEqual(expectation[i]);
        }
    }
);

test(
    "check the result value of the call to the function generateMatrix",
    () => {
        let expectation = [[1]];
        let result = generateMatrix(1);
        expect(result.length).toEqual(expectation.length);
        for (let i = 0; i < result.length; ++i) {
            for (let j = 0; j < result[i].length; ++j) {
                expect(result[i][j]).toEqual(expectation[i][j]);
            }
        }

        expectation = [[1, 2], [4, 3]];
        result = generateMatrix(2);
        expect(result.length).toEqual(expectation.length);
        for (let i = 0; i < result.length; ++i) {
            for (let j = 0; j < result[i].length; ++j) {
                expect(result[i][j]).toEqual(expectation[i][j]);
            }
        }

        expectation = [[1, 2, 3], [8, 9, 4], [7, 6, 5]];
        result = generateMatrix(3);
        expect(result.length).toEqual(expectation.length);
        for (let i = 0; i < result.length; ++i) {
            for (let j = 0; j < result[i].length; ++j) {
                expect(result[i][j]).toEqual(expectation[i][j]);
            }
        }

        expectation = [[1, 2, 3, 4], [12, 13, 14, 5], [11, 16, 15, 6], [10, 9, 8, 7]];
        result = generateMatrix(4);
        expect(result.length).toEqual(expectation.length);
        for (let i = 0; i < result.length; ++i) {
            for (let j = 0; j < result[i].length; ++j) {
                expect(result[i][j]).toEqual(expectation[i][j]);
            }
        }
    }
);

function rotateArray2<T>(elements: T[], k: number): void {
    if (elements.length > 0) {
        k %= elements.length;
        if (k > 0) {
            let tmp = new Array<T>(k);
            for (let i = k - 1, j = elements.length - 1; i >= 0; --i, --j) {
                tmp[i] = elements[j];
            }
            for (let i = elements.length - 1, j = i - k; j >= 0; --i, --j) {
                elements[i] = elements[j];
            }
            for (let i = 0; i < k; ++i) {
                elements[i] = tmp[i];
            }
        }
    }
}

test(
    "check the result value of the call to the function rotateArray",
    () => {
        let input = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19];
        for (let k = 0; k <= input.length; ++k) {
            let copy1 = [...input];
            rotateArray(copy1, k);
            let copy2 = [...input];
            rotateArray2(copy2, k);
            for (let i = 0; i < input.length; ++i) {
                expect(copy1[i]).toEqual(copy2[i]);
            }
        }
    }
);
