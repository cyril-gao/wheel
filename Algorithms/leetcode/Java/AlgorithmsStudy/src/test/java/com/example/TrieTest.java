package com.example;

import org.testng.annotations.*;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertFalse;
import static org.testng.Assert.assertTrue;

public class TrieTest {
    @Test
    public void testTrie() {
        Trie<Integer> dictionary = new Trie<Integer>();
        int index = 0;
        dictionary.put("bad", index++);
        assertTrue(dictionary.contains("bad"));
        assertEquals(dictionary.size(), 1);
        dictionary.put("dad", index++);
        assertTrue(dictionary.contains("dad"));
        assertEquals(dictionary.size(), 2);
        dictionary.put("mad", index++);
        assertTrue(dictionary.contains("mad"));
        assertEquals(dictionary.size(), 3);

        dictionary.remove("dad");
        assertFalse(dictionary.contains("dad"));
        assertEquals(dictionary.size(), 2);

        dictionary.put("pad", index++);
        assertTrue(dictionary.contains("pad"));
        assertEquals(dictionary.size(), 3);
        assertFalse(dictionary.contains("pat"));

        dictionary.put("pad", index++);
        assertTrue(dictionary.contains("bad"));
        assertEquals(dictionary.size(), 3);

        dictionary.put("1", index++);
        dictionary.put("111", index++);
        dictionary.put("111111", index++);
        dictionary.put("1111111111", index++);
        dictionary.put("111111111111111", index++);
        dictionary.put("111111111111111111111", index++);
        dictionary.put("1111111111111111111111111111", index++);
        dictionary.put("111111111111111111111111111111111111", index++);
        assertEquals(dictionary.size(), 11);
        assertFalse(dictionary.contains("paddle"));
        assertFalse(dictionary.contains("111111111"));

        var iter = dictionary.keysWithPrefix("11").iterator();
        int count = 0;
        while (iter.hasNext()) {
            ++count;
            var next = iter.next();
            assertTrue(next.startsWith("11"));
        }
        assertEquals(count, 7);
        var lp = dictionary.longestPrefixOf("111111111111111111111111111111111111");
        assertEquals(lp, "1111111111111111111111111111");

        count = 0;
        iter = dictionary.keys().iterator();
        while (iter.hasNext()) {
            ++count;
            iter.next();
        }
        assertTrue(count == 11);

        dictionary.put("111", index++);
        dictionary.put("she", index++);
        dictionary.put("see", index++);
        count = 0;
        iter = dictionary.keysThatMatch(".ad").iterator();
        while (iter.hasNext()) {
            ++count;
            var next = iter.next();
            assertEquals(next.substring(1), "ad");
        }
        assertEquals(count, 3);

        count = 0;
        iter = dictionary.keysThatMatch("...").iterator();
        while (iter.hasNext()) {
            ++count;
            var next = iter.next();
            assertTrue(next.length() == 3);
        }
        assertEquals(count, 6);

        iter = dictionary.keysThatMatch(".").iterator();
        assertTrue(iter.hasNext());
        assertEquals(iter.next(), "1");
        assertFalse(iter.hasNext());

        assertEquals(dictionary.longestPrefixOf("see"), "");
    }
}
