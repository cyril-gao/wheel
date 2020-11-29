import unittest
from unique_paths import unique_paths, unique_paths_2, unique_paths_with_obstacles
from minimum_path_sum import minimum_path_sum
from climbing_stairs import climbing_stairs


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
