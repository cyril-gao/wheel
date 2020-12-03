import unittest
from permutation import *
import word_search


class BacktrackingTester(unittest.TestCase):
    def test_permutation(self):
        self.assertEqual(len(permute([1, 2, 3, 4])), 24)
        self.assertEqual(len(dedup_permute([1, 1, 2])), 3)

    def test_subsets(self):
        self.assertEqual(len(subsets([1, 2, 3, 3])), 12)
        self.assertEqual(len(dedup_subsets([1, 3, 2, 3])), 12)
        self.assertEqual(len(dedup_subsets([4, 4, 4, 1, 4])), 10)

    def test_word_search(self):
        board = [
            ["A", "B", "C", "E"], ["S", "F", "C", "S"], ["A", "D", "E", "E"]
        ]
        self.assertTrue(word_search.exist(board, "ABCCED"))
        self.assertTrue(word_search.exist(board, "SEE"))
        self.assertFalse(word_search.exist(board, "ABCB"))
