import { solveNQueens, totalNQueens } from "./n.queens";

test(
    "check the result value of the call to the function solveNQueens",
    () => {
        let result = solveNQueens(1);
        expect(result.length).toEqual(1);
        expect(result[0].length).toEqual(1);
        expect(result[0][0]).toEqual('Q');

        result = solveNQueens(2);
        expect(result.length).toEqual(0);
        result = solveNQueens(3);
        expect(result.length).toEqual(0);

        result = solveNQueens(4);
        expect(result.length).toEqual(2);

        result = solveNQueens(5);
        expect(result.length).toEqual(10);
    }
);

test(
    "check the result value of the call to the function totalNQueens",
    () => {
        let result = totalNQueens(1);
        expect(result).toEqual(1);

        result = totalNQueens(2);
        expect(result).toEqual(0);

        result = totalNQueens(4);
        expect(result).toEqual(2);

        result = totalNQueens(5);
        expect(result).toEqual(10);
    }
);
