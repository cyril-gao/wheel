import numpy as np

extend_shortest_paths(L, M):
    assert L.ndim == 2 and M.ndim == 2
    n = L.shape[0]
    assert n == L.shape[1]
    L2 = np.zero(L.shape, L.dtype) # L2 == L'
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