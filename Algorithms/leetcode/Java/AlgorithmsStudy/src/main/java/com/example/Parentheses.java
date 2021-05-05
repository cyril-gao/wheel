package com.example;

import java.util.*;

public class Parentheses {
    public List<String> generateParenthesis(int n) {
        if (n > 1) {
            List<String> previousResult = generateParenthesis(n - 1);
            Set<String> result = new LinkedHashSet<>();
            for (String s : previousResult) {
                result.add("()" + s);
                result.add("(" + s + ")");
                result.add(s + "()");
            }
            for (int left = 2, right = n - left; right > 1; ++left, --right) {
                List<String> leftResult = generateParenthesis(left);
                List<String> rightResult = generateParenthesis(right);
                for (String s1 : leftResult) {
                    for (String s2 : rightResult) {
                        result.add(s1 + s2);
                    }
                }
            }
            return new LinkedList<String>(result);
        } else {
            List<String> retval = new LinkedList<>();
            if (n == 1) {
                retval.add("()");
            }
            return retval;
        }
    }

    /*
     * Given a string containing just the characters '(' and ')', find the length of
     * the longest valid (well-formed) parentheses substring.
     */
    public int longestValidParentheses(String s) {
        int retval = 0;
        int n = s.length();
        if (n > 1) {
            int[] cache = new int[n];
            Arrays.fill(cache, 0);
            for (int i = 0; i < n; ++i) {
                if (s.charAt(i) == ')' && i > 0) {
                    int j = i - 1;
                    j -= cache[j];
                    if (j >= 0 && s.charAt(j) == '(') {
                        int l = i - j + 1;
                        int k = j - 1;
                        if (k >= 0) {
                            l += cache[k];
                        }
                        cache[i] = l;
                        retval = Math.max(retval, l);
                    }
                }
            }
        }
        return retval;
    }
}
