package com.example;

import java.math.BigInteger;
import java.security.SecureRandom;

public class Prime {
    static final int DEFAULT_CERTAINTY = 80;

    // n = (2**x) * y, the return value is [2**x, y]
    private static long[] binarySimplify(long n)
    {
        assert(n >= 0);
        long x, y;
        long v = n ^ (n-1);
        if (v != 0) {
            x = (v >> 1) + 1;
            y = n / x;
        } else {
            x = 1 << 63;
            y = 1;
        }
        return new long[]{x, y};
    }

    private static BigInteger[] binarySimplify(BigInteger n)
    {
        assert(n.compareTo(BigInteger.ZERO) >= 0);
        BigInteger x, y;
        BigInteger v = n.xor(n.subtract(BigInteger.ONE));
        x = v.shiftRight(1).add(BigInteger.ONE);
        y = n.divide(x);
        return new BigInteger[]{x, y};
    }

    // if (a ** (n-1)) % n == 1, return true, or return false
    // carmichael numbers may make the function failed
    private static boolean canPassFermatLittleTheorem(long a, long n)
    {
        boolean retval = false;
        assert(a > 1 && a < n);
        assert(n > 2 && (n&1) == 1); // n must be an odd

        long[] vs = binarySimplify(n-1);
        assert(vs[0] > 1);
        long v = Number.modexp(a, vs[1], n);
        if (v != 1) {
            long v2 = v;
            BigInteger bn = BigInteger.valueOf(n);
            for (long i = 1; i < vs[0]; i <<= 1) {
                v2 = v;
                BigInteger bv = BigInteger.valueOf(v);
                v = bv.multiply(bv).mod(bn).longValue();
                if (v == 1) {
                    retval = (v2+1) == n;
                    break;
                }
            }
        } else {
            retval = true; // it may be wrong
        }

        return retval;
    }

    private static boolean canPassFermatLittleTheorem(BigInteger a, BigInteger n)
    {
        boolean retval = false;
        assert(a.compareTo(BigInteger.ONE) > 0 && a.add(BigInteger.ONE).compareTo(n) < 0);
        assert(n.and(BigInteger.ONE).compareTo(BigInteger.ONE) == 0); // n must be an odd

        BigInteger[] vs = binarySimplify(n.subtract(BigInteger.ONE));
        assert(vs[0].compareTo(BigInteger.ONE) > 0);
        BigInteger v = Number.modexp(a, vs[1], n);
        if (v.compareTo(BigInteger.ONE) > 0) {
            BigInteger v2 = v;
            for (BigInteger i = BigInteger.ONE; i.compareTo(vs[0]) < 0; i = i.shiftLeft(1)) {
                v2 = v;
                v = v.multiply(v).mod(n);
                if (v.compareTo(BigInteger.ONE) == 0) {
                    retval = (v2.add(BigInteger.ONE).compareTo(n) == 0);
                    break;
                }
            }
        } else {
            retval = true; // it may be wrong
        }
        return retval;
    }

    private static long gcd(long a, long b)
    {
        if (a >= b) {
            assert(b >= 0);
            if (b != 0) {
                return gcd(b, a % b);
            } else {
                return a;
            }
        } else {
            return gcd(b, a);
        }
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
                long d = gcd(num, a);
                if (d > 1 || !canPassFermatLittleTheorem(a, num)) {
                    retval = false;
                    break;
                }
            }
        } else {
            retval = (num == 2 || num == 3);
        }
        return retval;
    }

    private static BigInteger gcd(BigInteger a, BigInteger b)
    {
        if (a.compareTo(b) >= 0) {
            assert(b.compareTo(BigInteger.ZERO) >= 0);
            if (b.compareTo(BigInteger.ZERO) > 0) {
                return gcd(b, a.mod(b));
            } else {
                return a;
            }
        } else {
            return gcd(b, a);
        }
    }

    private static boolean _isProbablePrime(BigInteger num, int certainty) {
        var retval = false;
        if (num.and(BigInteger.ONE).compareTo(BigInteger.ONE) == 0) {
            var random = new SecureRandom();
            var len = (num.bitLength() + 7) >> 3;

            retval = true;
            byte[] bytes = new byte[len];
            for (int i = 0; i < certainty; ++i) {
                BigInteger a = null;
                for (;;) {
                    random.nextBytes(bytes);
                    a = new BigInteger(bytes);
                    if (a.compareTo(BigInteger.ZERO) < 0) {
                        a = a.negate();
                    }
                    if (a.compareTo(num) >= 0) {
                        a = a.mod(num);
                    }
                    if (a.compareTo(BigInteger.ZERO) > 0) {
                        break;
                    }
                }

                BigInteger d = gcd(num, a);
                if (
                    d.compareTo(BigInteger.ONE) > 0 ||
                    !canPassFermatLittleTheorem(a, num)
                ) {
                    retval = false;
                    break;
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
