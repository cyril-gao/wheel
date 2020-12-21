import unittest
from permutation import *
import word_search
from ip_addresses import restore_ip4_addresses
from partition import palindrome_partition
from word_breaking import word_break, word_breaking_is_possible
from sudoku import fill_empty_cells
from combination import k_combination
from additive_number import is_additive_number


class BacktrackingTester(unittest.TestCase):
    def test_permutation(self):
        self.assertEqual(len(dedup_permute([1, 1, 2])), 3)

        inputs = [
            (['1', '2', '3'], 6),
            (['1', '2', '3', '4'], 24),
            (['1', '2', '3', '4', '5'], 120),
            (['1', '2', '3', '4', '5', '6'], 720),
            (['1', '2', '3', '4', '5', '6', '7'], 5040),
            (['1', '2', '3', '4', '5', '6', '7', '8'], 40320)
        ]
        for pair in inputs:
            r = permute(pair[0])
            self.assertEqual(len(r), pair[1])
            for i in range(1, 1+len(r)):
                v = ''.join(r[i-1])
                self.assertEqual(
                    ''.join(r[i-1]), generate_permutation(len(pair[0]), i))

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

    def test_palindrome_partition(self):
        self.assertEqual(
            palindrome_partition("aab"),
            [["a", "a", "b"], ["aa", "b"]]
        )
        self.assertEqual(
            palindrome_partition("aaba"),
            [["a", "a", "b", "a"], ["a", "aba"], ["aa", "b", "a"]]
        )

    def test_word_break(self):
        word_set = set(["abcde", "cdef", "fg", "bcde", "a"])
        self.assertEqual(
            set(word_break("abcdefg", word_set)),
            set(["a bcde fg", "abcde fg"])
        )
        word_set = set(["cc", "ac"])
        self.assertEqual(
            set(word_break("ccaccc", word_set)),
            set(["cc ac cc"])
        )
        word_set = set(["cat", "cats", "and", "sand", "dog"])
        self.assertEqual(
            set(word_break("catsanddog", word_set)),
            set(["cats and dog", "cat sand dog"])
        )
        self.assertTrue(word_breaking_is_possible("catsanddog", word_set))
        word_set = set(["apple", "pen", "applepen", "pine", "pineapple"])
        self.assertEqual(
            set(word_break("pineapplepenapple", word_set)),
            set(["pineapple pen apple", "pine applepen apple", "pine apple pen apple"])
        )
        self.assertTrue(word_breaking_is_possible(
            "pineapplepenapple", word_set))
        word_set = set(["cats", "dog", "sand", "and", "cat"])
        self.assertEqual(word_break("catsandog", word_set), [])
        self.assertFalse(word_breaking_is_possible("catsandog", word_set))

        word_set = set(["a", "aa", "aaa", "aaaa", "aaaaa", "aaaaaa",
                        "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa"])
        input = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        self.assertTrue(word_breaking_is_possible(input, word_set))
        input = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaab"
        self.assertEqual(word_break(input, word_set), [])
        self.assertFalse(word_breaking_is_possible(input, word_set))

        word_set = set(["aa", "aaa", "aaaa", "aaaaa", "aaaaaa",
                        "aaaaaaa", "aaaaaaaa", "aaaaaaaaa", "aaaaaaaaaa", "ba"])
        input = "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaabaabaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa"
        self.assertFalse(word_breaking_is_possible(input, word_set))

    def test_fill_empty_cells(self):
        board = [
            ["5", "3", ".", ".", "7", ".", ".", ".", "."],
            ["6", ".", ".", "1", "9", "5", ".", ".", "."],
            [".", "9", "8", ".", ".", ".", ".", "6", "."],
            ["8", ".", ".", ".", "6", ".", ".", ".", "3"],
            ["4", ".", ".", "8", ".", "3", ".", ".", "1"],
            ["7", ".", ".", ".", "2", ".", ".", ".", "6"],
            [".", "6", ".", ".", ".", ".", "2", "8", "."],
            [".", ".", ".", "4", "1", "9", ".", ".", "5"],
            [".", ".", ".", ".", "8", ".", ".", "7", "9"]
        ]
        result = [
            ["5", "3", "4", "6", "7", "8", "9", "1", "2"],
            ["6", "7", "2", "1", "9", "5", "3", "4", "8"],
            ["1", "9", "8", "3", "4", "2", "5", "6", "7"],
            ["8", "5", "9", "7", "6", "1", "4", "2", "3"],
            ["4", "2", "6", "8", "5", "3", "7", "9", "1"],
            ["7", "1", "3", "9", "2", "4", "8", "5", "6"],
            ["9", "6", "1", "5", "3", "7", "2", "8", "4"],
            ["2", "8", "7", "4", "1", "9", "6", "3", "5"],
            ["3", "4", "5", "2", "8", "6", "1", "7", "9"]
        ]
        fill_empty_cells(board)
        self.assertEqual(board, result)

    def test_k_combination(self):
        result = k_combination(3, 7)
        self.assertEqual(len(result), 1)
        self.assertEqual(result[0], [1, 2, 4])

        expectation = [[1, 2, 6], [1, 3, 5], [2, 3, 4]]
        result = k_combination(3, 9)
        self.assertEqual(result, expectation)

        result = k_combination(4, 1)
        self.assertFalse(result)

        result = k_combination(4, 9)
        self.assertFalse(result)

    def test_is_additive_number(self):
        self.assertTrue(is_additive_number("123"))
        self.assertTrue(is_additive_number("112358"))
        self.assertTrue(is_additive_number("199100199"))
        self.assertTrue(is_additive_number("199101991"))
        self.assertFalse(is_additive_number("1991019910"))
        self.assertTrue(is_additive_number("000"))
        self.assertTrue(is_additive_number("0000"))
        self.assertTrue(is_additive_number("0111111222"))
        self.assertFalse(is_additive_number("01111112220"))
