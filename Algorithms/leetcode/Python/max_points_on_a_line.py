from typing import List
from fractions import Fraction


'''
Given n points on a 2D plane, find the maximum number of points that lie on the same straight line.

Example 1:
Input: [[1,1],[2,2],[3,3]]
Output: 3
'''


def max_points(points: List[List[int]]) -> int:
    class KeyType:
        def __init__(self, v1, v2):
            self._key = (v1, v2)

        def __hash__(self):
            v1 = hash(self._key[0])
            if isinstance(self._key[0], int):
                v1 = 71 * self._key[0]
            v2 = hash(self._key[1])
            if isinstance(self._key[1], int):
                v2 = 65537 * self._key[1]
            return v1 + v2

        def __eq__(self, other):
            if isinstance(other, KeyType):
                return (
                    self._key[0] == other._key[0] and
                    self._key[1] == other._key[1] and
                    type(self._key[0]) == type(other._key[0]) and
                    type(self._key[1]) == type(other._key[1])
                )
            return False

        def __repr__(self):
            return "%s, %s" % (repr(self._key[0]), repr(self._key[1]))

    n = len(points) if points is not None else 0
    retval = n
    if n > 2:
        slopes = dict()
        for i in range(n-1):
            point1 = points[i]
            for j in range(i+1, n):
                point2 = points[j]
                deltax = point2[0] - point1[0]
                if deltax != 0:
                    v1 = Fraction(point2[1] - point1[1], deltax)
                    v2 = Fraction(point2[0] * point1[1] -
                                  point1[0] * point2[1], deltax)
                    key = KeyType(v1, v2)
                else:
                    key = KeyType(0, point1[0])
                point_set = slopes.get(key, set())
                point_set.add(i)
                point_set.add(j)
                slopes[key] = point_set
        retval = 0
        for k, v in slopes.items():
            l = len(v)
            if l > retval:
                retval = l
    return retval
