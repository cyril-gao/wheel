import { solve } from "./surrounded.regions";

test(
    "check the result value of the call to the function solve",
    () => {
        let board = [
            ['X', 'X', 'X', 'X', 'X', 'X', 'X'],
            ['X', 'X', 'O', 'X', 'O', 'X', 'X'],
            ['X', 'O', 'X', 'X', 'O', 'O', 'O'],
            ['X', 'X', 'O', 'O', 'X', 'X', 'X'],
            ['O', 'X', 'O', 'X', 'O', 'O', 'X'],
            ['O', 'O', 'X', 'X', 'X', 'X', 'X'],
        ];
        let expectation = [
            ['X', 'X', 'X', 'X', 'X', 'X', 'X'],
            ['X', 'X', 'X', 'X', 'O', 'X', 'X'],
            ['X', 'X', 'X', 'X', 'O', 'O', 'O'],
            ['X', 'X', 'X', 'X', 'X', 'X', 'X'],
            ['O', 'X', 'X', 'X', 'X', 'X', 'X'],
            ['O', 'O', 'X', 'X', 'X', 'X', 'X']
        ];
        solve(board);
        expect(board).toEqual(expectation);

        board = [
            ['X', 'X', 'X', 'X'],
            ['X', 'O', 'O', 'X'],
            ['X', 'X', 'O', 'X'],
            ['X', 'O', 'X', 'X']
        ];
        expectation = [
            ['X', 'X', 'X', 'X'],
            ['X', 'X', 'X', 'X'],
            ['X', 'X', 'X', 'X'],
            ['X', 'O', 'X', 'X']
        ];
        solve(board);
        expect(board).toEqual(expectation);
    }
);
