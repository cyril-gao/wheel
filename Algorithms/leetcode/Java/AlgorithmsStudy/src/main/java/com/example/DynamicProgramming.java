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
     * matching with support for '.' and '*' where:
     *   - '.' Matches any single character.​​​​
     *   - '*' Matches zero or more of the preceding element.
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
                assert((j - 1) >= 0);
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
        assert(containsAsterisk(p) && p.length() == 2);
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

    private List<Integer> getCandidates(boolean[][] matchingInfo, int begin)
    {
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
            boolean[][][] matchingInfo = new boolean[n][m+1][m+1];
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
}
