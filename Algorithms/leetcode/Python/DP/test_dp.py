import unittest
from unique_paths import unique_paths, unique_paths_2, unique_paths_with_obstacles
from minimum_path_sum import minimum_path_sum
from climbing_stairs import climbing_stairs
from decode_ways import number_of_decodings
from edit_distance import minimum_distance, minimum_distance_2
from triangle import minimum_path_in_triangle
from subsequence import lis


class DPTester(unittest.TestCase):
    def test_unique_paths(self):
        r = unique_paths(3, 7)
        self.assertEqual(r, 28)
        r = unique_paths(3, 2)
        self.assertEqual(r, 3)
        r = unique_paths(7, 3)
        self.assertEqual(r, 28)
        r = unique_paths(3, 3)
        self.assertEqual(r, 6)

        r = unique_paths_2(2, 2)
        self.assertEqual(r, 2)
        r = unique_paths_2(3, 3)
        self.assertEqual(r, 6)
        r = unique_paths_2(3, 2)
        self.assertEqual(r, 3)
        r = unique_paths_2(2, 3)
        self.assertEqual(r, 3)
        r = unique_paths_2(7, 3)
        self.assertEqual(r, 28)
        r = unique_paths_2(3, 7)
        self.assertEqual(r, 28)

    def test_minimum_path_sum(self):
        input = [
            [1, 3, 1],
            [1, 5, 1],
            [4, 2, 1]
        ]
        r = minimum_path_sum(input)
        self.assertEqual(r, 7)
        input = [[1, 2, 3], [4, 5, 6]]
        r = minimum_path_sum(input)
        self.assertEqual(r, 12)

    def test_unique_paths_with_obstacles(self):
        input = [[0, 0, 0], [0, 1, 0], [0, 0, 0]]
        r = unique_paths_with_obstacles(input)
        self.assertEqual(r, 2)
        input = [[0, 1], [0, 0]]
        r = unique_paths_with_obstacles(input)
        self.assertEqual(r, 1)
        input = [[0, 0], [1, 1], [0, 0]]
        r = unique_paths_with_obstacles(input)
        self.assertEqual(r, 0)

    def test_climbing_stairs(self):
        result = [1, 2, 3, 5, 8, 13, 21, 34, 55]
        for i in range(len(result)):
            self.assertEqual(climbing_stairs(i+1), result[i])

    def test_number_of_decodings(self):
        self.assertEqual(number_of_decodings("12"), 2)
        self.assertEqual(number_of_decodings("226"), 3)
        self.assertEqual(number_of_decodings("227"), 2)
        self.assertEqual(number_of_decodings("207"), 1)
        self.assertEqual(number_of_decodings("0"), 0)
        self.assertEqual(number_of_decodings("1"), 1)
        self.assertEqual(number_of_decodings("2101"), 1)
        self.assertEqual(number_of_decodings("123123"), 9)

    def test_minimum_distance(self):
        self.assertEqual(minimum_distance("", ""), 0)
        self.assertEqual(minimum_distance("123456", "12"), 4)
        self.assertEqual(minimum_distance("12", "123456"), 4)
        self.assertEqual(minimum_distance("123456", "123456"), 0)
        self.assertEqual(minimum_distance("123456", "12356"), 1)
        self.assertEqual(minimum_distance("12456", "123456"), 1)
        self.assertEqual(minimum_distance("horse", "ros"), 3)
        self.assertEqual(minimum_distance("intention", "execution"), 5)

        self.assertEqual(minimum_distance_2("", ""), 0)
        self.assertEqual(minimum_distance_2("123456", "12"), 4)
        self.assertEqual(minimum_distance_2("12", "123456"), 4)
        self.assertEqual(minimum_distance_2("123456", "123456"), 0)
        self.assertEqual(minimum_distance_2("123456", "12356"), 1)
        self.assertEqual(minimum_distance_2("12456", "123456"), 1)
        self.assertEqual(minimum_distance_2("horse", "ros"), 3)
        self.assertEqual(minimum_distance_2("intention", "execution"), 5)

    def test_minimum_path_in_triangle(self):
        triangle = [[2], [3, 4],[6, 5, 7], [4, 1, 8, 3], [20, 30, 40, 4, 10]]
        self.assertEqual(minimum_path_in_triangle(triangle), 20)
        self.assertEqual(minimum_path_in_triangle(triangle[0:4]), 11)
        self.assertEqual(minimum_path_in_triangle(triangle[0:3]), 10)
        self.assertEqual(minimum_path_in_triangle(triangle[0:2]), 5)

    def test_lis(self):
        input = [7, 1, 2, 10, 9, 8, 6, 4, 7, 3, 5, 2, 4, 7]
        self.assertEqual(len(lis(input)), 5)