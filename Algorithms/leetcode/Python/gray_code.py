from typing import List, Set


'''
The gray code is a binary numeral system where two successive values differ in only one bit.

Given a non-negative integer n representing the total number of bits in the code, print the sequence of gray code. A gray code sequence must begin with 0.

Example 1:
Input: 2
Output: [0,1,3,2]
Explanation:
00 - 0
01 - 1
11 - 3
10 - 2

For a given n, a gray code sequence may not be uniquely defined.
For example, [0,2,3,1] is also a valid gray code sequence.

00 - 0
10 - 2
11 - 3
01 - 1

Example 2:
Input: 0
Output: [0]
Explanation: We define the gray code sequence to begin with 0.
             A gray code sequence of n has size = 2n, which for n = 0 the size is 20 = 1.
             Therefore, for n = 0 the gray code sequence is [0].
'''


def gray_code(n: int) -> List[int]:
    def build_number(n: int, buf: List[int]):
        i = 1
        j = n - 1
        retval = 0
        for _ in range(n):
            if buf[j] == 1:
                retval += i
            i <<= 1
            j -= 1
        return retval

    def can_get_neighbour(n: int, buf: List[int], visited: Set[int]):
        for i in range(n):
            v1 = buf[i]
            buf[i] = (buf[i] + 1) % 2
            v2 = build_number(n, buf)
            if v2 not in visited:
                return v2
            else:
                buf[i] = v1
        return None

    retval = [0]
    if n > 0:
        visited = set()
        visited.add(0)
        buf = [0 for _ in range(n)]
        while True:
            v = can_get_neighbour(n, buf, visited)
            if v is not None:
                retval.append(v)
                visited.add(v)
            else:
                break
    return retval


def is_gray_code(nums: List[int]):
    n = len(nums)
    for i in range(n-1):
        v1 = nums[i]
        v2 = nums[i+1]
        if v1 == v2:
            return False
        if v1 < v2:
            v1, v2 = v2, v1
        v1 -= v2
        if v1 & (v1 - 1) != 0:
            return False
    return True
