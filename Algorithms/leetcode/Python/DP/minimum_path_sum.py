import copy
from typing import List


def minimum_path_sum(grid: List[List[int]]) -> int:
    m = len(grid)
    n = len(grid[0])

    cache = copy.deepcopy(grid)
    for i in range(1, max(m, n)):
        previous_i = i - 1
        if i < m:
            cache[i][0] += cache[previous_i][0]
            for j in range(1, min(i, n)):
                cache[i][j] += min(cache[i][j-1], cache[previous_i][j])
        if i < n:
            cache[0][i] += cache[0][previous_i]
            for j in range(1, min(i, m)):
                cache[j][i] += min(cache[j][previous_i], cache[j-1][i])
        if i < m and i < n:
            cache[i][i] += min(cache[previous_i][i], cache[i][previous_i])
    return cache[m-1][n-1]
