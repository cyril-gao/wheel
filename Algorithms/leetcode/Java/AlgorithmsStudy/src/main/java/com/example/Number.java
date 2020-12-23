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

    // https://leetcode.com/problems/utf-8-validation/
    public boolean validUtf8(int[] data) {
        int n = data != null ? data.length : 0;
        boolean retval = true;
        for (int i = 0; i < n;) {
            int v = (data[i] & 0xf8);
            if (v <= 0x78) {
                ++i;
            } else if (0xc0 <= v && v <= 0xd8) {
                ++i;
                if (i < n) {
                    v = data[i] & 0xc0;
                    if (v != 0x80) {
                        retval = false;
                        break;
                    }
                    ++i;
                } else {
                    retval = false;
                    break;
                }
            } else if (0xe0 <= v && v <= 0xe8) {
                i += 2;
                if (i < n) {
                    v = data[i] & 0xc0;
                    int v2 = data[i - 1] & 0xc0;
                    if (v != 0x80 || v2 != 0x80) {
                        retval = false;
                        break;
                    }
                    ++i;
                } else {
                    retval = false;
                    break;
                }
            } else if (v == 0xf0) {
                i += 3;
                if (i < n) {
                    v = data[i] & 0xc0;
                    int v2 = data[i - 1] & 0xc0;
                    int v3 = data[i - 2] & 0xc0;
                    if (v != 0x80 || v2 != 0x80 || v3 != 0x80) {
                        retval = false;
                        break;
                    }
                    ++i;
                } else {
                    retval = false;
                    break;
                }
            } else {
                retval = false;
                break;
            }
        }
        return retval;
    }

    // https://leetcode.com/problems/count-numbers-with-unique-digits/
    public int countNumbersWithUniqueDigits(int n) {
        int[] cache = new int[11];
        cache[1] = 10;
        int v = 9 * 9;
        cache[2] = v;
        for (int i = 3, j = 8; i <= 10; ++i, --j) {
            v *= j;
            cache[i] = v;
        }
        int retval = 0;
        if (n > 0) {
            if (n > 10) {
                n = 10;
            }
            for (int i = 1; i <= n; ++i) {
                retval += cache[i];
            }
        } else if (n == 0) {
            retval = 1;
        }
        return retval;
    }

    private int div2(int[] b, int length) {
        int n = 0, next = 0;
        for (int i = 0; i < length; ++i) {
            int dividend = (n * 10 + b[i]);
            int quotient = dividend / 2;
            n = dividend % 2;
            if (quotient != 0 || next != 0) {
                b[next++] = quotient;
            }
        }
        return next;
    }

    // https://leetcode.com/problems/super-pow/
    public int superPow(int a, int[] b) {
        int retval = 1;
        int nb = b != null ? b.length : 0;
        if (nb > 1 || (nb == 1 && b[0] > 0)) {
            final int divisor = 1337;
            long dividend = a;
            long remainder = dividend % divisor;
            long result = 1;
            if ((b[nb - 1] & 1) == 1) {
                result = remainder;
            }
            nb = div2(b, nb);
            while (nb > 1 || (nb == 1 && b[0] != 0)) {
                remainder = (remainder * remainder) % divisor;
                if ((b[nb - 1] & 1) == 1) {
                    result = (result * remainder) % divisor;
                }
                nb = div2(b, nb);
            }
            retval = (int) result;
        }
        return retval;
    }
}
