package com.example;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertTrue;
import static org.testng.Assert.assertFalse;
import org.testng.annotations.*;

import java.util.*;

public class MatrixOperationsTest {
    Random random = new Random();

    private void print(int[] array) {
        // for (int i = 0; i < array.length; ++i) {
        // System.out.print(array[i] + " ");
        // }
        // System.out.println();
    }

    @Test
    public void testRotate() {
        var ao = new MatrixOperations();
        {
            int[][] matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
            ao.rotate(matrix);
            for (int i = 0; i < matrix.length; ++i) {
                print(matrix[i]);
            }
        }
        {
            int[][] matrix = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } };
            ao.rotate(matrix);
            for (int i = 0; i < matrix.length; ++i) {
                print(matrix[i]);
            }
        }
    }

    private boolean equals(int[][] a, int[][] b) {
        if (a != b) {
            if (a != null && b != null && a.length == b.length && a[0].length == b[0].length) {
                for (int i = 0; i < a.length; ++i) {
                    for (int j = 0; j < a[0].length; ++j) {
                        if (a[i][j] != b[i][j]) {
                            return false;
                        }
                    }
                }
            } else {
                return false;
            }
        }
        return true;
    }

    @Test
    public void testGenerateMatrix() {
        var ao = new MatrixOperations();
        {
            int[][] expection = { { 1 } };
            var r = ao.generateMatrix(1);
            assertTrue(equals(expection, r));
        }
        {
            int[][] expection = { { 1, 2 }, { 4, 3 } };
            var r = ao.generateMatrix(2);
            assertTrue(equals(expection, r));
        }
        {
            int[][] expection = { { 1, 2, 3 }, { 8, 9, 4 }, { 7, 6, 5 } };
            var r = ao.generateMatrix(3);
            assertTrue(equals(expection, r));
        }
        {
            int[][] expection = { { 1, 2, 3, 4 }, { 12, 13, 14, 5 }, { 11, 16, 15, 6 }, { 10, 9, 8, 7 } };
            var r = ao.generateMatrix(4);
            assertTrue(equals(expection, r));
        }
    }

    private int randomInc() {
        int v = -1;
        while (v <= 0) {
            v = random.nextInt() % 5;
        }
        return v;
    }

    @Test
    public void testSearchInOrderedMatrix() {
        var ao = new MatrixOperations();
        {
            int[] nums = { 1, 4, 7, 200, 296, 314, 1000, 2, 80, 100, 400, 500, 600, 1100, 90, 100, 110, 1410, 1510,
                    1610, 11200, 11300, 11400, 11500, 11600, 11700, 11800, 20000 };
            int m = 4, n = 7;
            assert (m * n == nums.length);
            Set<Integer> numSet = new HashSet<>();
            for (var v : nums) {
                numSet.add(v);
            }
            int[][] matrix = new int[m][n];
            for (int i = 0, k = 0; i < m; ++i) {
                for (int j = 0; j < n; ++j) {
                    matrix[i][j] = nums[k++];
                }
            }
            for (int target = nums[0] - 1000; target < nums[nums.length - 1] + 1000; ++target) {
                var r = ao.searchInOrderedMatrix(matrix, target);
                if (numSet.contains(Integer.valueOf(target))) {
                    assertTrue(r);
                } else {
                    assertFalse(r);
                }
            }
        }
        {
            int m = 407, n = 2197;
            try {
                Set<Integer> numSet = new HashSet<>();
                int[][] matrix = new int[m][n];
                int v = Integer.MIN_VALUE + 100;
                for (int j = 0; j < n; ++j) {
                    numSet.add(v);
                    matrix[0][j] = v;
                    v += randomInc();
                    if (v <= matrix[0][j]) {
                        System.out.printf("v: %d, previous: %d%n", v, matrix[0][j]);
                        assert (false);
                    }
                }
                for (int i = 1; i < m; ++i) {
                    for (int j = 0; j < n; ++j) {
                        int v1 = matrix[i - 1][j];
                        int v2 = Integer.MIN_VALUE;
                        if (j > 0) {
                            v2 = matrix[i][j - 1];
                        }
                        v = Math.max(v1, v2) + randomInc();
                        matrix[i][j] = v;
                        numSet.add(v);
                    }
                }
                for (int target = Integer.MIN_VALUE; target < v + 200; ++target) {
                    var r = ao.searchInOrderedMatrix(matrix, target);
                    if (numSet.contains(Integer.valueOf(target))) {
                        assertTrue(r);
                    } else {
                        assertFalse(r);
                    }
                }
            } catch (OutOfMemoryError oom) {
                // ignore
            }
        }
    }

    @Test
    public void testSpiralOrder() {
        var ao = new MatrixOperations();
        {
            int[][] matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 } };
            Integer[] sequence = { 1, 2, 3, 6, 9, 8, 7, 4, 5 };
            assertEquals(ao.spiralOrder(matrix), Arrays.asList(sequence));
        }
        {
            int[][] matrix = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 }, { 13, 14, 15, 16 } };
            Integer[] sequence = { 1, 2, 3, 4, 8, 12, 16, 15, 14, 13, 9, 5, 6, 7, 11, 10 };
            assertEquals(ao.spiralOrder(matrix), Arrays.asList(sequence));
        }
        {
            int[][] matrix = { { 1, 2, 3, 4 }, { 5, 6, 7, 8 }, { 9, 10, 11, 12 } };
            Integer[] sequence = { 1, 2, 3, 4, 8, 12, 11, 10, 9, 5, 6, 7 };
            assertEquals(ao.spiralOrder(matrix), Arrays.asList(sequence));
        }
        {
            int[][] matrix = { { 1, 2, 3 }, { 4, 5, 6 }, { 7, 8, 9 }, { 10, 11, 12 }, { 13, 14, 15 } };
            Integer[] sequence = { 1, 2, 3, 6, 9, 12, 15, 14, 13, 10, 7, 4, 5, 8, 11 };
            assertEquals(ao.spiralOrder(matrix), Arrays.asList(sequence));
        }
    }

    @Test
    public void testSearchMatrix() {
        var ao = new MatrixOperations();
        int[][] matrix = { { 1, 3, 5, 7, 9, 11, 13 }, { 15, 17, 19, 21, 23, 25, 27 }, { 29, 31, 33, 35, 37, 39, 41 } };
        for (int i = 0; i < 43; ++i) {
            boolean r = ao.searchMatrix(matrix, i);
            if ((i & 1) != 0) {
                assertTrue(r);
            } else {
                assertFalse(r);
            }
        }
    }

    private void fillMatrix(int[][] matrix, int m, int n, int v) {
        for (int i = 0; i < m; ++i) {
            for (int j = 0; j < n; ++j) {
                matrix[i][j] = v;
            }
        }
    }

    private Set<Coordinate> generateCoordinates(int count, int m, int n) {
        Set<Coordinate> retval = new TreeSet<Coordinate>();
        for (int i = 0; i < count;) {
            var c = Coordinate.random(m, n);
            if (retval.add(c)) {
                ++i;
            }
        }
        return retval;
    }

    private void print(int[] nums, java.io.PrintStream ps) {
        StringBuffer sb = new StringBuffer();
        sb.append('[');
        for (int i = 0; i < nums.length; ++i) {
            if (i != 0) {
                sb.append(',');
            }
            sb.append(Integer.valueOf(nums[i]).toString());
        }
        sb.append(']');
        ps.println(sb.toString());
    }

    private void print(int[][] matrix, java.io.PrintStream ps) {
        ps.println("[");
        for (int i = 0; i < matrix.length; ++i) {
            ps.print('\t');
            print(matrix[i], ps);
        }
        ps.println("]");
    }

    @Test
    public void testSetZeroe() {
        var ao = new MatrixOperations();
        {
            int[][] matrix2 = new int[1][1];
            matrix2[0][0] = 1;
            ao.setZeroes(matrix2);
            matrix2[0][0] = 0;
            ao.setZeroes(matrix2);
            matrix2 = new int[2][1];
            fillMatrix(matrix2, 2, 1, 1);
            ao.setZeroes(matrix2);
            matrix2[0][0] = 0;
            ao.setZeroes(matrix2);
            matrix2 = new int[2][2];
            fillMatrix(matrix2, 2, 2, 1);
            ao.setZeroes(matrix2);
            matrix2[0][1] = 0;
            ao.setZeroes(matrix2);
        }
        {
            int m = 41, n = 91;
            for (int i = 0; i < 10; ++i, m += 11, n += 3) {
                int[][] matrix1 = new int[m][n];
                int[][] matrix2 = new int[m][n];
                for (int len = 1; len < 100; ++len) {
                    for (int retry = 0; retry < 100; ++retry) {
                        fillMatrix(matrix1, m, n, 1);
                        fillMatrix(matrix2, m, n, 1);
                        var sc = generateCoordinates(len, m, n);
                        for (var c : sc) {
                            matrix1[c.row][c.col] = 0;
                            matrix2[c.row][c.col] = 0;
                        }
                        ao.setZeroesByBruteForce(matrix1);
                        ao.setZeroes(matrix2);
                        if (!equals(matrix1, matrix2)) {
                            System.out.printf("len: %d%n%s%n", len, sc.toString());
                            print(matrix1, System.out);
                            print(matrix2, System.out);
                            assertTrue(false);
                        }
                    }
                }
            }
        }
    }

}
