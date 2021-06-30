package com.example;

import java.math.BigInteger;
import static org.testng.Assert.assertEquals;

import org.testng.annotations.*;

public class NumberTest {
    @Test
    public void testModexp() {
        {
            long[] ys = {
                1, 7, 16, 34897, 324756734L, 345234523534L, 3452345235334L, 3452834523534L,
                34528345923534L, 4611686018427387904L, 9223372036854775803L
            };
            var xs = ys;
            var Ns = ys;
            for (var x : xs) {
                for (var y : ys) {
                    for (var N : Ns) {
                        var result = Number.modexp(x, y, N);
                        var expectation = BigInteger.valueOf(x).modPow(BigInteger.valueOf(y), BigInteger.valueOf(N)).longValue();
                        assertEquals(result, expectation);
                    }
                }
            }
        }
        {
            BigInteger[] ys = {
                BigInteger.ONE, BigInteger.valueOf(16), BigInteger.valueOf(3452345235334L),
                BigInteger.valueOf(9223372036854775797L),
                new BigInteger("1208925819614629174706176"),
                new BigInteger("28486523256234784562347865238527"),
                new BigInteger("384865232562347845623478652384867527"),
                new BigInteger("484865232562347845623478652385234589627"),
                new BigInteger("5894957384865232562347845623478652385234589627")
            };
            var xs = ys;
            var Ns = ys;
            for (var x : xs) {
                for (var y : ys) {
                    for (var N : Ns) {
                        var result = Number.modexp(x, y, N);
                        var expectation = x.modPow(y, N);
                        assertEquals(result, expectation);
                    }
                }
            }
        }
    }


    @Test
    public void testEuclid() {
        BigInteger[] nums = {
            new BigInteger("34572348765237453244"),
            new BigInteger("83465324523325823466"),
            new BigInteger("834653245233258234665"),
            new BigInteger("8346532452332582346623"),
            new BigInteger("349574356237452364523645"),
            new BigInteger("34957435623745236452364523"),
            new BigInteger("387456234566234523487562634"),
            new BigInteger("39845723465234652365324323665")
        };
        for (var a : nums) {
            for (var b : nums) {
                //System.out.printf("gcd(%s, %s)%n", a.toString(), b.toString());
                var result = Number.euclid(a, b);
                assertEquals(result[1].multiply(a).add(result[2].multiply(b)), result[0]);
            }
        }
    }
}
