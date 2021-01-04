package com.example;

import java.util.*;

// https://leetcode.com/problems/insert-delete-getrandom-o1-duplicates-allowed/
public class RandomizedCollection {
    int size;
    Map<Integer, Set<Integer>> map;

    int[] buffer;
    int next;

    private void rebuildBuffer(Map<Integer, Set<Integer>> old) {
        buffer = new int[Math.max(size * 2, 32)];
        size = 0;
        next = 0;
        map = new HashMap<Integer, Set<Integer>>();
        if (old != null) {
            for (Integer k : old.keySet()) {
                Set<Integer> indices = new HashSet<Integer>();
                int val = k.intValue();
                for (int i = 0, ie = old.get(k).size(); i < ie; ++i) {
                    buffer[next] = val;
                    indices.add(Integer.valueOf(next));
                    ++next;
                }
                map.put(k, indices);
            }
            size = next;
        }
    }

    /** Initialize your data structure here. */
    public RandomizedCollection() {
        rebuildBuffer(null);
    }

    /**
     * Inserts a value to the collection. Returns true if the collection did not
     * already contain the specified element.
     */
    public boolean insert(int val) {
        if (next >= buffer.length) {
            rebuildBuffer(map);
        }
        Integer key = Integer.valueOf(val);
        Set<Integer> indices = map.get(key);
        if (indices == null) {
            indices = new HashSet<Integer>();
        }
        indices.add(next);
        buffer[next++] = val;
        map.put(key, indices);
        ++size;
        return indices.size() == 1;
    }

    /**
     * Removes a value from the collection. Returns true if the collection contained
     * the specified element.
     */
    public boolean remove(int val) {
        boolean retval = false;
        Integer key = Integer.valueOf(val);
        Set<Integer> indices = map.get(key);
        if (indices != null) {
            retval = true;
            Integer v = indices.iterator().next();
            indices.remove(v);
            if (indices.isEmpty()) {
                indices = null;
            }
            --size;
            if (indices != null) {
                map.put(key, indices);
            } else {
                map.remove(key);
            }
        }
        return retval;
    }

    /** Get a random element from the collection. */
    public int getRandom() {
        if (size > 0) {
            if (((double) size / next) < 0.5) {
                rebuildBuffer(map);
            }
            Random r = new Random();
            while (true) {
                int i = r.nextInt(next);
                int v = buffer[i];
                Integer key = Integer.valueOf(v);
                Set<Integer> indices = map.get(key);
                if (indices != null && indices.contains(i)) {
                    return v;
                }
            }
        } else {
            throw new RuntimeException("The collction is empty");
        }
    }

    int size() {
        return size;
    }
}
