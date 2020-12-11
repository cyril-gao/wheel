package com.cybernumen;

import java.util.*;

public class ArrayOperations {
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

    private void rotate(int[][] matrix, int row, int colRight, int rowBottom) {
        int diff = rowBottom - row;
        for (int col = row; col < colRight; ++col) {
            int tmp = matrix[row][col];
            int leftRow = row + (diff - (col - row)), leftCol = row;
            matrix[row][col] = matrix[leftRow][leftCol];
            int bottomRow = rowBottom, bottomCol = leftCol + (diff - (rowBottom - leftRow));
            matrix[leftRow][leftCol] = matrix[bottomRow][bottomCol];
            int rightRow = bottomRow - (diff - (colRight - bottomCol)), rightCol = colRight;
            matrix[bottomRow][bottomCol] = matrix[rightRow][rightCol];
            matrix[rightRow][rightCol] = tmp;
        }
    }

    public void rotate(int[][] matrix) {
        if (matrix != null && matrix.length > 1) {
            int loop = (matrix.length + 1) / 2;
            int row = 0, colRight = row + matrix.length - 1, rowBottom = colRight;
            for (int i = 0; i < loop; ++i) {
                rotate(matrix, row, colRight, rowBottom);
                ++row;
                --colRight;
                --rowBottom;
            }
        }
    }

    /**
     * Suppose an array sorted in ascending order is rotated at some pivot unknown
     * to you beforehand.
     * 
     * (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
     * 
     * You are given a target value to search. If found in the array return its
     * index, otherwise return -1.
     * 
     * You may assume no duplicate exists in the array.
     * 
     * Your algorithm's runtime complexity must be in the order of O(log n).
     */
    private int binarySearch(int[] nums, int begin, int end, int target) {
        int m = end;
        while (begin < end) {
            m = (begin + end) / 2;
            if (nums[m] < target) {
                begin = m + 1;
                m = end;
            } else if (nums[m] > target) {
                end = m;
                m = begin;
            } else {
                break;
            }
        }
        return m;
    }

    private int search(int[] nums, int begin, int end, int target) {
        int m = -1;
        if (nums != null && nums.length > 0) {
            int originalEnd = end;
            if (target != nums[begin]) {
                int pm = begin;
                int firstElement = nums[begin++];
                for (int _begin = begin, _end = end;;) {
                    m = (_begin + _end) / 2;
                    while (m < _end && firstElement <= nums[m]) {
                        pm = m;
                        m = (m + 1 + _end) / 2;
                    }
                    if (m < _end) {
                        _begin = pm;
                        _end = m;
                    } else {
                        end = _end;
                        break;
                    }
                }
                m = binarySearch(nums, begin, end, target);
                if (m == end || nums[m] != target) {
                    if (target < firstElement) {
                        m = binarySearch(nums, end, originalEnd, target);
                    }
                }
                if (m == originalEnd || nums[m] != target) {
                    m = -1;
                }
            } else {
                m = begin;
            }
        }
        return m;
    }

    public int search(int[] nums, int target) {
        return search(nums, 0, nums.length, target);
    }

    public int[] searchRange(int[] nums, int target) {
        int lower = -1, upper = -1;
        if (nums != null && nums.length > 0) {
            int begin = 0, end = nums.length, mid = end;
            while (begin < end) {
                mid = (begin + end) / 2;
                if (nums[mid] < target) {
                    begin = mid + 1;
                    mid = end;
                } else if (nums[mid] > target) {
                    end = mid;
                    mid = begin;
                } else {
                    upper = mid;
                    end = mid;
                    while (begin < end) {
                        mid = (begin + end) / 2;
                        if (nums[mid] != target) {
                            begin = mid + 1;
                            mid = end;
                        } else {
                            end = mid;
                            mid = begin;
                        }
                    }
                    lower = mid;
                    begin = upper + 1;
                    end = nums.length;
                    mid = end;
                    while (begin < end) {
                        mid = (begin + end) / 2;
                        if (nums[mid] != target) {
                            end = mid;
                            mid = begin;
                        } else {
                            begin = mid + 1;
                            mid = end;
                        }
                    }
                    upper = mid - 1;
                    break;
                }
            }
        }
        return new int[] { lower, upper };
    }

    public int firstMissingPositive(int[] nums) {
        int retval = 1;
        if (nums != null && nums.length > 0) {
            for (int i = 0; i < nums.length; ++i) {
                int value = nums[i];
                int index = value - 1;
                if (index != i) {
                    nums[i] = 0;
                    while (index >= 0 && index < nums.length && nums[index] != (index + 1)) {
                        int tmp = nums[index];
                        nums[index] = value;
                        value = tmp;
                        index = value - 1;
                    }
                }
            }
            retval = 1;
            for (int i = 0; i < nums.length; i = retval++) {
                if (nums[i] != retval) {
                    break;
                }
            }
        }
        return retval;
    }

    // https://leetcode.com/problems/set-matrix-zeroes/
    public void setZeroes(int[][] matrix) {

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

    private int toNumber(char a) {
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

    private char toChar(int n) {
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

    public List<Integer> spiralOrder(int[][] matrix) {
        int m = matrix.length, n = 0;
        if (m > 0) {
            n = matrix[0].length;
        }
        int total = m * n;
        List<Integer> retval = new ArrayList<>(total);
        if (total > 0) {
            int topRow = 0, topCol = n - 1;
            int bottomRow = m - 1;
            while (topRow <= topCol && topRow <= bottomRow) {
                for (int col = topRow; col <= topCol; ++col) {
                    retval.add(matrix[topRow][col]);
                }
                for (int row = topRow + 1; row <= bottomRow; ++row) {
                    retval.add(matrix[row][topCol]);
                }
                if (topRow < bottomRow) {
                    for (int col = topCol - 1; col >= topRow; --col) {
                        retval.add(matrix[bottomRow][col]);
                    }
                }
                if (topRow < topCol) {
                    for (int row = bottomRow - 1, col = topRow; row > topRow; --row) {
                        retval.add(matrix[row][col]);
                    }
                }
                ++topRow;
                --topCol;
                --bottomRow;
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

    private static class SudokuValiator {
        private int[] counters;

        public SudokuValiator() {
            counters = new int[10];
        }

        public boolean check(char c) {
            int i = -1;
            switch (c) {
                case '1':
                    i = 1;
                    break;
                case '2':
                    i = 2;
                    break;
                case '3':
                    i = 3;
                    break;
                case '4':
                    i = 4;
                    break;
                case '5':
                    i = 5;
                    break;
                case '6':
                    i = 6;
                    break;
                case '7':
                    i = 7;
                    break;
                case '8':
                    i = 8;
                    break;
                case '9':
                    i = 9;
                    break;
                case '.':
                    return true;
                default:
                    break;
            }
            boolean retval = false;
            if (i >= 1 && i <= 9) {
                retval = (++counters[i] <= 1);
            }
            return retval;
        }
    }

    private boolean gridsValid(char[][] board) {
        for (int row = 0; row < 9; row += 3) {
            for (int col = 0; col < 9; col += 3) {
                SudokuValiator sv = new SudokuValiator();
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        if (!sv.check(board[row + i][col + j])) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    private boolean columnsValid(char[][] board) {
        for (int i = 0; i < 9; ++i) {
            SudokuValiator sv = new SudokuValiator();
            for (int j = 0; j < 9; ++j) {
                if (!sv.check(board[j][i])) {
                    return false;
                }
            }
        }
        return true;
    }

    private boolean rowsValid(char[][] board) {
        for (int i = 0; i < 9; ++i) {
            SudokuValiator sv = new SudokuValiator();
            for (int j = 0; j < 9; ++j) {
                if (!sv.check(board[i][j])) {
                    return false;
                }
            }
        }
        return true;
    }

    public boolean isValidSudoku(char[][] board) {
        boolean itIs = board.length == 9 && board[0].length == 9;
        if (itIs) {
            itIs = (rowsValid(board) && columnsValid(board) && gridsValid(board));
        }
        return itIs;
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

    private boolean searchInRotatedSortedArray(int[] nums, int begin, int end, int target) {
        if (begin < end) {
            int front = nums[begin];
            if (target < front) {
                int back = nums[--end];
                if (back < target) {
                    return false;
                }
                if (back == target) {
                    return true;
                }
                ++begin;
                while (begin < end) {
                    int mid = (begin + end) / 2;
                    if (nums[mid] > front) {
                        begin = mid + 1;
                    } else if (nums[mid] < front) {
                        if (nums[mid] > target) {
                            end = mid;
                        } else if (nums[mid] < target) {
                            begin = mid + 1;
                            int r = binarySearch(nums, begin, end, target);
                            return (r != end) && (nums[r] == target);
                        } else {
                            return true;
                        }
                    } else {
                        if (searchInRotatedSortedArray(nums, begin, mid, target)) {
                            return true;
                        }
                        return searchInRotatedSortedArray(nums, mid + 1, end, target);
                    }
                }
            } else if (target > front) {
                int back = nums[end - 1];
                while (begin < end) {
                    int mid = (begin + end) / 2;
                    if (nums[mid] < front) {
                        end = mid;
                    } else if (nums[mid] > front) {
                        if (nums[mid] > target) {
                            end = mid;
                            int r = binarySearch(nums, begin, end, target);
                            return (r != end) && (nums[r] == target);
                        } else if (nums[mid] < target) {
                            begin = mid + 1;
                        } else {
                            return true;
                        }
                    } else {
                        if (nums[mid] <= back) {
                            if (searchInRotatedSortedArray(nums, begin, mid, target)) {
                                return true;
                            }
                            return searchInRotatedSortedArray(nums, mid + 1, end, target);
                        } else {
                            begin = mid + 1;
                        }
                    }
                }
            } else {
                return true;
            }
        }
        return false;
    }

    public boolean searchInRotatedSortedArray(int[] nums, int target) {
        if (nums != null && nums.length > 0) {
            return searchInRotatedSortedArray(nums, 0, nums.length, target);
        }
        return false;
    }

    public int[][] generateMatrix(int n) {
        int[][] retval = new int[n][n];
        int rowTop = 0, rowBottom = n - 1;
        int colLeft = 0, colRight = rowBottom;
        int v = 1;
        for (int count = 0; count < n; count += 2) {
            for (int i = colLeft; i <= colRight; ++i) {
                retval[rowTop][i] = v++;
            }
            for (int i = rowTop + 1; i <= rowBottom; ++i) {
                retval[i][colRight] = v++;
            }
            for (int i = colRight - 1; i >= colLeft; --i) {
                retval[rowBottom][i] = v++;
            }
            for (int i = rowBottom - 1; i > rowTop; --i) {
                retval[i][colLeft] = v++;
            }
            ++rowTop;
            --rowBottom;
            ++colLeft;
            --colRight;
        }
        return retval;
    }

    private void swap(int[] nums, int i, int j) {
        if (i != j) {
            int v = nums[i];
            nums[i] = nums[j];
            nums[j] = v;
        }
    }

    public void sortColors(int[] nums) {
        if (nums != null && nums.length > 1) {
            int zero = -1;
            int two = nums.length;
            for (int i = 0; i < two;) {
                int v = nums[i];
                assert (v >= 0 && v <= 2);
                if (v == 0) {
                    swap(nums, ++zero, i++);
                } else if (v == 2) {
                    swap(nums, --two, i);
                } else {
                    ++i;
                }
            }
        }
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

    public int findMinInUniqueElements(int[] nums) {
        int start = nums[0];
        int back = nums[nums.length - 1];
        if (start > back) {
            int begin = 1;
            int end = nums.length;
            while (begin < end) {
                int mid = (begin + end) / 2;
                int v = nums[mid];
                if (v > back) {
                    begin = mid + 1;
                } else {
                    end = mid;
                }
            }
            return nums[begin];
        } else {
            return start;
        }
    }

    private int findMinInRotatedSortedArray(int[] nums, int begin, int end) {
        assert (begin < end && end <= nums.length);
        int front = nums[begin];
        int back = nums[end - 1];
        if (front >= back) {
            int retval = back;
            for (++begin; begin < end;) {
                int mid = (begin + end) / 2;
                int middle = nums[mid];
                if (middle > front) {
                    begin = mid + 1;
                } else if (middle < front) {
                    retval = middle;
                    end = mid;
                } else {
                    if (begin < mid) {
                        int r = findMinInRotatedSortedArray(nums, begin, mid);
                        if (retval > r) {
                            retval = r;
                        }
                    }
                    if ((mid + 1) < end) {
                        int r = findMinInRotatedSortedArray(nums, mid + 1, end);
                        if (retval > r) {
                            retval = r;
                        }
                    }
                    break;
                }
            }
            return retval;
        } else {
            return front;
        }
    }

    public int findMin(int[] nums) {
        int retval = 0;
        int n = nums != null ? nums.length : 0;
        if (n > 1) {
            retval = findMinInRotatedSortedArray(nums, 0, n);
        } else {
            if (n == 1) {
                retval = nums[0];
            }
        }
        return retval;
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

    private static int getValue(int[][] matrix, int m, int n, int i) {
        int row = i / n;
        int col = i % n;
        return matrix[row][col];
    }

    public boolean searchMatrix(int[][] matrix, int target) {
        boolean retval = false;
        int m = matrix.length;
        if (m > 0) {
            int n = matrix[0].length;
            if (n > 0) {
                int begin = 0;
                int end = m * n;
                int mid = end;
                while (begin < end) {
                    mid = (begin + end) / 2;
                    int middle = getValue(matrix, m, n, mid);
                    if (middle > target) {
                        end = mid;
                        mid = begin;
                    } else if (middle < target) {
                        begin = mid + 1;
                        mid = end;
                    } else {
                        break;
                    }
                }
                retval = (mid != end && getValue(matrix, m, n, mid) == target);
            }
        }
        return retval;
    }

    public void setZeroesByBruteForce(int[][] matrix) {
        int m = matrix.length;
        if (m > 0) {
            int n = matrix[0].length;
            if (n > 0) {
                List<int[]> records = new LinkedList<int[]>();
                for (int i = 0; i < m; ++i) {
                    for (int j = 0; j < n; ++j) {
                        if (matrix[i][j] == 0) {
                            int[] item = { i, j };
                            records.add(item);
                        }
                    }
                }
                for (int[] r : records) {
                    int row = r[0];
                    int col = r[1];
                    for (int i = 0; i < n; ++i) {
                        matrix[row][i] = 0;
                    }
                    for (int i = 0; i < m; ++i) {
                        matrix[i][col] = 0;
                    }
                }
            }
        }
    }

    public void setZeroes73(int[][] matrix) {
        int m = matrix.length;
        if (m > 0) {
            int n = matrix[0].length;
            if (n > 0) {
                int row = 0;
                int col = 0;
                while (row < m && col < n) {
                    if (matrix[row][col] == 0) {
                        break;
                    }
                    ++col;
                    if (col == n) {
                        col = 0;
                        ++row;
                    }
                }
                if (row < m && col < n) {
                    for (int i = row, j = col;;) {
                        ++j;
                        if (j == n) {
                            j = 0;
                            ++i;
                        }
                        if (i < m && j < n) {
                            if (matrix[i][j] == 0) {
                                matrix[i][col] = 0;
                                matrix[row][j] = 0;
                            }
                        } else {
                            break;
                        }
                    }
                    for (int j = 0; j < n; ++j) {
                        if (j != col) {
                            if (matrix[row][j] == 0) {
                                for (int i = 0; i < m; ++i) {
                                    matrix[i][j] = 0;
                                }
                            }
                        }
                    }
                    for (int i = 0; i < m; ++i) {
                        if (i != row) {
                            if (matrix[i][col] == 0) {
                                for (int j = 0; j < n; ++j) {
                                    matrix[i][j] = 0;
                                }
                            }
                        }
                    }
                    for (int j = 0; j < n; ++j) {
                        matrix[row][j] = 0;
                    }
                    for (int i = 0; i < m; ++i) {
                        matrix[i][col] = 0;
                    }
                }
            }
        }
    }

    public int maxProfit(int[] prices) {
        int retval = 0;
        int n = prices != null ? prices.length : 0;
        if (n > 1) {
            for (int i = 0; i < n - 1;) {
                int j = i + 1;
                int d = prices[j] - prices[i];
                i = j;
                if (d > 0) {
                    retval += d;
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

    private int partition(int[] nums, int start, int end) {
        int ge = end;
        int v = nums[start];
        for (int i = end; i > start;) {
            --i;
            if (nums[i] >= v) {
                --ge;
                swap(nums, ge, i);
            }
        }
        return ge;
    }

    private int findKthLargest(int[] nums, int begin, int end, int k) {
        int separator = partition(nums, begin, end);
        int v = end - separator;
        if (v == k) {
            return nums[separator];
        } else {
            if (v > k) {
                return findKthLargest(nums, separator + 1, end, k);
            } else {
                return findKthLargest(nums, begin, separator, k - v);
            }
        }
    }

    public int findKthLargest(int[] nums, int k) {
        int n = nums != null ? nums.length : 0;
        assert (k <= n);
        return findKthLargest(nums, 0, n, k);
    }
}
