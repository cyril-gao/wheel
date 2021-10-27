package com.example;

import java.util.*;

public class DynamicProgramming {
    private static boolean equals(String s1, int begin, int end, String s2, int start) {
        boolean retval = true;
        for (int i = begin, j = start; i < end; ++i, ++j) {
            if (s1.charAt(i) != s2.charAt(j)) {
                retval = false;
                break;
            }
        }
        return retval;
    }

    // https://leetcode.com/problems/scramble-string
    public boolean isScramble(String s1, String s2) {
        boolean retval = s1 == s2;
        if (!retval) {
            if (s1 != null && s2 != null) {
                retval = s1.equals(s2);
                if (!retval) {
                    int n = s1.length();
                    if (n == s2.length()) {
                        int n1 = n + 1;
                        boolean cache[][][][] = new boolean[n][n1][n][n1];
                        for (int i = 0, ii = 1; ii < n1; ++i, ++ii) {
                            for (int j = 0, jj = 1; jj < n1; ++j, ++jj) {
                                cache[i][ii][j][jj] = (s1.charAt(i) == s2.charAt(j));
                            }
                        }
                        for (int span = 2; span < n1; ++span) {
                            for (int i = 0, ii = span; ii < n1; ++i, ++ii) {
                                for (int j = 0, jj = span; jj < n1; ++j, ++jj) {
                                    cache[i][ii][j][jj] = false;
                                    if (equals(s1, i, ii, s2, j)) {
                                        cache[i][ii][j][jj] = true;
                                    } else {
                                        for (int k = 1; k < span; ++k) {
                                            if ((cache[i][i + k][j][j + k] && cache[i + k][ii][j + k][jj])
                                                    || (cache[i][i + k][jj - k][jj] && cache[i + k][ii][j][jj - k])) {
                                                cache[i][ii][j][jj] = true;
                                                break;
                                            }
                                        }
                                    }
                                }
                            }
                        }
                        retval = cache[0][n][0][n];
                    }
                }
            }
        }
        return retval;
    }

    /*
     * Given an input string (s) and a pattern (p), implement regular expression
     * matching with support for '.' and '*' where: - '.' Matches any single
     * character.​​​​ - '*' Matches zero or more of the preceding element.
     *
     * The matching should cover the entire input string (not partial).
     */
    private List<String> divide(String pattern) {
        List<String> retval = new ArrayList<String>();
        for (int i = 0, n = pattern.length(); i < n;) {
            int j = i;
            while (j < n && pattern.charAt(j) != '*') {
                ++j;
            }
            if (j < n) {
                assert ((j - 1) >= 0);
                if (j - 1 - i > 0) {
                    retval.add(pattern.substring(i, j - 1));
                }
                i = j + 1;
                retval.add(pattern.substring(j - 1, i));
            } else {
                retval.add(pattern.substring(i));
                i = j;
            }
        }
        return retval;
    }

    private boolean containsAsterisk(String pattern) {
        boolean retval = false;
        for (int i = 0, n = pattern.length(); i < n; ++i) {
            if (pattern.charAt(i) == '*') {
                retval = true;
                break;
            }
        }
        return retval;
    }

    private boolean isMatch(String s, int begin, String p) {
        boolean retval = true;
        for (int i = 0, n = p.length(); i < n; ++i) {
            char c = p.charAt(i);
            if (c != '.' && c != s.charAt(begin + i)) {
                retval = false;
                break;
            }
        }
        return retval;
    }

    private boolean isMatch(String s, int begin, int span, String p) {
        assert (containsAsterisk(p) && p.length() == 2);
        boolean retval = true;
        char c = p.charAt(0);
        if (c != '.') {
            for (int i = 0; i < span; ++i, ++begin) {
                if (s.charAt(begin) != c) {
                    retval = false;
                    break;
                }
            }
        }
        return retval;
    }

    private List<Integer> getCandidates(boolean[][] matchingInfo, int begin) {
        List<Integer> retval = new ArrayList<Integer>();
        for (int i = 0; i < matchingInfo.length; ++i) {
            for (int j = 0; j < matchingInfo[i].length; ++j) {
                if (matchingInfo[i][j] && i == begin) {
                    retval.add(j);
                }
            }
        }
        return retval;
    }

    private boolean isMatch(String txt, int txtIndex, List<String> patterns, int pIndex, boolean[][][] matchingInfo) {
        boolean retval = false;
        if (pIndex < patterns.size()) {
            List<Integer> candidates = getCandidates(matchingInfo[pIndex], txtIndex);
            if (!candidates.isEmpty()) {
                for (int l : candidates) {
                    if (isMatch(txt, txtIndex + l, patterns, pIndex + 1, matchingInfo)) {
                        retval = true;
                        break;
                    }
                }
            }
        } else {
            retval = txtIndex >= txt.length();
        }
        return retval;
    }

    public boolean isMatch(String s, String p) {
        boolean retval = false;
        List<String> patterns = divide(p);
        if (!patterns.isEmpty()) {
            int n = patterns.size();
            int m = s.length();
            boolean[][][] matchingInfo = new boolean[n][m + 1][m + 1];
            for (int i = 0; i < n; ++i) {
                String pattern = patterns.get(i);
                if (containsAsterisk(pattern)) {
                    for (int span = 0; span <= m; ++span) {
                        for (int start = 0, end = span; end <= m; ++start, ++end) {
                            if (isMatch(s, start, span, pattern)) {
                                matchingInfo[i][start][span] = true;
                            }
                        }
                    }
                } else {
                    int k = pattern.length();
                    for (int start = 0, end = start + k; end <= m; ++start, ++end) {
                        if (isMatch(s, start, pattern)) {
                            matchingInfo[i][start][k] = true;
                        }
                    }
                }
            }
            retval = isMatch(s, 0, patterns, 0, matchingInfo);
        } else {
            retval = s.isEmpty();
        }
        return retval;
    }

    public int numDecodings(String s) {
        int retval = 0;
        int n = s.length();
        if (n > 1) {
            int[] record = new int[3];
            if (s.charAt(n - 1) != '0') {
                record[2] = 1;
            }
            char c = s.charAt(n - 2);
            if (c != '0') {
                record[1] = record[2];
                if (c == '1' || (c == '2' && s.charAt(n - 1) <= '6')) {
                    ++record[1];
                }
            }

            int current = 1;
            for (int i = n - 3; i >= 0; --i) {
                --current;
                if (current < 0) {
                    current += 3;
                }
                int previous = (current + 1) % 3;
                c = s.charAt(i);
                if (c != '0') {
                    record[current] = record[previous];
                    if (c == '1' || (c == '2' && s.charAt(i + 1) <= '6')) {
                        record[current] += record[(previous + 1) % 3];
                    }
                } else {
                    record[current] = 0;
                }
            }
            retval = record[current];
        } else {
            if (n == 1 && s.charAt(0) != '0') {
                retval = 1;
            }
        }
        return retval;
    }

    /*
     * You are a professional robber planning to rob houses along a street. Each
     * house has a certain amount of money stashed, the only constraint stopping you
     * from robbing each of them is that adjacent houses have security systems
     * connected and it will automatically contact the police if two adjacent houses
     * were broken into on the same night.
     * 
     * Given an integer array nums representing the amount of money of each house,
     * return the maximum amount of money you can rob tonight without alerting the
     * police.
     */
    int rob(int[] nums, int begin, int end) {
        int retval = 0;
        int diff = end - begin;
        if (diff > 2) {
            int[] cache = new int[]{nums[end - 2], nums[end - 1]};
            if (cache[0] < cache[1]) {
                cache[0] = cache[1];
            }
            retval = Integer.max(cache[0], cache[1]);
            for (int i = end - 3; i >= begin; --i) {
                int v = Integer.max(nums[i] + cache[1], cache[0]);
                retval = Integer.max(v, retval);
                cache[1] = cache[0];
                cache[0] = v;
            }
        } else {
            if (diff == 2) {
                retval = Integer.max(nums[begin], nums[begin + 1]);
            } else if (diff == 1) {
                retval = nums[begin];
            }
        }
        return retval;
    }

    public int rob(int[] nums) {
        return rob(nums, 0, nums.length);
    }

    /*
     * You are a professional robber planning to rob houses along a street. Each
     * house has a certain amount of money stashed. All houses at this place are
     * arranged in a circle. That means the first house is the neighbor of the last
     * one. Meanwhile, adjacent houses have a security system connected, and it will
     * automatically contact the police if two adjacent houses were broken into on
     * the same night.
     * 
     * Given an integer array nums representing the amount of money of each house,
     * return the maximum amount of money you can rob tonight without alerting the
     * police.
     */
    public int robInACircle(int[] nums) {
        int retval = 0;
        if (nums.length > 2) {
            int[] cache = new int[]{nums[nums.length - 2], nums[nums.length - 1]};
            int[] cache2 = new int[]{cache[0], 0};
            boolean[] lastIsUsed = new boolean[]{false, true};
            if (cache[0] < cache[1]) {
                cache[0] = cache[1];
                lastIsUsed[0] = true;
            }
            retval = Integer.max(cache[0], cache[1]);
            for (int i = nums.length - 3; i > 0; --i) {
                int v = nums[i] + cache[1];
                boolean liu = lastIsUsed[1];
                if (v < cache[0]) {
                    v = cache[0];
                    liu = lastIsUsed[0];
                }
                retval = Integer.max(retval, v);
                cache[1] = cache[0];
                cache[0] = v;
                lastIsUsed[1] = lastIsUsed[0];
                lastIsUsed[0] = liu;
                v = Integer.max(nums[i] + cache2[1], cache2[0]);
                assert(v <= retval);
                cache2[1] = cache2[0];
                cache2[0] = v;
            }
            if (!lastIsUsed[1]) {
                retval = Integer.max(nums[0] + cache[1], cache[0]);
            }
            retval = Integer.max(Integer.max(nums[0] + cache2[1], cache2[0]), retval);
        } else {
            if (nums.length == 2) {
                retval = Integer.max(nums[0], nums[1]);
            } else if (nums.length == 1) {
                retval = nums[0];
            }
        }
        return retval;
    }
}
