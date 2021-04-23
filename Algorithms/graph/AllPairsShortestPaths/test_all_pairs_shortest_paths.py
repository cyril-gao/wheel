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
        self.expectation = np.array([
            [0.,  3.,  9.,  5., 11.],
            [11., 0.,  6.,  2.,  8.],
            [5.,  8.,  0., 10.,  2.],
            [9.,  1.,  4.,  0.,  6.],
            [3.,  6.,  7.,  8.,  0.]
        ])

    def test_slow_all_pairs_shortest_paths(self):
        L = slow_all_pairs_shortest_paths(np.array(self.W))
        self.assertTrue(np.array_equal(L, self.expectation))

    def test_faster_all_pairs_shortest_paths_recursively(self):
        L = faster_all_pairs_shortest_paths_recursively(np.array(self.W))
        self.assertTrue(np.array_equal(L, self.expectation))

    def test_faster_all_pairs_shortest_paths(self):
        L = faster_all_pairs_shortest_paths(np.array(self.W))
        self.assertTrue(np.array_equal(L, self.expectation))