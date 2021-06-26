package com.example;

import java.math.BigInteger;
import java.security.SecureRandom;

public class Prime {
    // if (a ** (n-1)) % n == 1, return true, or return false
    // carmichael numbers may make the function failed
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

    public static boolean isProbablePrime(BigInteger num, int certainty) {
        var retval = false;
        if (num.and(BigInteger.ONE).compareTo(BigInteger.ONE) == 0) {
            var random = new SecureRandom();
            var bits = num.bitLength();

            retval = true;
            byte[] bytes = new byte[bits];
            for (int i = 0; i < certainty;) {
                random.nextBytes(bytes);
                BigInteger a = new BigInteger(bytes);
                if (a.compareTo(BigInteger.ZERO) > 0) {
                    a = a.mod(num);
                }
                if (a.compareTo(BigInteger.ZERO) > 0) {
                    if (!canPassFermatLittleTheorem(a, num)) {
                        retval = false;
                        break;
                    }
                    ++i;
                }
            }
        } else {
            retval = (num.compareTo(BigInteger.TWO) == 0);
        }
        return retval;
    }

    public static boolean isProbablePrime(BigInteger num) {
        return isProbablePrime(num, 40);
    }
}
