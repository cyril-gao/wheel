/*
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return all distinct solutions to the n-queens puzzle.

Each solution contains a distinct board configuration of the n-queens' placement, where 'Q' and '.' both indicate a queen and an empty space, respectively.
*/

function nextStep(
    n: number,
    row: number,
    col: number,
    selected: number[],
    result: string[][]
) {
    let valid = true;
    for (let i = 0; i < selected.length; ++i) {
        if (
            (selected[i] === col) ||
            (i - selected[i]) === (row - col) ||
            (i + selected[i]) === (row + col)
        ) {
            valid = false;
            break;
        }
    }
    if (valid) {
        selected.push(col);
        let nextRow = row + 1;
        if (nextRow < n) {
            for (let i = 0; i < n; ++i) {
                nextStep(n, nextRow, i, selected, result);
            }
        } else {
            let board = [];
            for (let i = 0; i < n; ++i) {
                let line = new Array<string>(n);
                line.fill('.');
                line[selected[i]] = 'Q';
                board.push(line.join(''));
            }
            result.push(board);
        }
        selected.pop();
    }
}

export function solveNQueens(n: number): string[][] {
    if (n > 0) {
        let retval = [];
        for (let i = 0; i < n; ++i) {
            nextStep(n, 0, i, [], retval);
        }
        return retval;
    }
    throw new Error(`Bad argument: ${n}, it must be bigger than 0`);
}


/*
The n-queens puzzle is the problem of placing n queens on an n x n chessboard such that no two queens attack each other.

Given an integer n, return the number of distinct solutions to the n-queens puzzle.
*/

function explorer(
    n: number,
    row: number,
    col: number,
    selectedCols: number[],
    result: number[]
) {
    let valid = true;
    for (let i = 0; i < row; ++i) {
        if (
            (selectedCols[i] === col) ||
            ((i - selectedCols[i]) === (row - col)) ||
            ((i + selectedCols[i]) === (row + col))
        ) {
            valid = false;
            break;
        }
    }
    if (valid) {
        selectedCols.push(col);
        let nextRow = row + 1;
        if (nextRow < n) {
            for (let i = 0; i < n; ++i) {
                explorer(n, nextRow, i, selectedCols, result);
            }
        } else {
            ++result[0];
        }
        selectedCols.pop();
    }
}

export function totalNQueens(n: number): number {
    let retval = 0;
    if (n > 0) {
        let result = [0];
        for (let i = 0; i < n; ++i) {
            explorer(n, 0, i, [], result);
        }
        retval = result[0];
    }
    return retval;
}
