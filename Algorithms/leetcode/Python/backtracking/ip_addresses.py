from typing import List


def restore_ip4_addresses(s: str) -> List[str]:
    def next(
        input: str,
        n: int,
        start: int,
        leavings: int,
        tmp: List[str],
        result: List[str]
    ):
        if start < n:
            if leavings > 0 and (leavings * 3) >= (n-start) and (n-start) >= leavings:
                if input[start] != '0':
                    for i in range(1, 4):
                        next_index = start + i
                        if next_index <= n:
                            s = input[start:next_index]
                            v = int(s)
                            if v >= 0 and v <= 255:
                                tmp.append(s)
                                next(input, n, next_index,
                                     leavings-1, tmp, result)
                                tmp.pop()
                            else:
                                break
                        else:
                            break
                else:
                    tmp.append('0')
                    next(input, n, start+1, leavings-1, tmp, result)
                    tmp.pop()
        else:
            if leavings == 0:
                result.append('.'.join(tmp))

    retval = []
    n = len(s) if s is not None else 0
    if n >= 4:
        next(s, n, 0, 4, [], retval)
    return retval
