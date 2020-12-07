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


def word_break(line: str, word_dict: Set[str]) -> List[str]:
    def next(
        word_dict: Set[str],
        len_dict: Set[int],
        line: str,
        n: int,
        start: int,
        tmp: List[str],
        result: List[str]
    ):
        if start < n:
            for last in range(start, n):
                next_index = last + 1
                l = next_index - start
                if l in len_dict:
                    w = line[start:next_index]
                    if w in word_dict:
                        tmp.append(w)
                        next(word_dict, len_dict, line,
                             n, next_index, tmp, result)
                        tmp.pop()
        else:
            result.append(' '.join(tmp))

    len_dict = set()
    for w in word_dict:
        len_dict.add(len(w))
    retval = []
    n = len(line) if line is not None else 0
    if n > 0:
        next(word_dict, len_dict, line, n, 0, [], retval)
    return retval


if __name__ == "__main__":
    word_dict = set(["a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa",
                     "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"])
    input = "aaaaaaaaaaaaaaaaaaaa"
    print(len(word_break(input, word_dict)))
