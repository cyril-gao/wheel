package com.example;

import java.util.Comparator;

import org.testng.annotations.*;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertFalse;
import static org.testng.Assert.assertTrue;

class MyComp implements Comparator<String> {
    @Override
    public int compare(String str1, String str2) {
        return str1.compareTo(str2);
    }
}

public class SkipListMapTest {
    @Test
    public void testAdding() {
        var sl = new SkipListMap<String, Integer>(new MyComp());
        for (int i = 0; i < 1000; ++i) {
            Integer v = Integer.valueOf(i);
            sl.put(v.toString(), v);
            assertTrue(sl.contains(v.toString()));
            v = Integer.valueOf(i + 1);
            assertFalse(sl.contains(v.toString()));
        }
    }

    @Test
    public void testRemoving() {
        final int limit = 1000;
        var sl = new SkipListMap<String, Integer>(new MyComp());
        for (int i = 0; i < limit; ++i) {
            Integer v = Integer.valueOf(i);
            sl.put(v.toString(), v);
        }
        for (int i = 0; i < limit; ++i) {
            var k = Integer.valueOf(i).toString();
            assertTrue(sl.remove(k));
            assertFalse(sl.contains(k));
        }
        assertEquals(sl.size(), 0);
    }
}
