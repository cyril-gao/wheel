import unittest
from permutation import *
import word_search
from ip_addresses import restore_ip4_addresses


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

    def test_restore_ip4_addresses(self):
        self.assertEqual(restore_ip4_addresses("25525511135"),
                         ["255.255.11.135", "255.255.111.35"])
        self.assertEqual(restore_ip4_addresses("0000"),
                         ["0.0.0.0"])
        self.assertEqual(restore_ip4_addresses("1111"),
                         ["1.1.1.1"])
        self.assertEqual(restore_ip4_addresses("010010"),
                         ["0.10.0.10", "0.100.1.0"])
        self.assertEqual(restore_ip4_addresses("101023"),
                         ["1.0.10.23", "1.0.102.3", "10.1.0.23", "10.10.2.3", "101.0.2.3"])
