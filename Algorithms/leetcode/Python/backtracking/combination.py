from typing import List


'''
https://leetcode.com/problems/combination-sum-iii/

Find all valid combinations of k numbers that sum up to n such that the following conditions are true:

Only numbers 1 through 9 are used.
Each number is used at most once.
Return a list of all possible valid combinations. The list must not contain the same combination twice, and the combinations may be returned in any order.
'''


def k_combination(k: int, n: int) -> List[List[int]]:
    def next(
        target: int,
        index_upper_limit: int,
        start: int,
        index: int,
        tmp: List[int],
        result: List[List[int]]
    ):
        if index < index_upper_limit:
            r = index_upper_limit - index
            l = min((target + r - 1) // r + 1, 10)
            for i in range(start, l):
                tmp.append(i)
                next(target-i, index_upper_limit, i+1, index+1, tmp, result)
                tmp.pop()
        else:
            if target == 0:
                result.append(tmp[:])
    retval = []
    next(n, k, 1, 0, [], retval)
    return retval
