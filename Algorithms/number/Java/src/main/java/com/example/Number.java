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
    Output: Integers d, x, y such that d = gcd(a, b) and ax + by = d
    */
    private static BigInteger[] _euclid(BigInteger a, BigInteger b) {
        assert(b.compareTo(BigInteger.ZERO) >= 0);
        assert(a.compareTo(b) >= 0); 
        if (b.compareTo(BigInteger.ZERO) == 0) {
            return new BigInteger[]{a, BigInteger.ONE, BigInteger.ZERO};
        } else {
            var result = _euclid(b, a.mod(b));
            var retval = new BigInteger[] {
                result[0], result[2], result[1].subtract(a.divide(b).multiply(result[2]))
            };
        }
    }

    public static BigInteger[] euclid(BigInteger a, BigInteger b) {
        BigInteger[] retval;
        if (a.compareTo(b) >= 0) {
            retval = _euclid(a, b);
        } else {
            retval = _euclid(b, a);
            var tmp = retval[1];
            retval[1] = retval[2];
            retval[2] = tmp;
        }
        while (retval[1].compareTo(BigInteger.ZERO) < 0) {
            retval[1] = retval[1].add(b);
            retval[2] = retval[2].sub(a);
        }
        return retval;
    }

    public static BigInteger modInverse(BigInteger a, BigInteger m)
    throws IllegalArgumentException {
        var result = euclid(a, m);
        if (result[0].compareTo(BigInteger.ONE) == 0) {
            if (result[1].compareTo(m) >= 0) {
                result[1] = result[1].mod(m);
            }
            return result[1];
        } else {
            throw new IllegalArgumentException("No mod inverse for a modulo m");
        }
    }
}
