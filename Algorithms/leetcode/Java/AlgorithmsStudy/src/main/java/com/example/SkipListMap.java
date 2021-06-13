package com.example;

import java.util.*;

public class SkipListMap<K, V> {
    static class Node<K, V> {
        K key;
        V value;
        List<Node<K, V>> previous;
        List<Node<K, V>> next;

        Node(K key, V value, int size) {
            this.key = key;
            this.value = value;
            this.previous = new ArrayList<>(size);
            this.next = new ArrayList<>(size);
            for (int i = 0; i < size; ++i) {
                this.previous.add(null);
                this.next.add(null);
            }
        }

        Node() {
            this(null, null, 1);
        }
    }

    private static int log2(int n) {
        assert(n > 0);
        int retval = 0;
        for (int i = 1; i < n; i <<= 1, ++retval) {}
        return retval;
    }

    private int size;
    private Node<K, V> head;
    private Comparator<K> comparator;
    private Random random;

    public SkipListMap(Comparator<K> comparator) {
        this.size = 0;
        this.head = new Node<K, V>();
        this.head.next = new ArrayList<>();
        this.head.next.add(null);
        this.comparator = comparator;
        this.random = new Random();
    }

    static class FindingResult<K, V> {
        List<Node<K, V>> ancestors;
        Node<K, V> self;

        FindingResult(
            List<Node<K, V>> ancestors,
            Node<K, V> self
        ) {
            this.ancestors = ancestors;
            this.self = self;
        }
    }

    private FindingResult<K, V> find(K key) {
        var ancestors = new ArrayList<Node<K, V>>(head.next.size());
        Node<K, V> self = null;
        Node<K, V> previous = this.head;
        for (int n = head.next.size() - 1; n >= 0; --n) {
            Node<K, V> i = previous.next.get(n);
            while (i != null && this.comparator.compare(i.key, key) < 0) {
                previous = i;
                i = i.next.get(n);
            }
            ancestors.add(previous);
            if (i != null && this.comparator.compare(i.key, key) == 0) {
                self = i;
                break;
            }
        }
        return new FindingResult<>(ancestors, self);
    }

    public boolean contains(K key) {
        return find(key).self != null;
    }

    public void put(K key, V value) {
        var result = find(key);
        if (result.self == null) {
            ++this.size;
            int n = 0;
            for (int b = log2(this.size) + 1; n < b && random.nextDouble() > 0.5; ++n) {}
            if (n == 0) {
                n = 1;
            }
            Node<K, V> node = new Node<K, V>(key, value, n);
            Collections.reverse(result.ancestors);
            for (int i = 0, ie = Math.min(n, result.ancestors.size()); i < ie; ++i) {
                var previous = result.ancestors.get(i);
                var next = previous.next.get(i);
                if (previous != null) {
                    previous.next.set(i, node);
                }
                node.previous.set(i, previous);
                node.next.set(i, next);
                if (next != null) {
                    next.previous.set(i, node);
                }
            }
            for (int i = head.next.size(); i < n; ++i) {
                head.next.add(node);
            }
            for (int i = result.ancestors.size(); i < n; ++i) {
                node.previous.set(i, head);
            }
        } else {
            result.self.value = value;
        }
    }

    public boolean remove(K key) {
        boolean retval = false;
        var result = find(key);
        var toBeDeleted = result.self;
        if (toBeDeleted != null) {
            retval = true;
            --this.size;
            for (int i = toBeDeleted.next.size(); i > 0;) {
                --i;
                var previous = toBeDeleted.previous.get(i);
                var next = toBeDeleted.next.get(i);
                if (previous != null) {
                    previous.next.set(i, next);
                }
                if (next != null) {
                    next.previous.set(i, previous);
                }
            }
        }
        return retval;
    }

    public int size() { return this.size; }
}
