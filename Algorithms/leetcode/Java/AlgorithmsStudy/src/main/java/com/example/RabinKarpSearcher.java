package com.example;

import java.util.Random;
import java.math.BigInteger;

class RabinKarp {
    private String pattern;
    private long R; // radix
    private long Q;
    private long patternHash;
    private long RM; // R ^ (M-1) % Q

    private static long generateLargePrime() {
        return BigInteger.probablePrime(31, new Random()).longValue();
    }

    private long hash(String value, int length) {
        long retval = 0;
        for (int i = 0; i < length; ++i) {
            retval = (R * retval + value.charAt(i)) % Q;
        }
        return retval;
    }

    private boolean matched(String txt, int start) {
        boolean retval = true;
        for (int i = 0, ie = pattern.length(), j = start; i < ie; ++i, ++j) {
            if (pattern.charAt(i) != txt.charAt(j)) {
                retval = false;
                break;
            }
        }
        return retval;
    }

    RabinKarp(String pattern, long R) {
        this.pattern = pattern;
        this.R = R;
        this.Q = generateLargePrime();
        int M = pattern.length();
        this.patternHash = hash(pattern, M);
        this.RM = 1;
        R = R % Q;
        --M;
        for (int i = 1; i <= M; i <<= 1) {
            if ((i & M) != 0) {
                this.RM = (this.RM * R) % Q;
            }
            R = (R * R) % Q;
        }
    }

    int search(String txt) {
        int retval = -1;
        int n = txt.length();
        int m = pattern.length();
        if (n >= m) {
            long txtHash = hash(txt, m);
            if (patternHash == txtHash && matched(txt, 0)) {
                retval = 0;
            } else {
                for (int i = m, j = 0, k = 1; i < n; ++i, ++j, ++k) {
                    txtHash = (txtHash + Q - RM * txt.charAt(j) % Q) % Q;
                    txtHash = (txtHash * R + txt.charAt(i)) % Q;
                    if (patternHash == txtHash && matched(txt, k)) {
                        retval = k;
                        break;
                    }
                }
            }
        }
        return retval;
    }
}

public class RabinKarpSearcher implements SubstringSearcher {
    public int search(String s, String p) {
        return new RabinKarp(p, 65536).search(s);
    }
}
