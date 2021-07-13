from typing import List, Tuple
from permutation import permute


'''
Given an integer n, return the number of structurally unique BST's
(binary search trees) which has exactly n nodes of unique values from 1 to n.
'''

def number_of_unique_trees(n: int) -> int:
    retval = 0
    if n > 0:
        cache = [0 for _ in range(n + 1)]
        cache[0] = 1
        cache[1] = 1
        index = 2
        while index <= n:
            left = 0
            v = 0
            for _ in range(1, index + 1):
                right = index - 1 - left
                v += cache[left] * cache[right]
                left += 1
            cache[index] = v
            index += 1
        retval = cache[n]
    return retval


'''
Given an integer n, return all the structurally unique BST's (binary search trees),
which has exactly n nodes of unique values from 1 to n. Return the answer in any order.
'''

def _sort(nums: List[int], begin: int, end: int) -> None:
    n = end - begin
    if n > 2:
        buf = []
        v = nums[begin]
        index = begin + 1
        for i in range(begin + 1, end):
            if nums[i] > v:
                buf.append(nums[i])
            else:
                nums[index] = nums[i]
                index += 1
        for i in range(len(buf)):
            nums[index + i] = buf[i]
        _sort(nums, begin + 1, index)
        _sort(nums, index, end)


class TreeNode:
    def __init__(self, val=0, left=None, right=None):
        self.val = val
        self.left = left
        self.right = right


class Constant:
    ROOT = 0
    LEFT_CHILD = 1
    RIGHT_CHILD = 2
    CURRENT = 3


def find(root: TreeNode, target: int) -> Tuple[TreeNode, int]:
    parent = None
    p = root
    position = Constant.ROOT
    while p is not None:
        parent = p
        if p.val < target:
            position = Constant.RIGHT_CHILD
            p = p.right
        elif p.val > target:
            position = Constant.LEFT_CHILD
            p = p.left
        else:
            position = Constant.CURRENT
            break
    return (parent, position)


def create_tree(nums: List[int]) -> TreeNode:
    retval = None
    for n in nums:
        parent, position = find(retval, n)
        if position == Constant.LEFT_CHILD:
            parent.left = TreeNode(n)
        elif position == Constant.RIGHT_CHILD:
            parent.right = TreeNode(n)
        elif position == Constant.ROOT:
            retval = TreeNode(n)
        else:
            assert False # bad input
    return retval


def generate_trees(n: int) -> List[TreeNode]:
    retval = []
    if n > 0:
        unique_items = set()
        result = permute([_ + 1 for _ in range(n)])
        for r in result:
            _sort(r, 0, len(r))
            unique_items.add(tuple(r))
        for s in unique_items:
            retval.append(create_tree(s))
    return retval
