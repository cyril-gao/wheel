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
    private void print(int[] array) {
        // for (int i = 0; i < array.length; ++i) {
        // System.out.print(array[i] + " ");
        // }
        // System.out.println();
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
}