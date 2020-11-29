def climbing_stairs(n: int) -> int:
    assert n >= 0
    cache = [0 for _ in range(max(3, n+1))]
    cache[1] = 1
    cache[2] = 2
    for distance in range(3, n+1):
        cache[distance] = cache[distance-1] + cache[distance-2]
    return cache[n]
