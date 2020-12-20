package com.example;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertTrue;
import static org.testng.Assert.assertFalse;
import org.testng.annotations.*;

class NumberInput {
    public String input;
    public boolean expection;

    public NumberInput(String input, boolean expection) {
        this.input = input;
        this.expection = expection;
    }
}

public class ArrayOperationsTest {
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
    public void testIsPalindrome() {
        var ao = new ArrayOperations();
        assertTrue(ao.isPalindrome("A man, a plan, a canal: Panama"));
        assertFalse(ao.isPalindrome("race a car"));
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

    @Test
    public void testMissingNumber() {
        var ao = new ArrayOperations();
        {
            int[] nums = { 0, 1 };
            assertEquals(ao.missingNumber(nums), 2);
        }
        {
            int[] nums = { 9, 6, 4, 2, 3, 5, 7, 0, 1 };
            assertEquals(ao.missingNumber(nums), 8);
        }
        {
            int[] nums = { 0 };
            assertEquals(ao.missingNumber(nums), 1);
        }
        {
            int[] nums = { 8, 6, 4, 2, 3, 5, 7, 0, 1 };
            assertEquals(ao.missingNumber(nums), 9);
        }
    }

    @Test
    public void testMoveZeroes() {
        var ao = new ArrayOperations();
        {
            int[] data = { 0, 0, 1, 0, 3, 12 };
            int[] result = { 1, 3, 12, 0, 0, 0 };
            ao.moveZeroes(data);
            assertTrue(equals(data, result));
        }
        {
            int[] data = { 1, 2, 0, 3, 4, 0, 5, 0, 0, 6, 0, 8, 12 };
            int[] result = { 1, 2, 3, 4, 5, 6, 8, 12, 0, 0, 0, 0, 0 };
            ao.moveZeroes(data);
            assertTrue(equals(data, result));
        }
        {
            int[] data = { 1, 2, 3, 4, 5, 6, 8, 12 };
            int[] result = { 1, 2, 3, 4, 5, 6, 8, 12 };
            ao.moveZeroes(data);
            assertTrue(equals(data, result));
        }
        {
            int[] data = { 0 };
            int[] result = { 0 };
            ao.moveZeroes(data);
            assertTrue(equals(data, result));
        }
        {
            int[] data = { 1 };
            int[] result = { 1 };
            ao.moveZeroes(data);
            assertTrue(equals(data, result));
        }
    }

    @Test
    public void testConvertToTitle() {
        var ao = new ArrayOperations();
        assertEquals(ao.convertToTitle(26), "Z");
        assertEquals(ao.convertToTitle(52), "AZ");
        assertEquals(ao.convertToTitle(53), "BA");
        assertEquals(ao.convertToTitle(702), "ZZ");
    }
}
