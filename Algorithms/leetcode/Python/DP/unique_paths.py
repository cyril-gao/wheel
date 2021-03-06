from typing import List


def unique_paths(m, n):
    k = max(m, n)
    cache = [[0 for _ in range(k)] for _ in range(k)]
    cache[0][0] = 1
    for i in range(1, k):
        previous_i = i - 1

        cache[i][0] = cache[previous_i][0]
        for j in range(1, i):
            cache[i][j] = cache[previous_i][j] + cache[i][j-1]

        cache[0][i] = cache[0][previous_i]
        for j in range(1, i):
            cache[j][i] = cache[j-1][i] + cache[j][previous_i]

        cache[i][i] = cache[previous_i][i] + cache[i][previous_i]
    return cache[m-1][n-1]


def unique_paths_2(m, n):
    k = max(m, n)
    cache = [[0 for _ in range(k)] for _ in range(2)]
    cache[0][0] = cache[1][0] = 1
    previous_i = 0
    current_i = 1
    for i in range(1, k):
        previous_i = (i - 1) % 2
        current_i = i % 2
        for j in range(1, i):
            cache[current_i][j] = cache[previous_i][j] + cache[current_i][j-1]
        cache[current_i][i] = cache[current_i][i-1] * 2
    return cache[current_i][min(m, n)-1]


def unique_paths_with_obstacles(obstacle_grid: List[List[int]]) -> int:
    m = len(obstacle_grid)
    n = len(obstacle_grid[0])
    cache = [[0 for _ in range(n)] for _ in range(m)]
    if obstacle_grid[0][0] == 0:
        cache[0][0] = 1

        for i in range(1, max(m, n)):
            previous_i = i - 1
            if i < m:
                if obstacle_grid[i][0] == 0:
                    cache[i][0] = cache[previous_i][0]
                for j in range(1, min(i, n)):
                    if obstacle_grid[i][j] == 0:
                        cache[i][j] = cache[previous_i][j] + cache[i][j-1]
            if i < n:
                if obstacle_grid[0][i] == 0:
                    cache[0][i] = cache[0][previous_i]
                for j in range(1, min(i, m)):
                    if obstacle_grid[j][i] == 0:
                        cache[j][i] = cache[j-1][i] + cache[j][previous_i]
            if i < m and i < n:
                if obstacle_grid[i][i] == 0:
                    cache[i][i] = cache[previous_i][i] + cache[i][previous_i]
        return cache[m-1][n-1]
    else:
        return 0
