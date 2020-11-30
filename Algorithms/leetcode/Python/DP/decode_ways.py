def _number_of_decodings(s: str, start: int, next: int) -> int:
    assert start <= next and (next+1) <= len(s) and (start+1) >= next
    first = ord(s[start])
    if first == 48:  # 0
        return 0
    elif first == 49:  # 1
        if next > start and s[next] != '0':
            return 2
        else:
            return 1
    elif first == 50:  # 2
        if next > start:
            second = ord(s[next])
            if second > 48 and second < 55:
                return 2
        return 1
    else:
        if next > start and s[next] == '0':
            return 0
        return 1


def _is_valid(s: str, start: int, next: int) -> bool:
    assert start <= next and (next+1) <= len(s) and (start+1) >= next
    if start == next:
        if s[start] != '0':
            return True
        else:
            return False
    if s[start] == '1':
        return True
    if s[start] == '2':
        if s[next] >= '0' and s[next] <= '6':
            return True
    return False


def number_of_decodings(s: str) -> int:
    n = len(s) if s is not None else 0
    if n > 2:
        cache = [0, 0]
        cache[0] = _number_of_decodings(s, n-1, n-1)
        cache[1] = _number_of_decodings(s, n-2, n-1)
        for i in range(3, n+1):
            j = n-i
            v1 = cache[1] if _is_valid(s, j, j) else 0
            v2 = cache[0] if _is_valid(s, j, j+1) else 0
            cache[0] = cache[1]
            cache[1] = v1 + v2
        return cache[1]
    else:
        retval = 0
        if n > 0:
            retval = _number_of_decodings(s, 0, n-1)
        return retval
