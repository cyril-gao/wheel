package com.example;

public class PopulatingNextRightPointersInEachNode {
    public static class Node {
        public int val;
        public Node left;
        public Node right;
        public Node next;

        public Node(int _val, Node _left, Node _right, Node _next) {
            val = _val;
            left = _left;
            right = _right;
            next = _next;
        }

        public Node() {
            this(0);
        }

        public Node(int _val) {
            this(_val, null, null, null);
        }
    };

    // https://leetcode.com/problems/populating-next-right-pointers-in-each-node-ii/
    public Node connect(Node node) {
        for (Node i = node; i != null;) {
            Node newHead = null;
            Node newTail = null;
            for (Node j = i; j != null; j = j.next) {
                if (j.left != null) {
                    if (newTail != null) {
                        newTail.next = j.left;
                    } else {
                        newHead = j.left;
                    }
                    newTail = j.left;
                }
                if (j.right != null) {
                    if (newTail != null) {
                        newTail.next = j.right;
                    } else {
                        newHead = j.right;
                    }
                    newTail = j.right;
                }
                if (newTail != null) {
                    newTail.next = null;
                }
            }
            i = newHead;
        }
        return node;
    }
}
