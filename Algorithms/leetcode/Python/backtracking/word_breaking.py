from typing import List, Set


'''
Given a non-empty string s and a dictionary wordDict containing a list of non-empty words, add spaces in s to construct a sentence where each word is a valid dictionary word. Return all such possible sentences.

Note:

The same word in the dictionary may be reused multiple times in the segmentation.
You may assume the dictionary does not contain duplicate words.
Example 1:

Input:
s = "catsanddog"
wordDict = ["cat", "cats", "and", "sand", "dog"]
Output:
[
  "cats and dog",
  "cat sand dog"
]
Example 2:

Input:
s = "pineapplepenapple"
wordDict = ["apple", "pen", "applepen", "pine", "pineapple"]
Output:
[
  "pine apple pen apple",
  "pineapple pen apple",
  "pine applepen apple"
]
Explanation: Note that you are allowed to reuse a dictionary word.
Example 3:

Input:
s = "catsandog"
wordDict = ["cats", "dog", "sand", "and", "cat"]
Output:
[]
'''


# if the return value is [], it means that it is impossible
def _word_break(patient: bool, line: str, word_set: Set[str]) -> List[str]:
    def for_ease_cases(
        line: str,
        word_set: Set[str],
        unnormal_words: Set[str],
        normal_words: Set[str]
    ) -> bool:
        s1 = set(line)
        s2 = set()
        for w in word_set:
            sw = set(w)
            if len(sw) < 2:
                unnormal_words.add(w)
            else:
                normal_words.add(w)
            s2 = s2 | sw
        return not bool(s1 - s2)

    def next(
        patient: bool,
        word_set: Set[str],
        len_set: Set[int],
        line: str,
        n: int,
        start: int,
        tmp: List[str],
        result: Set[str]
    ) -> bool:
        retval = False
        if start < n:
            for last in range(n-1, start-1, -1):
                next_index = last + 1
                l = next_index - start
                if l in len_set:
                    w = line[start:next_index]
                    if w in word_set:
                        tmp.append(w)
                        if next(patient, word_set, len_set, line, n, next_index, tmp, result):
                            retval = True
                            if not patient:
                                break
                        tmp.pop()
        else:
            result.add(' '.join(tmp))
            retval = True
        return retval

    def try_to_break_words(
        patient: bool,
        line: str,
        n: int,
        word_set: Set[str],
        len_set: Set[int],
        unnormal_words: Set[str],
        normal_words: Set[str],
        result: Set[str]
    ) -> bool:
        retval = False
        us = set()
        for w in unnormal_words:
            us = us | set(w)
        if unnormal_words and len(us) < 2 and normal_words:
            for w in normal_words:
                i = line.find(w)
                next_index = i + len(w)
                if i > 0:
                    lr = set()
                    rr = set()
                    if (
                        next(patient, word_set, len_set, line[0:i], i, 0, [], lr) and
                        next(patient, word_set, len_set,
                             line[next_index:], n - next_index, 0, [], rr)
                    ):
                        for l in lr:
                            assert l
                            if n > next_index:
                                for r in rr:
                                    assert r
                                    result.add("%s %s %s" % (l, w, r))
                            else:
                                result.add("%s %s" % (l, w))
                        retval = True
                        if not patient:
                            break
                elif i == 0:
                    rr = set()
                    if next(patient, word_set, len_set, line[next_index:], n - next_index, 0, [], rr):
                        if n > next_index:
                            for r in rr:
                                assert r
                                result.add("%s %s" % (w, r))
                        retval = True
                        if not patient:
                            break
        else:
            retval = next(patient, word_set, len_set, line, n, 0, [], result)
        return retval

    retval = []
    len_set = set()
    for w in word_set:
        len_set.add(len(w))
    n = len(line) if line is not None else 0
    if n > 0:
        unnormal_words = set()
        normal_words = set()
        if for_ease_cases(line, word_set, unnormal_words, normal_words):
            result = set()
            if try_to_break_words(patient, line, n, word_set, len_set, unnormal_words, normal_words, result):
                retval = list(result)
    return retval


def word_break(line: str, word_set: Set[str]) -> List[str]:
    return _word_break(True, line, word_set)


def word_breaking_is_possible(line: str, word_set: Set[str]) -> bool:
    return bool(_word_break(False, line, word_set))
