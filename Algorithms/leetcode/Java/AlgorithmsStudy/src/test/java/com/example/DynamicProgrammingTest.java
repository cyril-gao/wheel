package com.example;

import static org.testng.Assert.assertTrue;
import static org.testng.Assert.assertFalse;
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
}
