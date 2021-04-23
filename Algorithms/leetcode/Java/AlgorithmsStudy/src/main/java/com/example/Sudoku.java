package com.example;

public class Sudoku {
    private static class SudokuValiator {
        private int[] counters;

        public SudokuValiator() {
            counters = new int[10];
        }

        public boolean check(char c) {
            int i = -1;
            switch (c) {
                case '1':
                    i = 1;
                    break;
                case '2':
                    i = 2;
                    break;
                case '3':
                    i = 3;
                    break;
                case '4':
                    i = 4;
                    break;
                case '5':
                    i = 5;
                    break;
                case '6':
                    i = 6;
                    break;
                case '7':
                    i = 7;
                    break;
                case '8':
                    i = 8;
                    break;
                case '9':
                    i = 9;
                    break;
                case '.':
                    return true;
                default:
                    break;
            }
            boolean retval = false;
            if (i >= 1 && i <= 9) {
                retval = (++counters[i] <= 1);
            }
            return retval;
        }
    }

    private boolean gridsValid(char[][] board) {
        for (int row = 0; row < 9; row += 3) {
            for (int col = 0; col < 9; col += 3) {
                SudokuValiator sv = new SudokuValiator();
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (!sv.check(board[row + i][col + j])) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    private boolean columnsValid(char[][] board) {
        for (int i = 0; i < 9; ++i) {
            SudokuValiator sv = new SudokuValiator();
            for (int j = 0; j < 9; ++j) {
                if (!sv.check(board[j][i])) {
                    return false;
                }
            }
        }
        return true;
    }

    private boolean rowsValid(char[][] board) {
        for (int i = 0; i < 9; ++i) {
            SudokuValiator sv = new SudokuValiator();
            for (int j = 0; j < 9; ++j) {
                if (!sv.check(board[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

    public boolean isValidSudoku(char[][] board) {
        boolean itIs = board.length == 9 && board[0].length == 9;
        if (itIs) {
            itIs = (rowsValid(board) && columnsValid(board) && gridsValid(board));
        }
        return itIs;
    }
}
