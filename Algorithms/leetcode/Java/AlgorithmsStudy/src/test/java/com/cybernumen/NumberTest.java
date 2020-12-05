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
}
