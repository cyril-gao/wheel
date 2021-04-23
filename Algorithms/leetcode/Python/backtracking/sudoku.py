from typing import List
from copy import deepcopy

'''
Write a program to solve a Sudoku puzzle by filling the empty cells.

A sudoku solution must satisfy all of the following rules:

Each of the digits 1-9 must occur exactly once in each row.
Each of the digits 1-9 must occur exactly once in each column.
Each of the digits 1-9 must occur exactly once in each of the 9 3x3 sub-boxes of the grid.
The '.' character indicates empty cells.
'''


def fill_empty_cells(board: List[List[str]]) -> None:
    class Cache:
        def get_grid_index(self, row, col):
            return (row // 3) * 3 + (col // 3)

        def __init__(self, board: List[List[str]]):
            self.rows = [set([_ for _ in range(1, 10)]) for _ in range(9)]
            self.cols = [set([_ for _ in range(1, 10)]) for _ in range(9)]
            self.grids = [set([_ for _ in range(1, 10)]) for _ in range(9)]
            for i in range(9):
                for j in range(9):
                    v = board[i][j]
                    if v.isdigit():
                        v = int(v)
                        self.rows[i].discard(v)
                        self.cols[j].discard(v)
                        self.grids[self.get_grid_index(i, j)].discard(v)

        def get_candidates(self, row, col):
            s1 = self.rows[row]
            s2 = self.cols[col]
            s3 = self.grids[self.get_grid_index(row, col)]
            return list(s1 & s2 & s3)

        def remove_candidate(self, row, col, d):
            self.rows[row].discard(d)
            self.cols[col].discard(d)
            self.grids[self.get_grid_index(row, col)].discard(d)

        def add_candidate(self, row, col, d):
            self.rows[row].add(d)
            self.cols[col].add(d)
            self.grids[self.get_grid_index(row, col)].add(d)

    def next(
        board: List[List[str]],
        row: int,
        col: int,
        cache
    ):
        while row < 9 and col < 9:
            if board[row][col].isdigit():
                col += 1
                if col >= 9:
                    col -= 9
                    row += 1
            else:
                break

        if row < 9 and col < 9:
            candidates = cache.get_candidates(row, col)
            for c in candidates:
                board[row][col] = str(c)
                cache.remove_candidate(row, col, c)
                new_row = row
                new_col = col + 1
                if new_col >= 9:
                    new_col -= 9
                    new_row += 1
                retval = next(board, new_row, new_col, cache)
                cache.add_candidate(row, col, c)
                board[row][col] = '.'
                if retval:
                    return True
            return False
        else:
            cache.result = deepcopy(board)
            return True

    assert len(board) == 9 and len(board[0]) == 9
    cache = Cache(board)
    if (next(board, 0, 0, cache)):
        for row in range(9):
            for col in range(9):
                board[row][col] = cache.result[row][col]
