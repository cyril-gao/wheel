from typing import List


def minimum_distance(word1: str, word2: str) -> int:
    def calculate_distance(word1, word2, i, j, cache):
        v1 = cache[i+1][j] + 1
        v2 = cache[i][j+1] + 1
        v3 = cache[i+1][j+1] + 1
        if word1[i] == word2[j]:
            v3 -= 1
        return min(v1, v2, v3)

    m = len(word1)
    n = len(word2)
    cache = [[0 for _ in range(n + 1)] for _ in range(m+1)]
    for i in range(n):
        cache[m][i] = n - i
    for i in range(m):
        cache[i][n] = m - i
    row = m-1
    col = n-1
    while row >= 0 and col >= 0:
        cache[row][col] = calculate_distance(word1, word2, row, col, cache)
        for j in range(col-i, -1, -1):
            cache[row][j] = calculate_distance(word1, word2, row, j, cache)
        for i in range(row-1, -1, -1):
            cache[i][col] = calculate_distance(word1, word2, i, col, cache)
        row -= 1
        col -= 1
    return cache[0][0]


def minimum_distance_2(word1: str, word2: str) -> int:
    def calculate_distance(
        word1: str, word2: str,
        i: int, j: int, start: int,
        two_values: List[int], value: int
    ) -> int:
        v1 = value + 1
        v2 = two_values[start] + 1
        v3 = two_values[start+1] + 1
        if word1[i] == word2[j]:
            v3 -= 1
        return min(v1, v2, v3)

    m = len(word1)
    n = len(word2)
    row_cache = [[0 for _ in range(n+1)] for _ in range(2)]
    col_cache = [[0 for _ in range(m+1)] for _ in range(2)]

    for i in range(n):
        row_cache[0][i] = n - i
    for i in range(m):
        col_cache[0][i] = m - i
    row = m - 1
    col = n - 1
    current = 0
    while row >= 0 and col >= 0:
        previous = current
        current = (current + 1) % 2
        v = calculate_distance(
            word1, word2,
            row, col, col,
            row_cache[previous], col_cache[previous][row]
        )
        row_cache[current][col] = col_cache[current][row] = v
        for j in range(col-1, -1, -1):
            row_cache[current][j] = calculate_distance(
                word1, word2,
                row, j, j,
                row_cache[previous], row_cache[current][j+1]
            )
        for i in range(row-1, -1, -1):
            col_cache[current][i] = calculate_distance(
                word1, word2,
                i, col, i,
                col_cache[previous], col_cache[current][i+1]
            )
        row -= 1
        col -= 1
    if m >= n:
        return col_cache[current][0]
    else:
        return row_cache[current][0]
