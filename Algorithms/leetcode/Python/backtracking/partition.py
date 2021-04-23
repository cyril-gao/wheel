from typing import List, Set
from copy import copy


def is_palindrome(word: str, start: int, last: int) -> bool:
    assert start <= last and last < len(word)
    while start < last:
        if word[start] != word[last]:
            return False
        start += 1
        last -= 1
    return True


def palindrome_partition(word: str) -> List[List[str]]:
    def next(
        word: str,
        n: int,
        start: int,
        tmp: List[str],
        result: List[List[str]]
    ):
        if start < n:
            for last in range(start, n):
                if is_palindrome(word, start, last):
                    next_index = last+1
                    tmp.append(word[start:next_index])
                    next(word, n, next_index, tmp, result)
                    tmp.pop()
        else:
            result.append(copy(tmp))

    retval = []
    n = len(word) if word is not None else 0
    if n > 0:
        next(word, n, 0, [], retval)
    return retval
