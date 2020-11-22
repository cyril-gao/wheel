import unittest
import random
from graph import *


class ElementaryGraphAlgorithmsTester(unittest.TestCase):
    def setUp(self):
        self.graph1 = Graph(14)
        self.graph1.add_edge(0, 4).add_edge(0, 5).add_edge(0, 11)
        self.graph1.add_edge(1, 2).add_edge(1, 4).add_edge(1, 8)
        self.graph1.add_edge(2, 5).add_edge(2, 6).add_edge(2, 9)
        self.graph1.add_edge(3, 2).add_edge(3, 6).add_edge(3, 13)
        self.graph1.add_edge(4, 7)
        self.graph1.add_edge(5, 8).add_edge(5, 12)
        self.graph1.add_edge(6, 5)
        self.graph1.add_edge(8, 7)
        self.graph1.add_edge(9, 10).add_edge(9, 11)
        self.graph1.add_edge(10, 13)
        self.graph1.add_edge(12, 9)

        self.graph2 = Graph(8)
        self.graph2.add_edge(0, 1)
        self.graph2.add_edge(1, 2).add_edge(1, 4)
        self.graph2.add_edge(2, 3).add_edge(2, 6)
        self.graph2.add_edge(3, 2).add_edge(3, 7)
        self.graph2.add_edge(4, 0).add_edge(4, 5)
        self.graph2.add_edge(5, 6)
        self.graph2.add_edge(6, 5).add_edge(6, 7)
        self.graph2.add_edge(7, 7)

    def test_bfs(self):
        r = Bfs(self.graph1, 0)()
        self.assertEqual(r.path_to(13), (0, 5, 12, 9, 10, 13))
        self.assertFalse(r.has_path_to(3))

    def test_dfs(self):
        r = Dfs(self.graph1, 0)()
        self.assertEqual(r.path_to(11), (0, 5, 12, 9, 11))
        self.assertEqual(r.path_to(12), (0, 5, 12))
        self.assertEqual(r.path_to(13), (0, 5, 12, 9, 10, 13))
        self.assertFalse(r.has_path_to(1))
        self.assertFalse(r.has_path_to(3))

    def test_topological_sort(self):
        r = topological_sort(self.graph1)
        self.assertEqual(r, (3, 1, 2, 6, 0, 5, 12, 9, 11, 10, 13, 8, 4, 7))

    def test_strongly_connected_components(self):
        scc = get_strongly_connected_components(self.graph2)
        self.assertTrue(frozenset((0, 1, 4)) in scc)
        self.assertTrue(frozenset((2, 3)) in scc)
        self.assertTrue(frozenset((5, 6)) in scc)
        self.assertTrue(frozenset((7,)) in scc)
