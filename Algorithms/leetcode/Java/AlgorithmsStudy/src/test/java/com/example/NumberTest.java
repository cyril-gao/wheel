package com.example;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertNotEquals;
import static org.testng.Assert.assertTrue;
import static org.testng.Assert.assertFalse;

import org.testng.annotations.*;

import java.util.*;

public class NumberTest {
    @Test
    public void testDivide() {
        Number n = new Number();
        assertEquals(n.divide(Integer.MIN_VALUE, 1), Integer.MIN_VALUE);
        assertEquals(n.divide(Integer.MIN_VALUE, -1), Integer.MAX_VALUE);
        assertNotEquals(n.divide(Integer.MIN_VALUE, -1), Integer.MIN_VALUE / -1);
        assertEquals(n.divide(Integer.MAX_VALUE, Integer.MAX_VALUE), Integer.MAX_VALUE / Integer.MAX_VALUE);
        assertEquals(n.divide(2474, -44), 2474 / -44);
        assertEquals(n.divide(-2474, -44), -2474 / -44);
        assertEquals(n.divide(1776873474, 13), 1776873474 / 13);
        assertEquals(n.divide(24, -44), 24 / -44);
        assertEquals(n.divide(-24, 44), -24 / 44);
    }

    @Test
    public void testSqrt() {
        Number n = new Number();
        int retry = 1234567;
        for (int i = 0; i < retry; ++i) {
            int v1 = n.mySqrt(i);
            int v2 = (int) Math.floor(Math.sqrt(i));
            if (v1 != v2) {
                System.out.printf("sqrt of %d: %d <-> %d%n", i, v1, v2);
                assertEquals(n.mySqrt(i), (int) Math.floor(Math.sqrt(i)));
            }
        }
        for (int i = Integer.MAX_VALUE; i > (Integer.MAX_VALUE - retry); --i) {
            int v1 = n.mySqrt(i);
            int v2 = (int) Math.floor(Math.sqrt(i));
            if (v1 != v2) {
                System.out.printf("sqrt of %d: %d <-> %d%n", i, v1, v2);
                assertEquals(n.mySqrt(i), (int) Math.floor(Math.sqrt(i)));
            }
        }
    }

    @Test
    public void testFindNthDigit() {
        Number n = new Number();
        {
            var r = n.findNthDigit(1000000000);
            assertEquals(r, 1);
        }
        StringBuffer sb = new StringBuffer();
        for (int i = 1; i < 1000; ++i) {
            sb.append(Integer.valueOf(i).toString());
        }
        String s = sb.toString();
        for (int i = 0; i < 1000;) {
            int j = i + 1;
            var r = n.findNthDigit(j);
            // System.out.println(j);
            assertEquals(s.charAt(i), (char) (r + '0'));
            i = j;
        }
    }

    @Test
    public void testIsPerfectSquare() {
        Number n = new Number();
        Set<Integer> nums = new HashSet<>();
        nums.add(0);
        nums.add(1);
        nums.add(4);
        nums.add(9);
        nums.add(16);
        nums.add(25);
        nums.add(36);
        nums.add(49);
        nums.add(64);
        nums.add(81);
        nums.add(100);
        for (int i = 0; i < 110; ++i) {
            if (nums.contains(i)) {
                assertTrue(n.isPerfectSquare(i));
            } else {
                assertFalse(n.isPerfectSquare(i));
            }
        }
        assertFalse(n.isPerfectSquare(Integer.MAX_VALUE));
        assertTrue(n.isPerfectSquare(2147395600));
    }

    @Test
    public void testValidUtf8() {
        Number n = new Number();
        {
            int[] data = { 197, 130, 1 };
            assertTrue(n.validUtf8(data));
        }
        {
            int[] data = { 235, 140, 4 };
            assertFalse(n.validUtf8(data));
        }
        {
            int[] data = { 0xec, 0xb3, 0x9c, 197, 130, 1, 235, 140, 4 };
            assertFalse(n.validUtf8(data));
        }
        {
            int[] data = { 0xec, 0xb3, 0x9c, 197, 130, 1 };
            assertTrue(n.validUtf8(data));
        }
        {
            int[] data = { 0xf7, 0xb3, 0x9c, 0x82, 197, 130, 1 };
            assertTrue(n.validUtf8(data));
        }
    }

    @Test
    public void testCountNumbersWithUniqueDigits() {
        Number n = new Number();
        assertEquals(n.countNumbersWithUniqueDigits(0), 1);
        assertEquals(n.countNumbersWithUniqueDigits(1), 10);
        assertEquals(n.countNumbersWithUniqueDigits(2), 91);
        assertEquals(n.countNumbersWithUniqueDigits(3), 739);
        assertEquals(n.countNumbersWithUniqueDigits(4), 5275);
        assertEquals(n.countNumbersWithUniqueDigits(5), 32491);
        assertEquals(n.countNumbersWithUniqueDigits(6), 168571);
        assertEquals(n.countNumbersWithUniqueDigits(7), 712891);
        assertEquals(n.countNumbersWithUniqueDigits(8), 2345851);
        assertEquals(n.countNumbersWithUniqueDigits(9), 5611771);
        assertEquals(n.countNumbersWithUniqueDigits(10), 8877691);
        assertEquals(n.countNumbersWithUniqueDigits(11), 8877691);
        assertEquals(n.countNumbersWithUniqueDigits(12), 8877691);
    }

    @Test
    public void testSuperPow() {
        Number n = new Number();
        {
            int[] b = { 3 };
            assertEquals(n.superPow(2, b), 8);
        }
        {
            int[] b = { 0 };
            assertEquals(n.superPow(2, b), 1);
        }
        {
            int[] b = { 1, 0 };
            assertEquals(n.superPow(2, b), 1024);
        }
        {
            int[] b = { 4, 3, 3, 8, 5, 2 };
            assertEquals(n.superPow(1, b), 1);
        }
        {
            int[] b = { 2, 0, 0 };
            assertEquals(n.superPow(2147483647, b), 1198);
        }
        {
            int[] b = { 3, 4, 5, 7, 4, 3, 5 };
            assertEquals(n.superPow(390457, b), 802);
        }
        {
            int[] b = { 3, 4, 5, 7, 4, 3, 5 };
            assertEquals(n.superPow(2147483647, b), 1121);
        }
    }

    @Test
    public void testFractionToDecimal() {
        Number n = new Number();
        {
            var result = n.fractionToDecimal(11, 2);
            assertEquals(result, "5.5");

            result = n.fractionToDecimal(92, 46);
            assertEquals(result, "2");

            result = n.fractionToDecimal(5, 3);
            assertEquals(result, "1.(6)");

            result = n.fractionToDecimal(1, 1048576);
            assertEquals(result, "0.00000095367431640625");

            result = n.fractionToDecimal(670, 333);
            assertEquals(result, "2.(012)");

            result = n.fractionToDecimal(37037, 300000);
            assertEquals(result, "0.12345(6)");

            result = n.fractionToDecimal(-50, 8);
            assertEquals(result, "-6.25");

            result = n.fractionToDecimal(0, -8);
            assertEquals(result, "0");

            {
                String expectation = "-0.0000000004656612873077392578125";
                result = n.fractionToDecimal(1, Integer.MIN_VALUE);
                assertEquals(result, expectation);
            }
            {
                result = n.fractionToDecimal(210756734, 112700000);
                String expectation = "1.87006(862466725820763087843833185448092280390417036379769299023957409050576752440106477373558118899733806566104702750665483584738243123336291038154392191659272404614019520851818988464951197870452528837622005323868677905944986690328305235137533274179236912156166814551907719609582963620230700976042590949423247559893522626441881100266193433895297249334516415261756876663708961845607808340727595385980479148181011535048802129547471162377994676131322094055013309671694764)";
                assertEquals(result, expectation);
            }
        }
    }
}
