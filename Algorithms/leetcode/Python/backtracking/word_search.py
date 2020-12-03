from typing import List


def exist(board: List[List[str]], word: str) -> bool:
    class Position:
        def __init__(self, found=False, row=None, col=None):
            self.exist = found
            self.row = row
            self.col = col

        def set(self, row, col):
            self.row = row
            self.col = col

        def get_positions_of(self, c, board, m, n, visited):
            retval = []
            row = self.row - 1
            if row >= 0 and board[row][self.col] == c and tuple((row, self.col)) not in visited:
                retval.append(Position(True, row, self.col))
            row += 2
            if row < m and board[row][self.col] == c and tuple((row, self.col)) not in visited:
                retval.append(Position(True, row, self.col))
            col = self.col - 1
            if col >= 0 and board[self.row][col] == c and tuple((self.row, col)) not in visited:
                retval.append(Position(True, self.row, col))
            col += 2
            if col < n and board[self.row][col] == c and tuple((self.row, col)) not in visited:
                retval.append(Position(True, self.row, col))
            return retval

    def next(board, m, n, word, l, i, position, visited) -> bool:
        next_index = i + 1
        if next_index < l:
            assert word[i] == board[position.row][position.col]
            rc = tuple((position.row, position.col))
            visited.add(rc)
            for p in position.get_positions_of(word[next_index], board, m, n, visited):
                if next(board, m, n, word, l, next_index, p, visited):
                    return True
            visited.remove(rc)
            return False
        else:
            return True

    m = len(board) if board is not None else 0
    if m > 0:
        n = len(board[0]) if board[0] is not None else 0
        if n > 0:
            l = len(word) if word is not None else 0
            if l > 0 and (m*n) >= l:
                c = word[0]
                visited = set()
                for row in range(m):
                    for col in range(n):
                        if board[row][col] == c:
                            if next(board, m, n, word, l, 0, Position(True, row, col), visited):
                                return True
    return False
