from typing import List, Tuple, Set, TypeVar
from copy import copy


T = TypeVar('T')


def permute(input: List[T]) -> List[List[T]]:
    def next(
        input: List[T],
        visited: List[bool],
        n: int, remains: int,
        intermediate_result: List[T],
        result: List[List[T]]
    ):
        if remains > 0:
            for i in range(n):
                if not visited[i]:
                    intermediate_result.append(input[i])
                    visited[i] = True
                    next(input, visited, n, remains-1,
                         intermediate_result, result)
                    visited[i] = False
                    intermediate_result.pop()
        else:
            result.append(copy(intermediate_result))

    retval = []
    n = len(input) if input is not None else 0
    if n > 0:
        visited = [False for _ in range(n)]
        next(input, visited, n, n, [], retval)
    return retval


def dedup_permute(input: List[T]) -> List[List[T]]:
    def next(
        input: List[T],
        visited: List[bool],
        n: int, remains: int,
        intermediate_result: List[T],
        result: Set[Tuple[T]]
    ):
        if remains > 0:
            for i in range(n):
                if not visited[i]:
                    intermediate_result.append(input[i])
                    visited[i] = True
                    next(input, visited, n, remains-1,
                         intermediate_result, result)
                    visited[i] = False
                    intermediate_result.pop()
        else:
            result.add(tuple(intermediate_result))

    retval = []
    n = len(input) if input is not None else 0
    if n > 0:
        output = set()
        visited = [False for _ in range(n)]
        next(input, visited, n, n, [], output)
        for t in output:
            retval.append(list(t))
    return retval


def subsets(input: List[T]) -> List[List[T]]:
    def next(
        input: List[T],
        n: int,
        start: int,
        remains: int,
        intermediate_result: List[T],
        result: Set[Tuple[T]]
    ):
        if remains > 0:
            for i in range(start, n-remains+1):
                intermediate_result.append(input[i])
                next(input, n, i+1, remains-1, intermediate_result, result)
                intermediate_result.pop()
        else:
            result.add(tuple(intermediate_result))
    retval = [[]]
    n = len(input) if input is not None else 0
    if n > 0:
        for remains in range(1, n+1):
            output = set()
            next(input, n, 0, remains, [], output)
            for t in output:
                retval.append(list(t))
    return retval


def dedup_subsets(input: List[T]) -> List[List[T]]:
    def next(
        input: List[T],
        n: int,
        start: int,
        remains: int,
        intermediate_result: List[T],
        result: Set[Tuple[T]]
    ):
        if remains > 0:
            for i in range(start, n-remains+1):
                intermediate_result.append(input[i])
                next(input, n, i+1, remains-1, intermediate_result, result)
                intermediate_result.pop()
        else:
            result.add(tuple(sorted(intermediate_result)))
    retval = [[]]
    n = len(input) if input is not None else 0
    if n > 0:
        for remains in range(1, n+1):
            output = set()
            next(input, n, 0, remains, [], output)
            for t in output:
                retval.append(list(t))
    return retval
