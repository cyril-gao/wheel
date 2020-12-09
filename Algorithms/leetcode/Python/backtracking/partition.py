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


def word_breaking_is_possible(line: str, word_dict: Set[str]) -> bool:
    def next(
        word_dict: Set[str],
        len_dict: Set[int],
        line: str,
        n: int,
        start: int
    ):
        if start < n:
            for last in range(n-1, start-1, -1):
                next_index = last + 1
                l = next_index - start
                if l in len_dict:
                    w = line[start:next_index]
                    if w in word_dict:
                        if next(word_dict, len_dict, line, n, next_index):
                            return True
            return False
        else:
            return True

    def for_ease_cases(
        line: str,
        word_dict: Set[str],
        unnormal_words: Set[str],
        normal_words: Set[str]
    ) -> bool:
        s1 = set(line)
        s2 = set()
        words = sorted(list(word_dict))
        for w in words:
            sw = set(w)
            if len(sw) < 2:
                unnormal_words.add(w)
            else:
                normal_words.add(w)
            s2 = s2 | sw
        return not bool(s1 - s2)

    def is_possible(
        line: str,
        n: int,
        word_dict: Set[str],
        len_dict: Set[int],
        unnormal_words: Set[str],
        normal_words: Set[str]
    ) -> bool:
        us = set()
        for w in unnormal_words:
            us = us | set(w)
        if len(us) < 2 and normal_words:
            for w in normal_words:
                i = line.find(w)
                next_index = i + len(w)
                if i > 0:
                    if (
                        next(word_dict, len_dict, line[0:i], i, 0) and
                        next(word_dict, len_dict,
                             line[next_index:], n - next_index, 0)
                    ):
                        return True
                elif i == 0:
                    if next(word_dict, len_dict, line[next_index:], n - next_index, 0):
                        return True
            return False
        else:
            return next(word_dict, len_dict, line, n, 0)

    len_dict = set()
    for w in word_dict:
        len_dict.add(len(w))
    n = len(line) if line is not None else 0
    retval = False
    if n > 0:
        unnormal_words = set()
        normal_words = set()
        retval = for_ease_cases(line, word_dict, unnormal_words, normal_words)
        if retval:
            retval = is_possible(
                line, n, word_dict, len_dict, unnormal_words, normal_words)
    return retval


if __name__ == "__main__":
    word_dict = set(["a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa",
                     "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"])
    input = "aaaaaaaaaaaaaaa"
    print(len(word_break(input, word_dict)))
