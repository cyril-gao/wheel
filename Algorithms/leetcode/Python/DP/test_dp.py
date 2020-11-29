import unittest
from unique_paths import unique_paths, unique_paths_2


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
