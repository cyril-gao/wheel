package com.example;

import java.math.BigInteger;
import java.security.SecureRandom;

import static org.testng.Assert.assertTrue;

import org.testng.annotations.*;

public class PrimeTest {
    @Test
    public void primeTest() {
        assertTrue(Prime.isProbablePrime(BigInteger.TWO));
        int certainty = 40;
        var random = new SecureRandom();
        byte[] bytes = new byte[256];
        for (int i = 0; i < 100;) {
            random.nextBytes(bytes);
            BigInteger num = new BigInteger(bytes);
            if (num.compareTo(BigInteger.ZERO) > 0) {
                assertTrue(
                    Prime.isProbablePrime(num, certainty) == num.isProbablePrime(certainty)
                );
                ++i;
            }
        }
    }
}
