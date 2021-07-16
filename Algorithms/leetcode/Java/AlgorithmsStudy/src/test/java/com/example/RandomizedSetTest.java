package com.example;

import java.util.*;

import static org.testng.Assert.assertTrue;
import static org.testng.Assert.assertFalse;
import org.testng.annotations.*;

public class RandomizedSetTest {
    @Test
    public void testCase1() {
        var rs = new RandomizedSet();
        {
            assertTrue(rs.isEmpty());
            var r = rs.insert(1);
            assertTrue(r);
            r = rs.remove(2);
            assertFalse(r);
            r = rs.insert(2);
            assertTrue(r);
            int v = rs.getRandom();
            assertTrue(v == 1 || v == 2);
            r = rs.remove(1);
            assertTrue(r);
            r = rs.insert(2);
            assertFalse(r);
            v = rs.getRandom();
            assertTrue(v == 2);
        }
    }

    @Test
    public void testCase2() {
        var rs = new RandomizedSet();
        var hs = new HashSet<Integer>();
        var random = new Random();
        for (int i = 0, limit = 1000000; i < limit; ++i) {
            int val = random.nextInt(limit / 50);
            int d = random.nextInt(limit);
            if ((d & 1) != 0) {
                var r1 = hs.add(val);
                var r2 = rs.insert(val);
                if (r1 != r2) {
                    System.err.println(i);
                    assertTrue(false);
                }
                rs.getRandom();
            } else {
                var r1 = hs.remove(val);
                var r2 = rs.remove(val);
                if (r1 != r2) {
                    System.err.println(i);
                    assertTrue(false);
                }
                if (!rs.isEmpty()) {
                    rs.getRandom();
                }
            }
        }
    }
}
