/*
Determine if a 9 x 9 Sudoku board is valid. Only the filled cells need to be validated according to the following rules:
1. Each row must contain the digits 1-9 without repetition.
2. Each column must contain the digits 1-9 without repetition.
3. Each of the nine 3 x 3 sub-boxes of the grid must contain the digits 1-9 without repetition.

Note:
1. A Sudoku board (partially filled) could be valid but is not necessarily solvable.
2. Only the filled cells need to be validated according to the mentioned rules.
*/
function getDigitMap(): Map<string, number> {
    let retval = new Map<string, number>();
    for (let i = 1; i < 10; ++i) {
        retval.set(i.toString(), i);
    }
    return retval;
}

const digitMap = getDigitMap();

function isValid(cell: string, digitSet: Set<number>): boolean {
    let d = digitMap.get(cell);
    if (d !== undefined) {
        if (!digitSet.has(d)) {
            digitSet.add(d);
        } else {
            return false;
        }
    }
    return true;
}

function rowsAreValid(board: string[][]): boolean {
    let retval = false;
    if (board.length == 9) {
        retval = true;
        for (let i = 0; i < 9 && retval; ++i) {
            if (board[i].length == 9) {
                let digitSet = new Set<number>();
                for (let j = 0; j < 9; ++j) {
                    if (!isValid(board[i][j], digitSet)) {
                        retval = false;
                        break;
                    }
                }
            } else {
                retval = false;
            }
        }
    }
    return retval;
}

function colsAreValid(board: string[][]): boolean {
    let retval = true;
    for (let j = 0; j < 9 && retval; ++j) {
        let digitSet = new Set<number>();
        for (let i = 0; i < 9; ++i) {
            if (!isValid(board[i][j], digitSet)) {
                retval = false;
                break;
            }
        }
    }
    return retval;
}

function gridsAreValid(board: string[][]): boolean {
    try {
        for (let i = 0; i < 3; ++i) {
            for (let j = 0; j < 3; ++j) {
                let digitSet = new Set<number>();
                for (let ii = 0, row = i * 3; ii < 3; ++ii, ++row) {
                    for (let jj = 0, col = j * 3; jj < 3; ++jj, ++col) {
                        if (!isValid(board[row][col], digitSet)) {
                            throw new Error("Invalid");
                        }
                    }
                }
            }
        }
    } catch (e) {
        return false;
    }
    return true;
}

export function isValidSudoku(board: string[][]): boolean {
    return rowsAreValid(board) && colsAreValid(board) && gridsAreValid(board);
}
