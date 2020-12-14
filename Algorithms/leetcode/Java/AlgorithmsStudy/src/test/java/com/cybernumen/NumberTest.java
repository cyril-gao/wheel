package com.cybernumen;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertNotEquals;
import org.testng.annotations.*;

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
        for (int i = 1; i < 100000; ++i) {
            sb.append(Integer.valueOf(i).toString());
        }
        String s = sb.toString();
        for (int i = 0; i < 100000;) {
            int j = i + 1;
            var r = n.findNthDigit(j);
            // System.out.println(j);
            assertEquals(s.charAt(i), (char) (r + '0'));
            i = j;
        }
    }
}
