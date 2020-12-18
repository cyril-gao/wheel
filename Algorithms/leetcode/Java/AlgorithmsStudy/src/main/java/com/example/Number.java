package com.example;

public class Number {
    public int divide(int dividend, int divisor) {
        assert (divisor != 0);
        if (divisor != Integer.MIN_VALUE) {
            if (divisor != 1 && divisor != -1) {
                int flag = 1;
                int inc = 0;
                if ((dividend > 0 && divisor < 0) || (dividend < 0 && divisor > 0)) {
                    flag = -1;
                }
                if (dividend < 0) {
                    if (dividend != Integer.MIN_VALUE) {
                        dividend = -dividend;
                    } else {
                        dividend = Integer.MAX_VALUE;
                        inc = 1;
                    }
                }
                if (divisor < 0) {
                    divisor = -divisor;
                }
                int retval = 0;
                while (dividend >= divisor) {
                    dividend -= divisor;
                    ++retval;
                }
                dividend += inc;
                if (dividend >= divisor) {
                    ++retval;
                }
                return flag == 1 ? retval : -retval;
            } else {
                if (divisor == 1) {
                    return dividend;
                } else {
                    if (dividend != Integer.MIN_VALUE) {
                        return -dividend;
                    } else {
                        return Integer.MAX_VALUE;
                    }
                }
            }
        } else {
            return dividend == divisor ? 1 : 0;
        }
    }

    public int getBits(int x) {
        int retval = 0;
        while (x != 0) {
            ++retval;
            x >>>= 1;
        }
        return retval;
    }

    public int mySqrt(int x) {
        assert (x >= 0);
        int end = Math.min((1 << ((getBits(x) + 1) / 2)), 46341);
        int begin = 0;
        int retval = begin;
        while (begin < end) {
            int mid = (begin + end) / 2;
            int m2 = mid * mid;
            if (m2 > x) {
                end = mid;
            } else if (m2 < x) {
                retval = mid;
                begin = mid + 1;
            } else {
                retval = mid;
                break;
            }
        }
        return retval;
    }

    private int pow10(int d) {
        int retval = 1;
        for (int i = 0; i < d; ++i) {
            retval *= 10;
        }
        return retval;
    }

    // https://leetcode.com/problems/nth-digit/
    public int findNthDigit(int n) {
        assert (n > 0);
        final int limit = 12;
        long[][] ranges = new long[limit][2];
        {
            long begin = 0, end = 9;
            long v = 9, d = 1;
            for (int i = 0; i < limit; ++i) {
                ranges[i][0] = begin;
                ranges[i][1] = end;
                v *= 10;
                ++d;
                long len = v * d;
                begin = end;
                end += len;
            }
        }
        {
            --n; // start from 0
            int i = 0;
            while (i < limit) {
                if (n < ranges[i][1]) {
                    break;
                }
                ++i;
            }
            int d = i + 1;
            n -= ranges[i][0];
            int j = n / d;
            int k = n % d;
            j += pow10(i);
            String s = Integer.valueOf(j).toString();
            return s.charAt(k) - '0';
        }
    }

    public boolean isPerfectSquare(int num) {
        boolean retval = false;
        if (num >= 2) {
            int bits = (getBits(num) + 1) / 2;
            long begin = 1 << (bits - 1);
            long end = 1 << bits;
            long target = num;
            while (begin < end) {
                long mid = (begin + end) / 2;
                long v = mid * mid;
                if (v > target) {
                    end = mid;
                } else if (v < target) {
                    begin = mid + 1;
                } else {
                    retval = true;
                    break;
                }
            }
        } else {
            retval = (num == 0 || num == 1);
        }
        return retval;
    }
}
