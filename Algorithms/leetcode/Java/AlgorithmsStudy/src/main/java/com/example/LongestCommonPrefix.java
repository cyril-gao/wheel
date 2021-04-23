package com.example;

public class LongestCommonPrefix {
    private boolean equals(String[] strs, int index) {
        char c = strs[0].charAt(index);
        boolean retval = true;
        for (int i = 1; i < strs.length; ++i) {
            if (c != strs[i].charAt(index)) {
                retval = false;
                break;
            }
        }
        return retval;
    }

    public String longestCommonPrefix(String[] strs) {
        StringBuilder sb = new StringBuilder();
        if (strs.length > 1) {
            int shortestLength = strs[0].length();
            for (int i = 1; i < strs.length; ++i) {
                if (shortestLength > strs[i].length()) {
                    shortestLength = strs[i].length();
                }
            }
            for (int i = 0; i < shortestLength; ++i) {
                if (equals(strs, i)) {
                    sb.append(strs[0].charAt(i));
                } else {
                    break;
                }
            }
        }
        return sb.toString();
    }

    public static void main(String[] args) {
        var lcp = new LongestCommonPrefix();
        {
            String[] input = { "", "car" };
            var result = lcp.longestCommonPrefix(input);
            System.out.println(result);
        }
        {
            String[] input = { "flower", "flow", "flight" };
            var result = lcp.longestCommonPrefix(input);
            System.out.println(result);
        }
        {
            String[] input = { "dog", "racecar", "car" };
            var result = lcp.longestCommonPrefix(input);
            System.out.println(result);
        }
    }
}