package com.example;

import java.util.*;

// https://leetcode.com/problems/lru-cache/
public class LRUCache<K, V> {
    static class Node<K, V> {
        K key;
        V value;
        Node<K, V> previous;
        Node<K, V> next;

        public Node(K k, V v) {
            key = k;
            value = v;
            previous = null;
            next = null;
        }

        @Override
        public String toString() {
            return String.format("%s: %s", key, value);
        }
    }

    int capacity;
    int size;
    Node<K, V> head;
    Map<K, Node<K, V>> hashMap;

    public LRUCache(int capacity) {
        if (capacity > 0) {
            this.capacity = capacity;
            this.size = 0;
            head = null;
            if (capacity > 1) {
                hashMap = new HashMap<>();
            }
        } else {
            throw new IllegalArgumentException("The capacity must be greater than 0");
        }
    }

    private void detach(Node<K, V> node) {
        assert (node != head);
        // detach the node from the list
        var previous = node.previous;
        var next = node.next;
        previous.next = next;
        next.previous = previous;
    }

    private void insertFront(Node<K, V> node) {
        assert (node != head);
        // put it into the head of the list
        var tail = head.previous;
        node.next = head;
        node.previous = tail;
        head.previous = node;
        tail.next = node;
        head = node;
    }

    public V get(K key) {
        if (capacity > 1) {
            var v = hashMap.get(key);
            if (v != null) {
                if (v != head) {
                    detach(v);
                    insertFront(v);
                }
                return v.value;
            }
        } else {
            if (head != null && head.key.equals(key)) {
                return head.value;
            }
        }
        return null;
    }

    public void put(K key, V value) {
        if (capacity > 1) {
            var v = hashMap.get(key);
            if (v != null) {
                v.value = value;
                if (v != head) {
                    detach(v);
                    insertFront(v);
                }
            } else {
                ++size;
                var node = new Node<K, V>(key, value);
                if (head != null) {
                    if (size > capacity) {
                        --size;
                        var tail = head.previous;
                        hashMap.remove(tail.key);
                        detach(tail);
                        tail = null;
                    }
                    insertFront(node);
                } else {
                    head = node;
                    head.previous = head;
                    head.next = head;
                }
                hashMap.put(key, node);
            }
        } else {
            if (head != null) {
                head.key = key;
                head.value = value;
            } else {
                head = new Node<K, V>(key, value);
            }
        }
    }

    // only for testing
    V getValue(int index) {
        assert (index >= 0);
        var node = head;
        if (node != null) {
            for (int i = 0; i < index; ++i) {
                node = node.next;
                if (node == head) {
                    node = null;
                }
            }
        }
        return node != null ? node.value : null;
    }

    boolean contains(K key) {
        return hashMap.containsKey(key);
    }

    int getListLength() {
        int count = 0;
        if (head != null) {
            for (var i = head;;) {
                ++count;
                i = i.next;
                if (i == head) {
                    break;
                }
            }
        }
        return count;
    }
}
