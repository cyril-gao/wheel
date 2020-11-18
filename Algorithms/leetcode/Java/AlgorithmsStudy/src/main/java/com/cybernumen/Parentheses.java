package com.cybernumen;

import java.util.*;

public class Parentheses {
    public List<String> generateParenthesis(int n) {
        if (n > 1) {
            List<String> previousResult = generateParenthesis(n-1);
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
}
