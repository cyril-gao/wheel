package com.cybernumen;

public class RomanNumber {
    public String intToRoman(int num) {
        assert(num > 0);
        StringBuilder sb = new StringBuilder();
        int v = num / 1000;
        for (int i = 0; i < v; ++i) {
            sb.append('M');
        }
        num %= 1000;
        if (num >= 900) {
            sb.append("CM");
            num -= 900;
        }
        if (num >= 500) {
            sb.append('D');
            num -= 500;
        }
        if (num >= 400) {
            sb.append("CD");
            num -= 400;
        }
        v = num / 100;
        for (int i = 0; i < v; ++i) {
            sb.append('C');
        }
        num %= 100;
        if (num >= 90) {
            sb.append("XC");
            num -= 90;
        }
        if (num >= 50) {
            sb.append('L');
            num -= 50;
        }
        if (num >= 40) {
            sb.append("XL");
            num -= 40;
        }
        v = num / 10;
        for (int i = 0; i < v; ++i) {
            sb.append('X');
        }
        num %= 10;
        if (num >= 9) {
            sb.append("IX");
            num -= 9;
        }
        if (num >= 5) {
            sb.append('V');
            num -= 5;
        }
        if (num >= 4) {
            sb.append("IV");
            num -= 4;
        }
        for (int i = 0; i < num; ++i) {
            sb.append('I');
        }
        return sb.toString();
    }

    public int romanToInt(String s) {
        int retval = 0;
        char[] input = s.toCharArray();
        for (int i = 0, j = 0; i < input.length;) {
            switch(input[i]) {
            case 'M':
                retval += 1000;
                break;
            case 'D':
                retval += 500;
                break;
            case 'C':
                j = i + 1;
                if (
                    j < input.length &&
                    (input[j] == 'M' || input[j] == 'D')
                ) {
                    if (input[j] == 'M') {
                        retval += 900;
                    } else {
                        retval += 400;
                    }
                    i = j;
                } else {
                    retval += 100;
                }
                break;
            case 'L':
                retval += 50;
                break;
            case 'X':
                j = i + 1;
                if (
                    j < input.length &&
                    (input[j] == 'C' || input[j] == 'L')
                ) {
                    if (input[j] == 'C') {
                        retval += 90;
                    } else {
                        retval += 40;
                    }
                    i = j;
                } else {
                    retval += 10;
                }
                break;
            case 'V':
                retval += 5;
                break;
            case 'I':
                j = i + 1;
                if (
                    j < input.length &&
                    (input[j] == 'X' || input[j] == 'V')
                ) {
                    if (input[j] == 'X') {
                        retval += 9;
                    } else {
                        retval += 4;
                    }
                    i = j;
                } else {
                    retval += 1;
                }
                break;
            default:
                // do nothing
            }
            ++i;
        }
        return retval;
    }

    public static void main(String[] args) {
        RomanNumber rn = new RomanNumber();
        for (int i = 1; i < 2000; ++i) {
            var v = rn.intToRoman(i);
            System.out.println(v);
            assert(rn.romanToInt(v) == i);
        }
    }
}