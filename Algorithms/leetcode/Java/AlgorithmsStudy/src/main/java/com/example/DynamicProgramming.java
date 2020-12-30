package com.example;

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
}
