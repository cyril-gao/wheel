package com.example;

import java.util.*;

public class ArrayOperations {
    public static void swap(int[] nums, int i, int j) {
        if (i != j) {
            int v = nums[i];
            nums[i] = nums[j];
            nums[j] = v;
        }
    }

    public int removeDuplicates(int[] nums) {
        int ui = -1;
        for (int i = 0; i < nums.length;) {
            int v = nums[i], j;
            for (j = i + 1; j < nums.length && nums[j] == v; ++j) {
            }
            nums[++ui] = v;
            i = j;
        }
        return ui + 1;
    }

    public int removeElement(int[] nums, int val) {
        int retval = 0;
        if (nums != null && nums.length > 0) {
            int i = 0;
            while (i < nums.length && nums[i] != val) {
                ++i;
            }
            retval = i;
            if (retval < nums.length) {
                for (++i; i < nums.length; ++i) {
                    if (nums[i] != val) {
                        nums[retval++] = nums[i];
                    }
                }
            }
        }
        return retval;
    }

    // https://leetcode.com/problems/trapping-rain-water/
    public int trap(int[] height) {
        int retval = 0;
        if (height != null && height.length > 1) {
            int left = 0, right = height.length - 1;
            while (left < right && height[left] == 0) {
                ++left;
            }
            while (left < right && height[right] == 0) {
                --right;
            }
            int leftHighest = height[left], rightHighest = height[right];
            while (left < right) {
                int count = 0, i;
                if (leftHighest <= rightHighest) {
                    for (i = left + 1; i < right && height[i] <= leftHighest; ++i) {
                        count += height[i];
                    }
                    int v = (i - left - 1) * leftHighest - count;
                    retval += v;
                    left = i;
                    leftHighest = height[left];
                } else {
                    for (i = right - 1; i > left && height[i] <= rightHighest; --i) {
                        count += height[i];
                    }
                    int v = (right - i - 1) * rightHighest - count;
                    retval += v;
                    right = i;
                    rightHighest = height[right];
                }
            }
        }
        return retval;
    }

    public static int toNumber(char a) {
        switch (a) {
            case '0':
                return 0;
            case '1':
                return 1;
            case '2':
                return 2;
            case '3':
                return 3;
            case '4':
                return 4;
            case '5':
                return 5;
            case '6':
                return 6;
            case '7':
                return 7;
            case '8':
                return 8;
            case '9':
                return 9;
            default:
                return 0;
        }
    }

    public static char toChar(int n) {
        assert (n >= 0 && n <= 9);
        switch (n) {
            case 0:
                return '0';
            case 1:
                return '1';
            case 2:
                return '2';
            case 3:
                return '3';
            case 4:
                return '4';
            case 5:
                return '5';
            case 6:
                return '6';
            case 7:
                return '7';
            case 8:
                return '8';
            case 9:
                return '9';
            default:
                return '\0';
        }
    }

    private void multiply(int[] num1, int b, int offset, int[] output) {
        Arrays.fill(output, 0, offset, 0);
        int carry = 0;
        for (int i = num1.length - 1; i >= 0; --i) {
            int m = num1[i] * b + carry;
            carry = m / 10;
            m %= 10;
            output[offset++] = m;
        }
        if (carry != 0) {
            output[offset++] = carry;
        }
        output[offset] = -1;
    }

    private void add(int[] num1, int[] num2) {
        assert (num1.length == num2.length);
        int inc = 0, i = 0;
        while (num1[i] >= 0 && num2[i] >= 0) {
            int s = num1[i] + num2[i] + inc;
            inc = 0;
            if (s > 9) {
                inc = 1;
                s -= 10;
            }
            num1[i++] = s;
        }
        int[] num = num1;
        if (num2[i] >= 0) {
            num = num2;
        }
        while (num[i] >= 0) {
            int s = num[i] + inc;
            inc = 0;
            if (s > 9) {
                inc = 1;
                s -= 10;
            }
            num1[i++] = s;
        }
        if (inc != 0) {
            num1[i++] = inc;
        }
        num1[i] = -1;
    }

    private int[] toArray(String num) {
        int n = num.length();
        int[] retval = new int[n];
        for (int i = 0; i < n; ++i) {
            retval[i] = toNumber(num.charAt(i));
        }
        return retval;
    }

    public String multiply(String num1, String num2) {
        String retval = "0";
        if (num1 != null && num1.length() > 0 && !num1.equals("0") && num2 != null && num2.length() > 0
                && !num2.equals("0")) {
            int bufferSize = num1.length() + num2.length() + 3;
            int[] buf1 = new int[bufferSize];
            Arrays.fill(buf1, -1);
            int[] buf2 = new int[bufferSize];
            Arrays.fill(buf2, -1);

            int[] aNum1 = toArray(num1);
            int[] aNum2 = toArray(num2);
            for (int i = aNum2.length - 1, offset = 0; i >= 0; --i, ++offset) {
                multiply(aNum1, aNum2[i], offset, buf2);
                add(buf1, buf2);
            }
            int i = 0;
            while (i < buf1.length && buf1[i] >= 0) {
                ++i;
            }
            --i;
            StringBuilder sb = new StringBuilder();
            while (i >= 0) {
                sb.append(toChar(buf1[i]));
                --i;
            }
            retval = sb.toString();
        }
        return retval;
    }

    public int longestValidParentheses(String s) {
        int retval = 0;
        if (s != null) {
            char[] input = s.toCharArray();
            if (input.length > 1) {
                int[] cache = new int[input.length];
                Arrays.fill(cache, 0);
                for (int i = 1; i < input.length; ++i) {
                    if (input[i] == ')') {
                        int prefixLen = cache[i - 1];
                        if (prefixLen > 0) {
                            int j = i - prefixLen - 1;
                            if (j >= 0 && input[j] == '(') {
                                cache[i] = prefixLen + 2;
                                --j;
                                if (j >= 0 && cache[j] > 0) {
                                    cache[i] += cache[j];
                                }
                            }
                        } else if (input[i - 1] == '(') {
                            cache[i] = 2;
                            int j = i - 2;
                            if (j >= 0 && cache[j] > 0) {
                                cache[i] += cache[j];
                            }
                        }
                        if (cache[i] > retval) {
                            retval = cache[i];
                        }
                    }
                }
            }
        }
        return retval;
    }

    // https://leetcode.com/problems/jump-game-ii/
    public int jump(int[] nums) {
        int retval = 0;
        if (nums != null && nums.length > 0) {
            int rightmost = 0;
            for (int start = 0, end = 1, i = 0; rightmost < (nums.length - 1);) {
                ++retval;
                for (i = start; i < end; ++i) {
                    int v = i + nums[i];
                    if (v > rightmost) {
                        rightmost = v;
                    }
                }
                start = end;
                end = rightmost + 1;
            }
        }
        return retval;
    }

    // https://leetcode.com/problems/jump-game/
    public boolean canJump(int[] nums) {
        boolean retval = true;
        if (nums != null && nums.length > 0) {
            retval = true;
            int rightmost = 0;
            for (int start = 0, end = 1; rightmost < (nums.length - 1);) {
                for (int i = start; i < end; ++i) {
                    int v = i + nums[i];
                    if (v > rightmost) {
                        rightmost = v;
                    }
                }
                if (rightmost < end) {
                    retval = false;
                    break;
                }
                start = end;
                end = rightmost + 1;
            }
        }
        return retval;
    }

    public int maxSubArray(int[] nums) {
        int retval = 0;
        if (nums != null && nums.length > 0) {
            retval = Integer.MIN_VALUE;
            int start = -1;
            int subsum = 0;
            for (int i = 0; i < nums.length; ++i) {
                int v = nums[i];
                if (start >= 0) {
                    subsum += v;
                } else {
                    start = i;
                    subsum = v;
                }
                if (retval < subsum) {
                    retval = subsum;
                }
                if (subsum <= 0) {
                    start = -1;
                    subsum = 0;
                }
            }
        }
        return retval;
    }

    private int findSequentialNumbers(char[] input, int i) {
        while (i < input.length && Character.isDigit(input[i])) {
            ++i;
        }
        return i;
    }

    public boolean isNumber(String toBeExamined) {
        boolean retval = false;
        if (toBeExamined != null && !toBeExamined.isEmpty()) {
            char[] input = toBeExamined.toCharArray();
            int n = input.length, i = 0, j = i;
            while (i < n && input[i] == ' ') {
                ++i;
            }
            if (i < n) {
                char c = input[i];
                if (c == '+' || c == '-') {
                    ++i;
                }
                boolean needContinue = true;
                j = i;
                i = findSequentialNumbers(input, j);
                if (i < n) {
                    int integralLen = i - j, decimalLen = 0;
                    c = input[i];
                    if (c == '.') {
                        j = i + 1;
                        i = findSequentialNumbers(input, j);
                        decimalLen = i - j;
                    }
                    needContinue = (integralLen > 0 || decimalLen > 0);
                    if (needContinue) {
                        if (i < n) {
                            c = input[i];
                            if (c == 'e' || c == 'E') {
                                j = i + 1;
                                if (j < n) {
                                    c = input[j];
                                    if (c == '+' || c == '-') {
                                        ++j;
                                    }
                                    i = findSequentialNumbers(input, j);
                                    needContinue = (i - j) > 0;
                                }
                            }
                        }
                    }
                }
                if (needContinue) {
                    while (i < n && input[i] == ' ') {
                        ++i;
                    }
                    retval = i >= n;
                }
            }
        }
        return retval;
    }

    // https://leetcode.com/problems/count-and-say/
    private String countAndSay(String input) {
        int n = input.length();
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < n;) {
            char c = input.charAt(i);
            int count = 1, j = i + 1;
            while (j < n && input.charAt(j) == c) {
                ++j;
                ++count;
            }
            sb.append(Integer.valueOf(count).toString());
            sb.append(c);
            i = j;
        }
        return sb.toString();
    }

    public String countAndSay(int n) {
        assert (n > 0);
        if (n > 1) {
            return countAndSay(countAndSay(n - 1));
        } else {
            return "1";
        }
    }

    public int singleNumber(int[] nums) {
        assert (nums != null && nums.length % 2 == 1);
        int retval = nums[0];
        for (int i = 1; i < nums.length; ++i) {
            retval ^= nums[i];
        }
        return retval;
    }

    public int removeDuplicates2(int[] nums) {
        int len = nums != null ? nums.length : 0;
        int o = len > 0 ? -1 : 0;
        for (int i = 0; i < len;) {
            int count = 1;
            int j = i + 1;
            while (j < len && nums[i] == nums[j]) {
                ++count;
                ++j;
            }
            if (o >= 0) {
                nums[o++] = nums[i];
                if (count > 1) {
                    nums[o++] = nums[i + 1];
                }
            } else {
                o = j;
                if (count > 2) {
                    o = i + 2;
                }
            }
            i = j;
        }
        return o;
    }

    public boolean isPalindrome(String s) {
        if (s != null && s.length() > 1) {
            char[] input = s.toCharArray();
            int i = 0, j = input.length - 1;
            while (i < j) {
                boolean bi = Character.isLetterOrDigit(input[i]);
                boolean bj = Character.isLetterOrDigit(input[j]);
                if (bi && bj && Character.toLowerCase(input[i]) != Character.toLowerCase(input[j])) {
                    return false;
                }
                if (bi && bj) {
                    ++i;
                    --j;
                } else {
                    if (!bi) {
                        ++i;
                    }
                    if (!bj) {
                        --j;
                    }
                }
            }
        }
        return true;
    }

    public void rotate(int[] nums, int k) {
        int n = nums != null ? nums.length : 0;
        if (n > 1) {
            k %= n;
            if (k > 0) {
                int left = n - k;
                int right = k;
                if (left != right) {
                    int left_begin = 0, left_end = left;
                    int right_begin = left, right_end = n;
                    while (true) {
                        int original_left = left_end - left_begin;
                        int original_right_begin = right_begin;
                        while (left_begin < left_end && right_begin < right_end) {
                            swap(nums, left_begin, right_begin);
                            ++left_begin;
                            ++right_begin;
                        }
                        left = left_end - left_begin;
                        right = right_end - right_begin;
                        if (left != right) {
                            if (left != 0) {
                                assert (right == 0);
                                right_begin = original_right_begin;
                            } else {
                                assert (right != 0);
                                left_begin = original_right_begin;
                                left_end = left_begin + original_left;
                            }
                        } else {
                            assert (left == 0);
                            break;
                        }
                    }
                } else {
                    for (int i = 0, j = left; j < n; ++i, ++j) {
                        swap(nums, i, j);
                    }
                }
            }
        }
    }

    private int maxProfitAtMostOneTransaction(int[] differences, int begin, int end) {
        int retval = 0, sum = 0;
        for (int i = begin; i < end; ++i) {
            sum += differences[i];
            if (sum > retval) {
                retval = sum;
            }
            if (sum < 0) {
                sum = 0;
            }
        }
        return retval;
    }

    private int[] getDifferences(int[] prices, int n) {
        assert (n > 1);
        int[] differences = new int[n - 1];
        for (int i = 0; i < differences.length;) {
            int j = i + 1;
            differences[i] = prices[j] - prices[i];
            i = j;
        }
        return differences;
    }

    // https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
    public int maxProfitAtMostOneTransaction(int[] prices) {
        int retval = 0;
        int n = prices != null ? prices.length : 0;
        if (n > 1) {
            int[] differences = getDifferences(prices, n);
            retval = maxProfitAtMostOneTransaction(differences, 0, differences.length);
        }
        return retval;
    }

    private int maxProfitAtMostOneTransactionFromHead(int[] differences, int[] cache) {
        int retval = 0, sum = 0;
        for (int i = 0; i < differences.length; ++i) {
            sum += differences[i];
            if (sum > retval) {
                retval = sum;
            }
            if (sum < 0) {
                sum = 0;
            }
            cache[i] = retval;
        }
        return retval;
    }

    private int maxProfitAtMostOneTransactionFromTail(int[] differences, int[] cache) {
        int retval = 0, sum = 0;
        for (int i = differences.length - 1; i >= 0; --i) {
            sum += differences[i];
            if (sum > retval) {
                retval = sum;
            }
            if (sum < 0) {
                sum = 0;
            }
            cache[i] = retval;
        }
        return retval;
    }

    // https://leetcode.com/problems/best-time-to-buy-and-sell-stock-iii/
    public int maxProfitAtMostTwoTransactions(int[] prices) {
        int retval = 0;
        int n = prices != null ? prices.length : 0;
        if (n > 1) {
            int[] differences = getDifferences(prices, n);
            int[] cache1 = new int[differences.length];
            int[] cache2 = new int[differences.length];
            retval = maxProfitAtMostOneTransactionFromHead(differences, cache1);
            n = maxProfitAtMostOneTransactionFromTail(differences, cache2);
            assert (retval == n);
            for (int i = 0, last = differences.length - 1; i < last;) {
                int j = i + 1;
                n = cache1[i] + cache2[j];
                i = j;
                if (n > retval) {
                    retval = n;
                }
            }
        }
        return retval;
    }

    public int rob(int[] nums) {
        int retval = 0;
        int n = nums != null ? nums.length : 0;
        if (n > 0) {
            int[] cache = new int[n + 1];
            cache[n] = 0;
            cache[n - 1] = nums[n - 1];
            if (n > 1) {
                cache[n - 2] = Math.max(nums[n - 2], nums[n - 1]);
                for (int i = n - 3; i >= 0; --i) {
                    cache[i] = Math.max(cache[i + 1], Math.max(cache[i + 2], cache[i + 3]) + nums[i]);
                }
            }
            retval = cache[0];
        }
        return retval;
    }

    public int[] productExceptSelf(int[] nums) {
        assert (nums != null && nums.length > 0);
        int[] retval = new int[nums.length];
        if (nums.length > 2) {
            for (int i = 0; i < nums.length; ++i) {
                retval[i] = 1;
            }
            for (int i = 1; i < nums.length; ++i) {
                int j = i - 1;
                retval[i] = retval[j] * nums[j];
            }
            int v = nums[nums.length - 1];
            for (int i = nums.length - 2; i >= 0; --i) {
                retval[i] *= v;
                v *= nums[i];
            }
        } else {
            if (nums.length == 2) {
                retval[0] = nums[1];
                retval[1] = nums[0];
            }
        }
        return retval;
    }

    // https://leetcode.com/problems/missing-number/
    public int missingNumber(int[] nums) {
        int n = nums.length;
        assert (n > 0);
        boolean nExists = false;
        for (int i = 0; i < n; ++i) {
            int v = nums[i];
            if (v != i) {
                if (v != n) {
                    while (true) {
                        int j = nums[v];
                        nums[v] = v;
                        if (j == v) {
                            break;
                        }
                        if (j == n) {
                            nExists = true;
                            break;
                        }
                        v = j;
                    }
                } else {
                    nExists = true;
                }
            }
        }
        int retval = n;
        if (nExists) {
            for (int i = 0; i < n; ++i) {
                if (nums[i] != i) {
                    retval = i;
                    break;
                }
            }
        }
        return retval;
    }

    // https://leetcode.com/problems/move-zeroes/
    public void moveZeroes(int[] nums) {
        int n = nums != null ? nums.length : 0;
        if (n > 1) {
            int next = 0;
            for (int i = 0; i < n;) {
                int j = i;
                while (j < n && nums[j] != 0) {
                    nums[next++] = nums[j++];
                }
                i = j; // point to 0 or the end
                int k = j;
                while (k < n && nums[k] == 0) {
                    ++k;
                }
                i = k;
            }
            while (next < n) {
                nums[next++] = 0;
            }
        }
    }

    // https://leetcode.com/problems/excel-sheet-column-title/
    public String convertToTitle(int n) {
        char[] cache = { ' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R',
                'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z' };
        final int base = 26;
        assert (n > 0);
        StringBuffer sb = new StringBuffer();
        while (n != 0) {
            int quotient = n / base;
            int remainder = n % base;
            if (remainder == 0) {
                remainder = base;
                --quotient;
            }
            sb.append(cache[remainder]);
            n = quotient;
        }
        return sb.reverse().toString();
    }

    // https://leetcode.com/problems/candy/
    public int candy(int[] ratings) {
        int n = ratings != null ? ratings.length : 0;
        int retval = 0;
        if (n > 0) {
            for (int i = 0; i < n;) {
                int j = i + 1;
                if (j < n) {
                    int k = j + 1;
                    if (ratings[i] > ratings[j]) {
                        while (k < n && ratings[k - 1] > ratings[k]) {
                            ++k;
                        }
                        j = (k - i);
                        j = (j * (j + 1)) / 2 - 1;
                        retval += j;
                        j = k - 1;
                    } else if (ratings[i] == ratings[j]) {
                        while (k < n && ratings[k - 1] == ratings[k]) {
                            ++k;
                        }
                        retval += (k - j);
                        j = k - 1;
                    } else {
                        while (k < n && ratings[k - 1] < ratings[k]) {
                            ++k;
                        }
                        if (k < n && ratings[k - 1] > ratings[k]) {
                            int top = k - 1;
                            int first = (k - i);
                            ++k;
                            while (k < n && ratings[k - 1] > ratings[k]) {
                                ++k;
                            }
                            int second = k - top;
                            if (first < second) {
                                int v1 = (first - 1) * first / 2;
                                int v2 = (second * (second + 1)) / 2;
                                retval += (v1 + v2);
                            } else {
                                int v1 = (first * (first + 1)) / 2;
                                int v2 = (second - 1) * second / 2;
                                retval += (v1 + v2);
                            }
                            j = k;
                            if (k < n && ratings[k - 1] < ratings[k]) {
                                --retval;
                                --j;
                            }
                        } else {
                            j = (k - i);
                            retval += (j * (j + 1)) / 2;
                            j = k;
                        }
                    }
                } else {
                    ++retval;
                }
                i = j;
            }
        }
        return retval;
    }
}
