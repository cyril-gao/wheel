from typing import List, TypeVar, Set, Tuple
from copy import copy

T = TypeVar('T')


'''
Given an array of unique elements, return all possible subsets (the power set).
The solution set must not contain duplicate subsets. Return the solution in any order.


Example 1:
Input: nums = [1,2,3]
Output: [[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

Example 2:
Input: nums = [0]
Output: [[],[0]]


Constraints:
- All the elements in the array are unique.
'''

def subsets(elements: List[T]) -> List[List[T]]:
    def next_step(
        elements: List[T],
        length: int,
        span: int,
        start: int,
        index: int,
        selected: List[T],
        result: List[List[T]]
    ):
        selected.append(elements[start])
        left = span - index - 1
        if left > 0:
            for i in range(start + 1, length - left + 1):
                next_step(elements, length, span, i, index + 1, selected, result)
        else:
            result.append(copy(selected))
        selected.pop()

    n = len(elements)
    retval = [[]]
    for span in range(1, n):
        for start in range(n - span + 1):
            next_step(elements, n, span, start, 0, [], retval)
    if n > 0:
        retval.append(copy(elements))
    return retval


'''
Given an array that may contain duplicates, return all possible subsets (the power set).

The solution set must not contain duplicate subsets. Return the solution in any order.
'''
def subsets_without_dup(elements: List[T]) -> List[List[T]]:
    def next_step(
        elements: List[T],
        start: int,
        remains: int,
        selected: List[T],
        result: Set[Tuple[T]]
    ):
        selected.append(elements[start])
        if remains > 0:
            n = len(elements)
            for i in range(start + 1, n - remains + 1):
                next_step(elements, i, remains - 1, selected, result)
        else:
            value = tuple(sorted(selected))
            result.add(value)
        selected.pop()

    retval = [[]]
    if elements:
        n = len(elements)
        result = set()
        for i in range(1, n + 1):
            for j in range(n - i + 1):
                next_step(elements, j, i - 1, [], result)
        for r in result:
            retval.append(list(r))
    return retval
