import { rotate, spiralOrder } from "./rotate.image";

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
