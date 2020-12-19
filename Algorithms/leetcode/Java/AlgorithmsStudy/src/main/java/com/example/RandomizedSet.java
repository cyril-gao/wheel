package com.example;

import java.util.List;
import java.util.ArrayList;
import java.util.Random;

public class RandomizedSet {
    static class RandomizedSetFullException extends RuntimeException {
        private static final long serialVersionUID = 1L;

        public RandomizedSetFullException() {
            super();
        }
    }

    static class Node {
        int value;
        Node next;

        public Node(int v, Node n) {
            value = v;
            next = n;
        }

        public Node(int v) {
            this(v, null);
        }
    }

    static class Item {
        int value;
        int count;
        Node next;

        public Item(int v, int c, Node n) {
            value = v;
            count = c;
            next = n;
        }

        public Item(int v) {
            this(v, 1, null);
        }
    }

    int bufSize;
    int itemSize;
    List<Item> items;
    int[] cache;
    int nextIndexInCache;

    Random random;
    final double A = (Math.sqrt(5) - 1) / 2;

    public int size() {
        return itemSize;
    }

    public boolean isEmpty() {
        return itemSize == 0;
    }

    public boolean contains(int val) {
        boolean retval = false;
        Item item = items.get(getIndex(val));
        if (item != null) {
            if (item.value == val) {
                retval = true;
            } else {
                for (Node i = item.next; i != null; i = i.next) {
                    if (i.value == val) {
                        retval = true;
                        break;
                    }
                }
            }
        }
        return retval;
    }

    private int getIndex(int val) {
        double v1 = val * A;
        double v2 = v1 - Math.floor(v1);
        return (int) Math.floor(bufSize * v2);
    }

    private boolean insert(int val, boolean needResh) {
        boolean retval = false;
        boolean reshaed = false;
        int i = getIndex(val);
        Item item = items.get(i);
        if (item == null) {
            item = new Item(val);
            items.set(i, item);
            ++itemSize;
            retval = true;
        } else {
            if (item.value != val) {
                Node node = item.next;
                while (node != null) {
                    if (node.value == val) {
                        break;
                    }
                    node = node.next;
                }
                if (node == null) {
                    node = new Node(val, item.next);
                    item.next = node;
                    ++item.count;
                    ++itemSize;
                    if (needResh) {
                        if (item.count > 3 || (itemSize / bufSize) > 0.9) {
                            rehash(bufSize * 2, items);
                            reshaed = true;
                        }
                    }
                    retval = true;
                }
            }
        }
        if (retval) {
            if (!reshaed) {
                if (nextIndexInCache >= cache.length) {
                    if (needResh) {
                        rehash(bufSize * 2, items);
                    } else {
                        throw new RandomizedSetFullException();
                    }
                }
                cache[nextIndexInCache++] = val;
            }
        }
        return retval;
    }

    private void rehash(int newBufSize, List<Item> old) {
        assert (newBufSize > itemSize);
        bufSize = newBufSize;
        itemSize = 0;
        items = new ArrayList<Item>(bufSize);
        for (int i = 0; i < bufSize; ++i) {
            items.add(null);
        }
        cache = new int[bufSize];
        nextIndexInCache = 0;
        if (old != null) {
            for (Item item : old) {
                if (item != null) {
                    insert(item.value, false);
                    for (Node node = item.next; node != null; node = node.next) {
                        insert(node.value, false);
                    }
                }
            }
        }
    }

    private void rebuildCache() {
        cache = new int[bufSize];
        nextIndexInCache = 0;
        for (Item item : items) {
            if (item != null) {
                cache[nextIndexInCache++] = item.value;
                for (Node node = item.next; node != null; node = node.next) {
                    cache[nextIndexInCache++] = node.value;
                }
            }
        }
    }

    /** Initialize your data structure here. */
    public RandomizedSet() {
        rehash(16, null);
        random = new Random();
    }

    /**
     * Inserts a value to the set. Returns true if the set did not already contain
     * the specified element.
     */
    public boolean insert(int val) {
        return insert(val, true);
    }

    private void removeItem(int index, Item item) {
        assert (items.get(index) == item);
        if (item.count == 1) {
            assert (item.next == null);
            items.set(index, null);
        } else {
            Node node = item.next;
            assert (node != null);
            item.next = node.next;
            item.value = node.value;
            --item.count;
        }
        --itemSize;
    }

    /**
     * Removes a value from the set. Returns true if the set contained the specified
     * element.
     */
    public boolean remove(int val) {
        boolean retval = false;
        int i = getIndex(val);
        Item item = items.get(i);
        if (item != null) {
            if (item.value == val) {
                removeItem(i, item);
                retval = true;
            } else {
                Node previous = null;
                Node next = item.next;
                while (next != null) {
                    if (next.value == val) {
                        break;
                    }
                    previous = next;
                    next = next.next;
                }
                if (next != null) {
                    assert (next.value == val);
                    --item.count;
                    if (previous == null) {
                        item.next = next.next;
                    } else {
                        previous.next = next.next;
                    }
                    retval = true;
                }
            }
        }
        /*
         * if (retval) { if ((itemSize / nextIndexInCache) < 0.5) {
         * rehash(Math.max(itemSize, bufSize), items); } }
         */
        return retval;
    }

    /** Get a random element from the set. */
    public int getRandom() {
        if ((itemSize / nextIndexInCache) < 0.25) {
            rebuildCache();
        }
        while (true) {
            int i = random.nextInt(nextIndexInCache);
            int v = cache[i];
            if (contains(v)) {
                return v;
            }
        }
    }
}
