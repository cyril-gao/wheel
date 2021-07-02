package com.example;

import java.math.BigInteger;

public class RSAKeyPair {
    public static RSAKeyPair generate(int numBits) {
        BigInteger p, q;
        while (true) {
            p = Prime.generatePrime(numBits);
            q = Prime.generatePrime(numBits);
            if (!p.equals(q)) {
                break;
            }
        }
        return new RSAKeyPair(p, q);
    }

    private BigInteger e;
    private BigInteger N;
    private BigInteger d;

    private RSAKeyPair(BigInteger p, BigInteger q, BigInteger e) throws IllegalArgumentException {
        this.e = e;
        this.N = p.multiply(q);
        BigInteger M = p.subtract(BigInteger.ONE).multiply(q.subtract(BigInteger.ONE));
        this.d = Number.modInverse(e, M);
    }

    private RSAKeyPair(BigInteger p, BigInteger q) throws IllegalArgumentException {
        this(p, q, BigInteger.valueOf(65537));
    }

    private void checkArgument(BigInteger input) throws IllegalArgumentException {
        if (input.bitLength() > this.N.bitLength() || input.compareTo(this.N) >= 0) {
            throw new IllegalArgumentException("The input argument must be less than " + N.toString());
        }
    }

    public BigInteger publicKeyEncrypt(BigInteger input) throws IllegalArgumentException {
        checkArgument(input);
        return Number.modexp(input, e, N);
    }

    public BigInteger publicKeyDecrypt(BigInteger input) throws IllegalArgumentException {
        checkArgument(input);
        return Number.modexp(input, e, N);
    }

    public BigInteger privateKeyEncrypt(BigInteger input) throws IllegalArgumentException {
        checkArgument(input);
        return Number.modexp(input, d, N);
    }

    public BigInteger privateKeyDecrypt(BigInteger input) throws IllegalArgumentException {
        checkArgument(input);
        return Number.modexp(input, d, N);
    }
}
