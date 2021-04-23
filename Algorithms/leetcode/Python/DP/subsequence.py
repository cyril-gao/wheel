from typing import List, TypeVar


T = TypeVar('T')


# longest increasing subsequence 
def lis(input: List[T]) -> List[T]:
    class Item:
        def __init__(self, length=0, next=None):
            self.length = length
            self.next = next

    retval = []
    n = len(input) if input is not None else 0
    if n > 1:
        max_length = 0
        max_start_index = -1
        cache = [Item(1) for _ in range(n)]
        for i in range(n-2, -1, -1):
            t = input[i]
            length = 1
            next = None
            for j in range(i+1, n):
                if t < input[j]:
                    l = 1 + cache[j].length
                    if l > length:
                        length = l
                        next = j
            cache[i] = Item(length, next)
            if length > max_length:
                max_length = length
                max_start_index = i
        i = max_start_index
        while True:
            retval.append(input[i])
            i = cache[i].next
            if i is None:
                break
    else:
        if n == 1:
            retval = input
    return retval