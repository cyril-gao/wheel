package com.cybernumen;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertTrue;
import static org.testng.Assert.assertFalse;
import org.testng.annotations.*;

import java.util.*;

class NumberInput {
    public String input;
    public boolean expection;

    public NumberInput(String input, boolean expection) {
        this.input = input;
        this.expection = expection;
    }
}

public class ArrayOperationsTest {
    Random random = new Random();

    private void print(int[] array) {
        // for (int i = 0; i < array.length; ++i) {
        // System.out.print(array[i] + " ");
        // }
        // System.out.println();
    }

    private boolean isSorted(int[] array) {
        for (int i = 0; i < array.length - 1; ++i) {
            if (array[i] > array[i + 1]) {
                return false;
            }
        }
        return true;
    }

    @Test
    public void testArrayOperations() {
        var ao = new ArrayOperations();
        {
            int[] nums = { 1, 1, 2 };
            var result = ao.removeDuplicates(nums);
            assertEquals(result, 2);
        }
        {
            int[] nums = { 0, 0, 1, 1, 1, 2, 2, 3, 3, 4 };
            var result = ao.removeDuplicates(nums);
            assertEquals(result, 5);
        }
        {
            int[] nums = { 1, 1, 2 };
            var result = ao.removeDuplicates2(nums);
            assertEquals(result, 3);
        }
        {
            int[] nums = { 0, 0, 1, 1, 1, 2, 2, 3, 3, 4 };
            var result = ao.removeDuplicates2(nums);
            assertEquals(result, 9);
        }
        {
            int[] nums = { 1, 1, 1, 2, 2, 3 };
            var result = ao.removeDuplicates2(nums);
            assertEquals(result, 5);
        }
        {
            int[] nums = { 0, 0, 1, 1, 1, 1, 2, 3, 3 };
            var result = ao.removeDuplicates2(nums);
            assertEquals(result, 7);
        }

        {
            int[] nums = { 3, 2, 2, 3 };
            var result = ao.removeElement(nums, 3);
            assertEquals(result, 2);
        }
        {
            int[] nums = { 0, 1, 2, 2, 3, 0, 4, 2 };
            var result = ao.removeElement(nums, 2);
            assertEquals(result, 5);
        }
        {
            int[] nums = { 0, 0, 0, 0, 0, 0, 0 };
            var result = ao.removeElement(nums, 0);
            assertEquals(result, 0);
        }
        {
            int[] nums = { 0, 1, 2, 2, 3, 0, 4, 2 };
            var result = ao.removeElement(nums, 8);
            assertEquals(result, nums.length);
        }
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
        {
            int[] nums = { 5, 6, 7, 9, 10, 11, 12, 13, 17, 89, 0, 1, 2, 3, 4 };
            // ao.search(nums, 89);
            for (int i = 0; i < nums.length; ++i) {
                int r = ao.search(nums, nums[i]);
                assertEquals(r, i);
            }
            assertEquals(ao.search(nums, -1), -1);
            assertEquals(ao.search(nums, -11), -1);
            assertEquals(ao.search(nums, 8), -1);
            assertEquals(ao.search(nums, 14), -1);
            assertEquals(ao.search(nums, 60), -1);
        }
        {
            int[] nums = { 1, 1, 5, 7, 7, 7, 9, 9, 9, 9, 9, 17, 17, 17, 17, 21 };
            var result = ao.searchRange(nums, -1);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 0);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 1);
            assertTrue(result != null && result.length == 2 && result[0] == 0 && result[1] == 1);
            result = ao.searchRange(nums, 3);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 5);
            assertTrue(result != null && result.length == 2 && result[0] == 2 && result[1] == 2);
            result = ao.searchRange(nums, 6);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 7);
            assertTrue(result != null && result.length == 2 && result[0] == 3 && result[1] == 5);
            result = ao.searchRange(nums, 8);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 9);
            assertTrue(result != null && result.length == 2 && result[0] == 6 && result[1] == 10);
            result = ao.searchRange(nums, 15);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 17);
            assertTrue(result != null && result.length == 2 && result[0] == 11 && result[1] == 14);
            result = ao.searchRange(nums, 20);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 21);
            assertTrue(result != null && result.length == 2 && result[0] == 15 && result[1] == 15);
            result = ao.searchRange(nums, 22);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
            result = ao.searchRange(nums, 212);
            assertTrue(result != null && result.length == 2 && result[0] == -1 && result[1] == -1);
        }
        {
            int[] nums = { 1, 2, 0 };
            assertEquals(ao.firstMissingPositive(nums), 3);
        }
        {
            int[] nums = { 3, 4, -1, 1 };
            assertEquals(ao.firstMissingPositive(nums), 2);
        }
        {
            int[] nums = { 7, 8, 9, 11, 12 };
            assertEquals(ao.firstMissingPositive(nums), 1);
        }
        {
            int[] nums = { 0, 1, 2, 3, 4, 5, 6 };
            assertEquals(ao.firstMissingPositive(nums), nums.length);
        }
        {
            int[] nums = { 10, 1, 2, 3, 4, 5, 6 };
            assertEquals(ao.firstMissingPositive(nums), 7);
        }
        {
            int[] nums = { 1 };
            assertEquals(ao.firstMissingPositive(nums), 2);
        }
        {
            int[] nums = { 1, 2, 3 };
            assertEquals(ao.firstMissingPositive(nums), 4);
        }
        {
            int[] height = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
            assertEquals(ao.trap(height), 6);
        }
        {
            int[] height = { 3, 1, 3, 2, 1, 0, 1, 4, 1, 3, 1, 0, 3, 1, 1, 2, 1, 1 };
            assertEquals(ao.trap(height), 19);
        }
        {
            int[] height = { 2, 0, 2 };
            assertEquals(ao.trap(height), 2);
        }
        {
            int n1 = 237, n2 = 2472;
            for (int i = 0; i < 1001; ++i, ++n1) {
                for (int j = 0; j < 1001; ++j) {
                    int n3 = n2 + j;
                    int m = n1 * n3;
                    var result = ao.multiply(String.valueOf(n1), String.valueOf(n3));
                    assertEquals(result, String.valueOf(m));
                }
            }
        }
        {
            var result = ao.longestValidParentheses("()(()");
            assertEquals(result, 2);
        }
        {
            var result = ao.longestValidParentheses("()))()()())(()))((");
            assertEquals(result, 6);
        }
        {
            var result = ao.longestValidParentheses("()(())");
            assertEquals(result, 6);
        }
        {
            String input = "((())())(()))(()()(()(()))(()((((()))))))((()())()))()()(()(((((()()()())))()())(()()))((((((())))((()))()()))))(()))())))()))()())((()()))))(()(((((())))))()((()(()(())((((())(())((()()(()())))())(()(())()()))())(()()()))()(((()())(((()()())))(((()()()))(()()))()))()))))))())()()((()(())(()))()((()()()((())))()(((()())(()))())())))(((()))))())))()(())))()())))())()((()))((()))()))(((())((()()()(()((()((())))((()()))())(()()(()))))())((())))(()))()))))))()(()))())(()())))))(()))((())(()((())(((((()()()(()()())))(()())()((()(()()))(()(())((()((()))))))))(()(())()())()(()(()(()))()()()(()()())))(())(()((((()()))())))(())((()(())())))))())()()))(((())))())((()(()))(()()))((())(())))))(()(()((()((()()))))))(()()()(()()()(()(())()))()))(((()(())()())(()))())))(((()))())(()((()))(()((()()()(())()(()())()(())(()(()((((())()))(((()()(((()())(()()()(())()())())(()(()()((()))))()(()))))(((())))()()))(()))((()))))()()))))((((()(())()()()((()))((()))())())(()((()()())))))))()))(((()))))))(()())))(((()))((()))())))(((()(((())))())(()))))(((()(((((((((((((())(((()))((((())())()))())((((())(((())))())(((()))))()())()(())())(()))))()))()()()))(((((())()()((()))())(()))()()(()()))(())(()()))()))))(((())))))((()()(()()()()((())((((())())))))((((((()((()((())())(()((()))(()())())())(()(())(())(()((())((())))(())())))(()()())((((()))))((()(())(()(()())))))))))((()())()()))((()(((()((()))(((((()()()()()(()(()((()(()))(()(()((()()))))()(()()((((((()((()())()))((())()()(((((()(()))))()()((()())((()())()(())((()))()()(()))";
            var result = ao.longestValidParentheses(input);
            assertEquals(result, 168);
        }
        {
            int[] nums = { 2, 3, 1, 1, 4 };
            var result = ao.jump(nums);
            assertEquals(result, 2);
        }
        {
            int[] nums = { 2, 3, 1, 1, 4 };
            var result = ao.jump(nums);
            assertEquals(result, 2);
            assertTrue(ao.canJump(nums));
        }
        {
            int[] nums = { 7, 0, 9, 6, 9, 6, 1, 7, 9, 0, 1, 2, 9, 0, 3 };
            var result = ao.jump(nums);
            assertEquals(result, 2);
            assertTrue(ao.canJump(nums));
        }
        {
            int[] nums = { 3, 2, 1, 0, 4 };
            assertFalse(ao.canJump(nums));
        }
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
        {
            int[] nums = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
            var result = ao.maxSubArray(nums);
            assertEquals(result, 6);
        }
        {
            int[] nums = { -22, -3, -3, -4, -1, -20, -1, -5, -14 };
            var result = ao.maxSubArray(nums);
            assertEquals(result, -1);
        }
        {
            int[] nums = { -22, -3, -3, -4, -1, 0, -1, -5, -14 };
            var result = ao.maxSubArray(nums);
            assertEquals(result, 0);
        }
        {
            int[] nums = { 2, -3, -3, 4, -1, 10, -1, 5, -25, 24 };
            var result = ao.maxSubArray(nums);
            assertEquals(result, 24);
        }
        {
            NumberInput[] strings = new NumberInput[] { new NumberInput("abc", false), new NumberInput("1 a", false),
                    new NumberInput(" 1e", false), new NumberInput("e3", false), new NumberInput("99e2.5", false),
                    new NumberInput(" --6", false), new NumberInput("-+3", false), new NumberInput("95a54e53", false),
                    new NumberInput(" 95.e -3   ", false), new NumberInput("0", true), new NumberInput(" 0.1", true),
                    new NumberInput("2e10", true), new NumberInput(" -90e3   ", true), new NumberInput(" 6e-1", true),
                    new NumberInput(" 6e-1   ", true), new NumberInput("53.5e93", true),
                    new NumberInput("53.e-3  ", true), new NumberInput("  .01  ", true),
                    new NumberInput(" -234.234e-34  ", true) };

            for (var ni : strings) {
                // System.out.println(ni.input + ", " + ni.expection);
                var result = ao.isNumber(ni.input);
                if (result != ni.expection) {
                    System.out.printf("It was failed for: [%s %s]\n", ni.input, ni.expection);
                }
                assertEquals(result, ni.expection);
            }
        }

        {
            int[] nums = { 1, 2, 3, 1 };
            var result = ao.rob(nums);
            assertEquals(result, 4);
        }
        {
            int[] nums = { 2, 7, 9, 3, 1 };
            var result = ao.rob(nums);
            assertEquals(result, 12);
        }
        {
            int[] nums = { 1, 3, 1 };
            var result = ao.rob(nums);
            assertEquals(result, 3);
        }
    }

    private static boolean equals(int[] result, int[] expection) {
        boolean retval = result.length == expection.length;
        if (retval) {
            for (int i = 0; i < result.length; ++i) {
                if (result[i] != expection[i]) {
                    retval = false;
                    break;
                }
            }
        }
        return retval;
    }

    @Test
    public void testNextPermutation() {
        var np = new NextPermutation();
        {
            int[] nums = { 1, 2, 3 };
            int[] expection = { 1, 3, 2 };
            np.nextPermutation(nums);
            assertTrue(equals(nums, expection));
        }
        {
            int[] nums = { 3, 2, 1 };
            int[] expection = { 1, 2, 3 };
            np.nextPermutation(nums);
            assertTrue(equals(nums, expection));
        }
        {
            int[] nums = { 2, 3, 1 };
            int[] expection = { 3, 1, 2 };
            np.nextPermutation(nums);
            assertTrue(equals(nums, expection));
        }
        {
            int[] nums = { 1, 1, 5 };
            int[] expection = { 1, 5, 1 };
            np.nextPermutation(nums);
            assertTrue(equals(nums, expection));
        }
        {
            int[] nums = { 1 };
            int[] expection = { 1 };
            np.nextPermutation(nums);
            assertTrue(equals(nums, expection));
        }
        {
            int[] nums = { 6, 4, 2, 8, 5, 0, 3 };
            int[] expection = { 6, 4, 2, 8, 5, 3, 0 };
            np.nextPermutation(nums);
            assertTrue(equals(nums, expection));
        }
        {
            int[] nums = { 6, 4, 2, 8, 5, 0 };
            int[] expection = { 6, 4, 5, 0, 2, 8 };
            np.nextPermutation(nums);
            assertTrue(equals(nums, expection));
        }
        {
            int[] nums = { 2, 2, 0, 4, 3, 1 };
            int[] expection = { 2, 2, 1, 0, 3, 4 };
            np.nextPermutation(nums);
            assertTrue(equals(nums, expection));
        }
        {
            int[] nums = { 1, 4, 3, 2, 2 };
            int[] expection = { 2, 1, 2, 3, 4 };
            np.nextPermutation(nums);
            assertTrue(equals(nums, expection));
        }
    }

    @Test
    public void testCountAndSay() {
        var ao = new ArrayOperations();
        assertEquals(ao.countAndSay(1), "1");
        assertEquals(ao.countAndSay(2), "11");
        assertEquals(ao.countAndSay(3), "21");
        assertEquals(ao.countAndSay(4), "1211");
        assertEquals(ao.countAndSay(5), "111221");
        assertEquals(ao.countAndSay(6), "312211");
    }

    @Test
    public void testSearchInRotatedSortedArray() {
        var ao = new ArrayOperations();
        {
            int[] nums = { 2, 5, 6, 0, 0, 1, 2 };
            assertTrue(ao.searchInRotatedSortedArray(nums, 0));
            assertTrue(ao.searchInRotatedSortedArray(nums, 1));
            assertTrue(ao.searchInRotatedSortedArray(nums, 2));
            assertFalse(ao.searchInRotatedSortedArray(nums, 3));
            assertFalse(ao.searchInRotatedSortedArray(nums, 4));
            assertFalse(ao.searchInRotatedSortedArray(nums, 7));
            assertFalse(ao.searchInRotatedSortedArray(nums, -1));
            assertFalse(ao.searchInRotatedSortedArray(nums, -10));
            assertTrue(ao.searchInRotatedSortedArray(nums, 6));
        }
        {
            int[] nums = { 1, 1, 1, 3, 1, 1, 1, 1 };
            assertFalse(ao.searchInRotatedSortedArray(nums, 0));
            assertTrue(ao.searchInRotatedSortedArray(nums, 1));
            assertFalse(ao.searchInRotatedSortedArray(nums, 2));
            assertTrue(ao.searchInRotatedSortedArray(nums, 3));
            assertFalse(ao.searchInRotatedSortedArray(nums, 4));
            assertFalse(ao.searchInRotatedSortedArray(nums, 7));
            assertFalse(ao.searchInRotatedSortedArray(nums, -1));
            assertFalse(ao.searchInRotatedSortedArray(nums, -10));
            assertFalse(ao.searchInRotatedSortedArray(nums, 6));
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
        var ao = new ArrayOperations();
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

    @Test
    public void testSortColors() {
        var ao = new ArrayOperations();
        {
            int[] array = { 2, 0, 0, 0, 0, 1, 0, 0, 1 };
            ao.sortColors(array);
            assertTrue(isSorted(array));
        }
        {
            int[] array = { 0, 0, 0, 0, 0 };
            ao.sortColors(array);
            assertTrue(isSorted(array));
        }
        {
            int[] array = { 1, 1, 1, 1, 1 };
            ao.sortColors(array);
            assertTrue(isSorted(array));
        }
        {
            int[] array = { 2, 2, 2, 2, 2 };
            ao.sortColors(array);
            assertTrue(isSorted(array));
        }
        {
            int[] array = { 2, 0, 2, 1, 1, 0 };
            ao.sortColors(array);
            assertTrue(isSorted(array));
        }
        {
            int[] array = { 2, 0, 1 };
            ao.sortColors(array);
            assertTrue(isSorted(array));
        }
        {
            int[] array = { 0 };
            ao.sortColors(array);
            assertTrue(isSorted(array) && array[0] == 0);
        }
        {
            int[] array = { 1 };
            ao.sortColors(array);
            assertTrue(isSorted(array) && array[0] == 1);
        }
        {
            int[] array = { 2 };
            ao.sortColors(array);
            assertTrue(isSorted(array) && array[0] == 2);
        }
    }

    @Test
    public void testIsPalindrome() {
        var ao = new ArrayOperations();
        assertTrue(ao.isPalindrome("A man, a plan, a canal: Panama"));
        assertFalse(ao.isPalindrome("race a car"));
    }

    @Test
    public void testfindMinInUniqueElements() {
        var ao = new ArrayOperations();
        {
            int[] nums = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12 };
            for (int i = 0; i < nums.length; ++i) {
                assertEquals(ao.findMinInUniqueElements(nums), 0);
                int v = nums[0];
                for (int j = 1; j < nums.length; ++j) {
                    nums[j - 1] = nums[j];
                }
                nums[nums.length - 1] = v;
            }
            assertEquals(ao.findMinInUniqueElements(nums), 0);
            assertEquals(ao.findMin(nums), 0);
        }
        {
            int[] nums = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 1, 1, 1, 2 };
            for (int i = 0; i < nums.length; ++i) {
                assertEquals(ao.findMin(nums), 0);
                int v = nums[0];
                for (int j = 1; j < nums.length; ++j) {
                    nums[j - 1] = nums[j];
                }
                nums[nums.length - 1] = v;
            }
            assertEquals(ao.findMin(nums), 0);
        }
        {
            int[] nums = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 0, 0, 2, 2 };
            for (int i = 0; i < nums.length; ++i) {
                assertEquals(ao.findMin(nums), 0);
                int v = nums[0];
                for (int j = 1; j < nums.length; ++j) {
                    nums[j - 1] = nums[j];
                }
                nums[nums.length - 1] = v;
            }
            assertEquals(ao.findMin(nums), 0);
        }
        {
            int[] nums = { 2, 2, 2, 2, 2, 2, 2, 2, 2, 0, 2 };
            for (int i = 0; i < nums.length; ++i) {
                assertEquals(ao.findMin(nums), 0);
                int v = nums[0];
                for (int j = 1; j < nums.length; ++j) {
                    nums[j - 1] = nums[j];
                }
                nums[nums.length - 1] = v;
            }
            assertEquals(ao.findMin(nums), 0);
        }
    }

    private void rotateCase(ArrayOperations ao, int n, int k) {
        k %= n;
        int[] nums = new int[n];
        for (int i = 0; i < n; ++i) {
            nums[i] = i;
        }
        ao.rotate(nums, k);
        int[] result = new int[n];
        for (int i = 0; i < n; ++i) {
            result[k++] = i;
            if (k == n) {
                k = 0;
            }
        }
        assertEquals(nums, result);
    }

    @Test
    public void testRotate() {
        var ao = new ArrayOperations();
        int[] limits = { 17, 128, 71, 97 };
        for (int limit : limits) {
            for (int i = 0; i < limit; ++i) {
                rotateCase(ao, limit, i);
            }
        }
    }

    @Test
    public void testSearchMatrix() {
        var ao = new ArrayOperations();
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
        var ao = new ArrayOperations();
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

    @Test
    public void testFindKthLargest() {
        var ao = new ArrayOperations();
        int[] template = { 3, 2, 3, 1, 2, 4, 5, 5, 6, 7, 2, 0, 8 };
        int[] results = { 8, 7, 6, 5, 5, 4, 3, 3, 2, 2, 2, 1, 0 };
        for (int k = 1, n = template.length; k <= n; ++k) {
            int[] nums = new int[n];
            System.arraycopy(template, 0, nums, 0, n);
            var r = ao.findKthLargest(nums, k);
            assertEquals(r, results[k - 1]);
        }
    }

    private int[] productExceptSelf(int[] nums) {
        int[] retval = new int[nums.length];
        for (int i = 0; i < nums.length; ++i) {
            int total = 1;
            for (int j = 0; j < nums.length; ++j) {
                if (i != j) {
                    total *= nums[j];
                }
            }
            retval[i] = total;
        }
        return retval;
    }

    @Test
    public void testProductExceptSelf() {
        var ao = new ArrayOperations();
        {
            int[] nums = { 11, 3, -4, 2, 8, -9, 7, 4, -3, 5 };
            var r1 = ao.productExceptSelf(nums);
            var r2 = productExceptSelf(nums);
            assertTrue(equals(r1, r2));
        }
        {
            int[] nums = { 11, 3, -4, 2, 8, 0, -9, 7, 4, -3, 5 };
            var r1 = ao.productExceptSelf(nums);
            var r2 = productExceptSelf(nums);
            assertTrue(equals(r1, r2));
        }
        {
            int[] nums = { 3, -3 };
            var r1 = ao.productExceptSelf(nums);
            var r2 = productExceptSelf(nums);
            assertTrue(equals(r1, r2));
        }
        {
            int[] nums = { 4, 0 };
            var r1 = ao.productExceptSelf(nums);
            var r2 = productExceptSelf(nums);
            assertTrue(equals(r1, r2));
        }
        {
            int[] nums = { 0, 0 };
            var r1 = ao.productExceptSelf(nums);
            var r2 = productExceptSelf(nums);
            assertTrue(equals(r1, r2));
        }
        {
            int[] nums = { 3, 0, -2 };
            var r1 = ao.productExceptSelf(nums);
            var r2 = productExceptSelf(nums);
            assertTrue(equals(r1, r2));
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
        var ao = new ArrayOperations();
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
}
