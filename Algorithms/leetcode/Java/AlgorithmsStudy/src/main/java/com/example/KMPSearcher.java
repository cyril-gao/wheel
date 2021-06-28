package com.example;

public class KMPSearcher implements SubstringSearcher {
    private int[] createSuffixArray(String p) {
        char[] pattern = p.toCharArray();
        int[] suffixArray = new int[pattern.length];
        int i = 0, j = -1;
        suffixArray[i] = j;
        while (i < pattern.length - 1) {
            while (j >= 0 && pattern[i] != pattern[j]) {
                j = suffixArray[j];
            }
            suffixArray[++i] = ++j;
        }
        return suffixArray;
    }

    public int search(String s, String p) {
        int retval = 0;
        if (s != p) {
            retval = -1;
            if (s != null && p != null) {
                char[] txt = s.toCharArray();
                char[] pattern = p.toCharArray();
                if (txt.length > 0 && pattern.length > 0 && txt.length >= pattern.length) {
                    int[] suffixArray = createSuffixArray(p);
                    int i = 0, j = 0;
                    while (i < txt.length) {
                        while (j >= 0 && txt[i] != pattern[j]) {
                            j = suffixArray[j];
                        }
                        ++i;
                        ++j;
                        if (j == pattern.length) {
                            retval = i - j;
                            break;
                        }
                    }
                } else {
                    if (txt.length >= pattern.length) {
                        retval = 0;
                    }
                }
            }
        }
        return retval;
    }
}