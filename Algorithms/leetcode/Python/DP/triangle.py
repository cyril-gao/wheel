from typing import List, TypeVar


T = TypeVar('T')


def minimum_path_in_triangle(triangle: List[List[T]]) -> T:
    retval = 0
    m = len(triangle) if triangle is not None else 0
    if m > 1:
        cache = triangle[m-1][:]
        for i in range(m-2, -1, -1):
            for j in range(len(triangle[i])):
                cache[j] = min(
                    cache[j], cache[j+1]
                ) + triangle[i][j]
        retval = cache[0]
    else:
        if m == 1:
            retval = min(triangle[0])
    return retval
