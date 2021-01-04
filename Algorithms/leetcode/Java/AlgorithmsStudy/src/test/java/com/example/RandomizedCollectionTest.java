package com.example;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertTrue;
import static org.testng.Assert.assertFalse;
import org.testng.annotations.*;

public class RandomizedCollectionTest {
    @Test
    public void testCase1() {
        var rc = new RandomizedCollection();
        var result = rc.insert(1);
        assertTrue(result);
        assertEquals(rc.size(), 1);
        result = rc.insert(1);
        assertFalse(result);
        assertEquals(rc.size(), 2);
        result = rc.insert(2);
        assertTrue(result);
        assertEquals(rc.size(), 3);
        for (int i = 0; i < 6; ++i) {
            var v = rc.getRandom();
            assertTrue(v == 1 || v == 2);
            // System.out.println(v);
        }
        result = rc.remove(1);
        assertTrue(result);
        assertEquals(rc.size(), 2);
        for (int i = 0; i < 6; ++i) {
            var v = rc.getRandom();
            assertTrue(v == 1 || v == 2);
            // System.out.println(v);
        }
    }
}
