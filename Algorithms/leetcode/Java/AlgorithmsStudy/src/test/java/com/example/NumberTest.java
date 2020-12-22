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
}
