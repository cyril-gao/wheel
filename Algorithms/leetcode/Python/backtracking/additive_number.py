from typing import List


'''
Additive number is a string whose digits can form additive sequence.

A valid additive sequence should contain at least three numbers. Except for the first two numbers, each subsequent number in the sequence must be the sum of the preceding two.

Given a string containing only digits '0'-'9', write a function to determine if it's an additive number.

Note: Numbers in the additive sequence cannot have leading zeros, so sequence 1, 2, 03 or 1, 02, 3 is invalid.


Example 1:
Input: "112358"
Output: true
Explanation: The digits can form an additive sequence: 1, 1, 2, 3, 5, 8. 
             1 + 1 = 2, 1 + 2 = 3, 2 + 3 = 5, 3 + 5 = 8

Example 2:
Input: "199100199"
Output: true
Explanation: The additive sequence is: 1, 99, 100, 199. 
             1 + 99 = 100, 99 + 100 = 199
'''


def is_additive_number(num: str) -> bool:
    class BreakException(Exception):
        def __init__(self, *args, **kwargs):
            super().__init__(*args, **kwargs)

    def search_the_third_number(num: str, length: int, start: int, n1: int, n2: int) -> bool:
        if start < length:
            n3 = n1 + n2
            s3 = str(n3)
            l3 = len(s3)
            next_index = start + l3
            if next_index < length:
                return search_the_third_number(num, length, next_index, n2, n3)
            elif next_index > length:
                return False
            else:
                if s3 != num[start:]:
                    return False
        return True

    retval = False
    n = len(num)
    if n >= 3:
        try:
            if num[0] != '0':
                for first in range(1, (n//2)+1):
                    n1 = int(num[:first])
                    first_1 = first + 1
                    if num[first] != '0':
                        for second in range(first_1, (n+first_1)//2+1):
                            retval = search_the_third_number(
                                num, n, second, n1, int(num[first:second])
                            )
                            if retval:
                                raise BreakException()
                    else:
                        retval = search_the_third_number(
                            num, n, first_1, int(num[:first]), 0
                        )
                        if retval:
                            break
            else:
                if num[1] != '0':
                    for second in range(2, (n//2)+1):
                        retval = search_the_third_number(
                            num, n, second, 0, int(num[1:second])
                        )
                        if retval:
                            break
                else:
                    retval = search_the_third_number(num, n, 2, 0, 0)
        except BreakException:
            pass
    return retval
