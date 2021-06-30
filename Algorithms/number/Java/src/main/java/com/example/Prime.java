package com.example;

import java.math.BigInteger;
import java.security.SecureRandom;

public class Prime {
    static final int DEFAULT_CERTAINTY = 40;

    // if (a ** (n-1)) % n == 1, return true, or return false
    // carmichael numbers may make the function failed
    private static boolean canPassFermatLittleTheorem(long a, long n)
    {
        boolean retval = false;
        assert(a > 1 && (a+1) < n);
        assert((n&1) == 1); // n must be an odd
        long loop = (n-1) >> 1;

        long finalMod = (loop&1) == 1 ? a : 1, i = a;
        for (loop >>= 1; loop != 0; loop >>= 1) {
            i = (i*i) % n;
            if ((loop&1) == 1) {
                finalMod = (finalMod*i) % n;
            }
        }
        if (((finalMod*finalMod) % n) == 1) {
            retval = (finalMod-1) == 0 || (finalMod+1) == n;
        }
        return retval;
    }

    private static boolean canPassFermatLittleTheorem(BigInteger a, BigInteger n)
    {
        boolean retval = false;
        assert(a.compareTo(BigInteger.ONE) > 0 && a.add(BigInteger.ONE).compareTo(n) < 0);
        assert(n.and(BigInteger.ONE).compareTo(BigInteger.ONE) == 0); // n must be an odd
        BigInteger loop = n.subtract(BigInteger.ONE).shiftRight(1);

        BigInteger finalMod = loop.and(BigInteger.ONE).compareTo(BigInteger.ONE) == 0 ? a : BigInteger.ONE;
        BigInteger i = a;
        for (loop = loop.shiftRight(1); loop.compareTo(BigInteger.ZERO) != 0; loop = loop.shiftRight(1)) {
            i = i.multiply(i).mod(n);
            if (loop.and(BigInteger.ONE).compareTo(BigInteger.ONE) == 0 ) {
                finalMod = finalMod.multiply(i).mod(n);
            }
        }
        if (finalMod.multiply(finalMod).mod(n).compareTo(BigInteger.ONE) == 0) {
            retval = (
                (finalMod.subtract(BigInteger.ONE).compareTo(BigInteger.ZERO) == 0) ||
                (finalMod.add(BigInteger.ONE).compareTo(n) == 0)
            );
        }
        return retval;
    }

    private static boolean _isProbablePrime(long num, int certainty) {
        var retval = false;
        if (num > 3 && (num & 1) == 1) {
            var random = new SecureRandom();

            long range = num - 3;
            retval = true;
            for (long i = 0, ie = Math.min(range, certainty); i < ie; ++i) {
                long a = random.nextLong();
                if (a < 0) {
                    a = -a;
                }
                a %= range;
                a += 2;
                if (!canPassFermatLittleTheorem(a, num)) {
                    retval = false;
                    break;
                }
            }
        } else {
            retval = (num == 2 || num == 3);
        }
        return retval;
    }

    private static boolean _isProbablePrime(BigInteger num, int certainty) {
        var retval = false;
        if (num.and(BigInteger.ONE).compareTo(BigInteger.ONE) == 0) {
            var random = new SecureRandom();
            var bits = num.bitLength();

            retval = true;
            byte[] bytes = new byte[bits];
            for (int i = 0; i < certainty;) {
                random.nextBytes(bytes);
                BigInteger a = new BigInteger(bytes);
                if (a.compareTo(BigInteger.ONE) > 0) {
                    a = a.mod(num);
                    if (a.compareTo(BigInteger.ONE) > 0 && a.add(BigInteger.ONE).compareTo(num) < 0) {
                        if (!canPassFermatLittleTheorem(a, num)) {
                            retval = false;
                            break;
                        }
                        ++i;
                    }
                }
            }
        } else {
            retval = (num.compareTo(BigInteger.TWO) == 0);
        }
        return retval;
    }

    public static boolean isProbablePrime(BigInteger num, int certainty) {
        if (num.compareTo(BigInteger.ONE) > 0) {
            if (num.compareTo(BigInteger.valueOf(Long.MAX_VALUE)) <= 0) {
                return _isProbablePrime(num.longValue(), certainty);
            } else {
                return _isProbablePrime(num, certainty);
            }
        }
        return false;
    }

    public static boolean isProbablePrime(BigInteger num) {
        return isProbablePrime(num, DEFAULT_CERTAINTY);
    }

    public static BigInteger generatePrime(int numBits, int certainty) {
        var random = new SecureRandom();
        while (true) {
            BigInteger num = new BigInteger(numBits, random);
            if (isProbablePrime(num, certainty)) {
                return num;
            }
        }
    }

    public static BigInteger generatePrime(int numBits) {
        return generatePrime(numBits, DEFAULT_CERTAINTY);
    }
}
