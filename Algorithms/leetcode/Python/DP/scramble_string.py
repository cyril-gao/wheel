'''
We can scramble a string s to get a string t using the following algorithm:
1. If the length of the string is 1, stop.
2. If the length of the string is > 1, do the following:
    1) Split the string into two non-empty substrings at a random index, i.e., if the string is s, divide it to x and y where s = x + y.
    2) Randomly decide to swap the two substrings or to keep them in the same order. i.e., after this step, s may become s = x + y or s = y + x.
    3) Apply step 1 recursively on each of the two substrings x and y.

Given two strings s1 and s2 of the same length, return true if s2 is a scrambled string of s1, otherwise, return false.
'''


def is_scramble(s1: str, s2: str) -> bool:
    n = len(s1)
    assert n == len(s2)
    cache = [[[False for _ in range(n+1)] for _ in range(n)] for _ in range(n)]
    for i in range(n):
        for j in range(n):
            if s1[i] == s2[j]:
                cache[i][j][1] = True
    for span in range(2, n+1):
        for i in range(n-span+1):
            for j in range(n-span+1):
                if s1[i:i+span] == s2[j:j+span]:
                    cache[i][j][span] = True
                else:
                    for k in range(1, span):
                        l = span - k
                        if (
                            (cache[i][j][k] and cache[i+k][j+k][l]) or
                            (cache[i][j+l][k] and cache[i+k][j][l])
                        ):
                            cache[i][j][span] = True
                            break
    return cache[0][0][n]
