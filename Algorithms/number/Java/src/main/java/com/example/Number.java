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
        assert(x.compareTo(BigInteger.ZERO) >= 0);
        assert(N.compareTo(BigInteger.ZERO) > 0);
        BigInteger retval = BigInteger.ONE;
        if (x.compareTo(BigInteger.ZERO) > 0) {
            BigInteger i = x.mod(N);
            long j = 1;
            while (j > 0 && j <= y) {
                if ((j&y) != 0) {
                    retval = retval.multiply(i).mod(N);
                }
                j <<= 1;
                i = i.multiply(i).mod(N);
            }
        } else {
            retval = BigInteger.ZERO;
        }
        return retval;        
    }

    public static BigInteger modexp(BigInteger x, BigInteger y, BigInteger N) {
        assert(y.compareTo(BigInteger.ZERO) >= 0);
        assert(x.compareTo(BigInteger.ZERO) >= 0);
        assert(N.compareTo(BigInteger.ZERO) > 0);
        BigInteger retval = BigInteger.ONE;
        if (x.compareTo(BigInteger.ZERO) > 0) {
            BigInteger i = x.mod(N);
            BigInteger j = BigInteger.ONE;
            while (j.compareTo(y) <= 0) {
                if (j.and(y).compareTo(BigInteger.ZERO) != 0) {
                    retval = retval.multiply(i).mod(N);
                }
                j = j.shiftLeft(1);
                i = i.multiply(i).mod(N);
            }
        } else {
            retval = BigInteger.ZERO;
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
            BigInteger[] qr = a.divideAndRemainder(b);
            var result = _euclid(b, qr[1]);
            return new BigInteger[] {
                result[0], result[2], result[1].subtract(qr[0].multiply(result[2]))
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
            retval[2] = retval[2].subtract(a);
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
