package com.example;

import java.util.*;

public class SubstringWithConcatenation {
    private static class Internal {
        public int indexInTxt;
        public int indexInWords;

        Internal(int it, int iw) {
            this.indexInTxt = it;
            this.indexInWords = iw;
        }
    }

    private Map<String, Integer> convert(String[] words, int indexInWords) {
        Map<String, Integer> map = new HashMap<>();
        for (int i = 0; i < words.length; ++i) {
            if (i != indexInWords) {
                Integer count = map.get(words[i]);
                if (count == null) {
                    count = Integer.valueOf(1);
                } else {
                    count = Integer.valueOf(count.intValue() + 1);
                }
                map.put(words[i], count);
            }
        }
        return map;
    }

    private boolean matches(String txt, int indexInTxt, String[] words, int indexInWords) {
        int n = txt.length();
        int m = words[0].length(), nextIndexInTxt = indexInTxt + m;
        assert txt.substring(indexInTxt, indexInTxt + m).compareTo(words[indexInWords]) == 0;
        boolean retval = true;
        Map<String, Integer> map = convert(words, indexInWords);
        while (map.size() > 0 && nextIndexInTxt < n) {
            indexInTxt = nextIndexInTxt;
            nextIndexInTxt += m;
            nextIndexInTxt = Math.min(nextIndexInTxt, n);
            String k = txt.substring(indexInTxt, nextIndexInTxt);
            Integer count = map.get(k);
            if (count != null) {
                int v = count.intValue() - 1;
                if (v <= 0) {
                    map.remove(k);
                } else {
                    map.put(k, Integer.valueOf(v));
                }
            } else {
                retval = false;
                break;
            }
        }
        if (map.size() > 0) {
            retval = false;
        }
        return retval;
    }

    private Internal find(String txt, int fromIndex, String[] words) {
        int indexInTxt = txt.length();
        int indexInWords = -1;
        for (int i = 0; i < words.length; ++i) {
            int j = txt.indexOf(words[i], fromIndex);
            if (j >= fromIndex) {
                if (j < indexInTxt) {
                    indexInTxt = j;
                    indexInWords = i;
                }
            }
        }
        return new Internal(indexInTxt, indexInWords);
    }

    public List<Integer> findSubstring(String s, String[] words) {
        List<Integer> retval = new LinkedList<>();
        int n = s.length();
        if (words.length > 0) {
            int m = words[0].length();
            int minimumLength = words.length * m;
            if (n >= minimumLength) {
                int fromIndex = 0;
                while ((n - fromIndex) >= minimumLength) {
                    Internal itnl = find(s, fromIndex, words);
                    if (itnl.indexInWords >= 0) {
                        if (matches(s, itnl.indexInTxt, words, itnl.indexInWords)) {
                            retval.add(Integer.valueOf(itnl.indexInTxt));
                        }
                        fromIndex = itnl.indexInTxt + 1;
                    } else {
                        break;
                    }
                }
            }
        }
        return retval;
    }
}
