import unittest
import numpy as np
from all_pairs_shortest_paths import *


class AllPairsShortestPathsTester(unittest.TestCase):
    def setUp(self):
        inf = np.Infinity
        self.W = [
            [0, 3, inf, 5, inf],
            [inf, 0, 6, 2, inf],
            [inf, inf, 0, inf, 2],
            [inf, 1, 4, 0, 6],
            [3, inf, 7, inf, 0]
        ]

    def test_slow_all_pairs_shortest_paths(self):
        L = slow_all_pairs_shortest_paths(np.array(self.W))
        print(L)
