package com.cybernumen;

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
}
