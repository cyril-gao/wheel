import numpy as np


def extend_shortest_paths(L, M):
    assert L.ndim == 2 and M.ndim == 2
    n = L.shape[0]
    assert n == L.shape[1]
    L2 = np.zeros(L.shape, L.dtype)  # L2 == L'
    for i in range(n):
        for j in range(n):
            v = np.Infinity
            for k in range(n):
                v = min(v, L[i, k] + M[k, j])
            L2[i, j] = v
    return L2


def slow_all_pairs_shortest_paths(W):
    assert W.ndim == 2
    n = W.shape[0]
    assert n == W.shape[1]
    L = np.copy(W)
    for _ in range(2, n):
        L = extend_shortest_paths(L, W)
    return L


def faster_all_pairs_shortest_paths_recursively(W):
    def _faster_all_pairs_shortest_paths_recursively(L, n):
        if n > 1:
            L2 = _faster_all_pairs_shortest_paths_recursively(L, n//2)
            L3 = extend_shortest_paths(L2, L2)
            if (n&2) == 1:
                L3 = extend_shortest_paths(L3, L)
            return L3
        else:
            return L
    assert W.ndim == 2
    n = W.shape[0]
    assert n == W.shape[1]
    return _faster_all_pairs_shortest_paths_recursively(W, n-1)


def faster_all_pairs_shortest_paths(W):
    assert W.ndim == 2
    n = W.shape[0]
    assert n == W.shape[1]
    if n > 1:
        n -= 1
        A = W if (n&1) == 1 else None
        n >>= 1
        L = W
        while n != 0:
            L = extend_shortest_paths(L, L)
            if (n&1) == 1 and n != 1:
                if A is not None:
                    A = extend_shortest_paths(A, L)
                else:
                    A = L
            n >>= 1
        if A is not None:
            L = extend_shortest_paths(L, A)
        return L
    else:
        return W
