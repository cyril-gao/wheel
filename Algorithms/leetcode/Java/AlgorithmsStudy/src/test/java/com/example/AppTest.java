package com.example;

import java.util.List;

import java.util.HashSet;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertTrue;
import org.testng.annotations.*;

public class AppTest {
    @Test
    public void testSimplifyPath() {
        var sp = new SimplifyPath();
        {
            var result = sp.simplifyPath("/home/");
            assertEquals(result, "/home");
        }
        {
            var result = sp.simplifyPath("/../");
            assertEquals(result, "/");
        }
        {
            var result = sp.simplifyPath("/home//foo/");
            assertEquals(result, "/home/foo");
        }
        {
            var result = sp.simplifyPath("/a/./b/../../c/");
            assertEquals(result, "/c");
        }
        {
            var result = sp.simplifyPath("/a/../../b/../c//.//");
            assertEquals(result, "/c");
        }
        {
            var result = sp.simplifyPath("/a//b////c/d//././/..");
            assertEquals(result, "/a/b/c");
        }
    }

    @Test
    public void testBacktracking() {
        var bt = new Backtracking();
        // for (int i = 1; i < 10; ++i) {
        // bt.queen(i);
        // System.out.println();
        // var solutions = bt.solveNQueens(i);
        // solutions.stream().forEach(System.out::println);
        // }
        {
            int[] candidates = { 2, 3, 6, 7 };
            int target = 7;
            var result = bt.combinationSum(candidates, target);
            assertEquals(result.size(), 2);
        }
        {
            int[] candidates = { 2, 3, 5 };
            int target = 8;
            var result = bt.combinationSum(candidates, target);
            assertEquals(result.size(), 3);
        }
        {
            int[] candidates = { 10, 1, 2, 7, 6, 1, 5 };
            int target = 8;
            var result = bt.combinationSum2(candidates, target);
            assertEquals(result.size(), 4);
        }
        {
            int[] candidates = { 2, 5, 2, 1, 2 };
            int target = 5;
            var result = bt.combinationSum2(candidates, target);
            assertEquals(result.size(), 2);
        }
        {
            var result = bt.combine(4, 2);
            assertEquals(result.size(), 6);
            // result.stream().forEach(System.out::println);
        }
        {
            var result = bt.combine(8, 4);
            assertEquals(result.size(), 70);
            // result.stream().forEach(System.out::println);
        }
    }

    @Test
    public void testMostWater() {
        var cal = new ContainerWithMostWater();
        int[] input1 = { 1, 8, 6, 2, 5, 4, 8, 3, 7 };
        var result = cal.maxArea(input1);
        assertEquals(result, 49);

        int[] input2 = { 2, 3, 10, 5, 7, 8, 9 };
        result = cal.maxArea(input2);
        assertEquals(result, 36);
    }

    @Test
    public void testRomanNumber() {
        var rn = new RomanNumber();
        // System.out.println(rn.intToRoman(9999));
        assertEquals(rn.intToRoman(9999), "MMMMMMMMMCMXCIX");
    }

    @Test
    public void testLongestCommonPrefix() {
        var lcp = new LongestCommonPrefix();
        {
            String[] input = { "flower", "flow", "flight" };
            var result = lcp.longestCommonPrefix(input);
            assertEquals(result, "fl");
        }
        {
            String[] input = { "dog", "racecar", "car" };
            var result = lcp.longestCommonPrefix(input);
            assertEquals(result, "");
        }
        {
            String[] input = { "", "car" };
            var result = lcp.longestCommonPrefix(input);
            assertEquals(result, "");
        }
    }

    @Test
    public void testLetterCombinations() {
        var lc = new LetterCombinations();
        {
            var result = lc.letterCombinations("");
            assertEquals(result.size(), 0);
        }
        {
            var result = lc.letterCombinations("23");
            var uniqueResult = new HashSet<String>(result);
            assertEquals(uniqueResult.size(), 9);
        }
        {
            var result = lc.letterCombinations("2379");
            var uniqueResult = new HashSet<String>(result);
            assertEquals(uniqueResult.size(), 9 * 16);
        }
    }

    @Test
    public void testParentheses() {
        var p = new Parentheses();
        assertEquals(p.generateParenthesis(1).size(), 1);
        assertEquals(p.generateParenthesis(2).size(), 2);
        assertEquals(p.generateParenthesis(3).size(), 5);
        assertEquals(p.generateParenthesis(4).size(), 14);
    }

    private boolean equals(List<Integer> result, Integer[] expection) {
        boolean retval = result.size() == expection.length;
        if (retval) {
            for (int i = 0; i < expection.length; ++i) {
                if (result.get(i).intValue() != expection[i].intValue()) {
                    retval = false;
                    break;
                }
            }
        }
        return retval;
    }

    @Test
    public void testSubstringWithConcatenation() {
        var swc = new SubstringWithConcatenation();
        {
            String[] words = { "foo", "bar" };
            Integer[] result = { 0, 9 };
            assertTrue(equals(swc.findSubstring("barfoothefoobarman", words), result));
        }
        {
            String[] words = { "word", "good", "best", "word" };
            Integer[] result = {};
            assertTrue(equals(swc.findSubstring("wordgoodgoodgoodbestword", words), result));
        }
        {
            String[] words = { "bar", "foo", "the" };
            Integer[] result = { 6, 9, 12 };
            assertTrue(equals(swc.findSubstring("barfoofoobarthefoobarman", words), result));
        }
        {
            String[] words = { "ca", "ac" };
            Integer[] result = { 1 };
            assertTrue(equals(swc.findSubstring("acaacc", words), result));
        }
        {
            String[] words = { "ca", "ba" };
            Integer[] result = { 2 };
            assertTrue(equals(swc.findSubstring("cccabaacca", words), result));
        }
    }

    @Test
    public void testSingleNumber() {
        var ao = new ArrayOperations();
        {
            int[] nums = { 2, 2, 1 };
            assertEquals(ao.singleNumber(nums), 1);
        }
        {
            int[] nums = { 4, 1, 2, 1, 2 };
            assertEquals(ao.singleNumber(nums), 4);
        }
        {
            int[] nums = { 1 };
            assertEquals(ao.singleNumber(nums), 1);
        }
    }
}
