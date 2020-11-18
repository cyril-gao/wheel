package com.cybernumen;

import java.util.*;

public class LetterCombinations {
    private char[] getMap(char c) {
        char[] empty = {};
        switch (c) {
        case '2':
            return new char[] {'a', 'b', 'c'};
        case '3':
            return new char[] {'d', 'e', 'f'};
        case '4':
            return new char[] {'g', 'h', 'i'};
        case '5':
            return new char[] {'j', 'k', 'l'};
        case '6':
            return new char[] {'m', 'n', 'o'};
        case '7':
            return new char[] {'p', 'q', 'r', 's'};
        case '8':
            return new char[] {'t', 'u', 'v'};
        case '9':
            return new char[] {'w', 'x', 'y', 'z'};
        default:
            return empty;
        }
    }
    private List<String> combinate(String input, int start) {
        List<String> retval = new LinkedList<String>();
        int length = input.length();
        if (start < length) {
            List<String> result = combinate(input, start + 1);
            char[] map = getMap(input.charAt(start));
            for (String s : result) {
                for (char c : map) {
                    StringBuilder sb = new StringBuilder();
                    sb.append(c);
                    sb.append(s);
                    retval.add(sb.toString());
                }
            }
        } else {
            retval.add("");
        }
        return retval;
    }
    public List<String> letterCombinations(String digits) {
        if (digits != null && digits.length() > 0) {
            return combinate(digits, 0);
        }
        return new ArrayList<String>(0);
    }
}