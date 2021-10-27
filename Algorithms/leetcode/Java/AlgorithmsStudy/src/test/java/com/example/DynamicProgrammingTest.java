package com.example;

import static org.testng.Assert.assertTrue;
import static org.testng.Assert.assertFalse;
import static org.testng.Assert.assertEquals;

import org.testng.annotations.*;

public class DynamicProgrammingTest {
    @Test
    public void testIsScramble() {
        var dp = new DynamicProgramming();
        assertTrue(dp.isScramble("abcdbdacbdac", "bdacabcdbdac"));
        assertTrue(dp.isScramble("great", "rgeat"));
        assertTrue(dp.isScramble("abcd", "cabd"));
        assertTrue(dp.isScramble("abcd", "dbac"));
        assertTrue(dp.isScramble("abcde", "edcba"));
        assertTrue(dp.isScramble("abcdbdacbdac", "bdacabcdbdac"));
        assertTrue(dp.isScramble("ccabcbabcbabbbbcbbabcdbdacbdacabcdbdacbdac",
                "bbbbabccccbbbabcbabdacabcdbdacbdacabcdbdac"));
        assertTrue(dp.isScramble("ccbabcbabbbbcbbabcdbdacac", "bbbbcccbbbabcbabdacabcdac"));
        assertFalse(dp.isScramble("abcde", "caebd"));
        assertFalse(dp.isScramble("dcoiorfhkqdwp", "rdpihwfkcooqd"));
    }

    private int robInACircle(int[] nums, DynamicProgramming dp) {
        int retval = 0;
        if (nums.length > 2) {
            retval = dp.rob(nums, 0, nums.length - 1);
            retval = Integer.max(retval, dp.rob(nums, 1, nums.length));
        } else {
            retval = dp.rob(nums);
        }
        return retval;
    }

    @Test
    public void testRob() {
        var dp = new DynamicProgramming();
        {
            int[] nums = {1, 2, 3, 1};
            assertEquals(dp.rob(nums), 4);
            assertEquals(dp.robInACircle(nums), 4);
            assertEquals(dp.robInACircle(nums),robInACircle(nums, dp));
        }
        {
            int[] nums = { 2, 7, 9, 3, 1 };
            assertEquals(dp.rob(nums), 12);
            assertEquals(dp.robInACircle(nums), 11);
            assertEquals(dp.robInACircle(nums),robInACircle(nums, dp));
        }
        {
            int[] nums = { 2, 1, 1, 2 };
            assertEquals(dp.rob(nums), 4);
            assertEquals(dp.robInACircle(nums), 3);
            assertEquals(dp.robInACircle(nums),robInACircle(nums, dp));
        }
        {
            int[] nums = { 10, 8, 9, 20, 18, 6 };
            assertEquals(dp.rob(nums), 37);
            assertEquals(dp.robInACircle(nums), 37);
            assertEquals(dp.robInACircle(nums),robInACircle(nums, dp));
        }
        {
            int[] nums = { 4, 1, 2, 7, 5, 3, 1 };
            assertEquals(dp.rob(nums), 14);
            assertEquals(dp.robInACircle(nums), 14);
            assertEquals(dp.robInACircle(nums),robInACircle(nums, dp));
        }
        {
            int[] nums = { 2, 3, 2 };
            assertEquals(dp.rob(nums), 4);
            assertEquals(dp.robInACircle(nums), 3);
            assertEquals(dp.robInACircle(nums),robInACircle(nums, dp));
        }
        {
            int[] nums = { 1, 2, 3 };
            assertEquals(dp.rob(nums), 4);
            assertEquals(dp.robInACircle(nums), 3);
            assertEquals(dp.robInACircle(nums),robInACircle(nums, dp));
        }
    }
}
