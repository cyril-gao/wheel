package com.example;

import java.math.BigInteger;

public class Number {
    static final long TWO_EXP_62 = 4611686018427387904L;
    /*
    Input: two integers x and N, an integer exponent y
    Output: x ^ y mod N
    */
    public static long modexp(long x, long y, long N) {
        return modexp(BigInteger.valueOf(x), y, BigInteger.valueOf(N)).longValue();
    }

    public static BigInteger modexp(BigInteger x, long y, BigInteger N) {
        assert(y >= 0);
        assert(x.compareTo(BigInteger.ZERO) > 0);
        assert(N.compareTo(BigInteger.ZERO) > 0);
        var v = x.mod(N);
        var retval = (y & 1) != 0 ? v : BigInteger.ONE;
        for (long i = 2; i <= y; i <<= 1) {
            v = v.multiply(v).mod(N);
            if ((i & y) != 0) {
                retval = retval.multiply(v).mod(N);
            }
            if (i == TWO_EXP_62) {
                break;
            }
        }
        return retval;        
    }

    public static BigInteger modexp(BigInteger x, BigInteger y, BigInteger N) {
        assert(y.compareTo(BigInteger.ZERO) >= 0);
        assert(x.compareTo(BigInteger.ZERO) > 0);
        assert(N.compareTo(BigInteger.ZERO) > 0);
        var v = x.mod(N);
        var retval = y.and(BigInteger.ONE).compareTo(BigInteger.ZERO) != 0 ? v : BigInteger.ONE;
        for (BigInteger i = BigInteger.TWO; i.compareTo(y) <= 0; i = i.shiftLeft(1)) {
            v = v.multiply(v).mod(N);
            if (i.and(y).compareTo(BigInteger.ZERO) != 0) {
                retval = retval.multiply(v).mod(N);
            }

        }
        return retval;  
    }

    /*
    Input: two positive integers a and b with a >= 0 and b >= 0
    Output: Integers x, y, d such that d = gcd(a, b) and ax + by = d
    */
    private static BigInteger[] _euclid(BigInteger a, BigInteger b) {
        assert(b.compareTo(BigInteger.ZERO) >= 0);
        assert(a.compareTo(b) >= 0); 
        if (b.compareTo(BigInteger.ZERO) == 0) {
            return new BigInteger[]{BigInteger.ONE, BigInteger.ZERO, a};
        } else {
            var result = _euclid(b, a.mod(b));
            return new BigInteger[]{
                result[1], result[0].subtract(a.divide(b).multiply(result[1])), result[2]
            };
        }
    }

    public static BigInteger[] euclid(BigInteger a, BigInteger b) {
        if (a.compareTo(b) >= 0) {
            return _euclid(a, b);
        } else {
            var result = _euclid(b, a);
            var tmp = result[0];
            result[0] = result[1];
            result[1] = tmp;
            return result;
        }
    }
}
