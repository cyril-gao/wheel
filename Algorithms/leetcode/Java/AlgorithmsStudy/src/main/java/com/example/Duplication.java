package com.example;

import java.util.*;

public class Duplication {
    public static class Node<T> {
        public T value;
        public List<Node<T>> neighbors;

        public Node(T value) {
            this.value = value;
            this.neighbors = new ArrayList<>();
        }
    }

    private static<T> Node<T> copy(Node<T> node, Map<Node<T>, Node<T>> visited) {
        var retval = visited.get(node);
        if (retval == null) {
            retval = new Node<T>(node.value);
            visited.put(node, retval);
            for (var n : node.neighbors) {
                retval.neighbors.add(copy(n, visited));
            }
        }
        return retval;
    }

    public static<T> Node<T> copy(Node<T> node) {
        Node<T> retval = null;
        if (node != null) {
            Map<Node<T>, Node<T>> visited = new HashMap<>();
            retval = copy(node, visited);
        }
        return retval;
    }

    public static class NodeWithRandomNeighbor<T> {
        public T value;
        public NodeWithRandomNeighbor<T> next;
        public NodeWithRandomNeighbor<T> random;

        public NodeWithRandomNeighbor(T value) {
            this.value = value;
            this.next = null;
            this.random = null;
        }
    }

    public static<T> NodeWithRandomNeighbor<T> copy(NodeWithRandomNeighbor<T> node) {
        NodeWithRandomNeighbor<T> retval = null;
        if (node != null) {
            NodeWithRandomNeighbor<T> previous = null;
            Map<NodeWithRandomNeighbor<T>, NodeWithRandomNeighbor<T>> map = new HashMap<>();
            for (var n = node; n != null; n = n.next) {
                var newNode = new NodeWithRandomNeighbor<T>(n.value);
                map.put(n, newNode);
                if (previous != null) {
                    previous.next = newNode;
                } else {
                    retval = newNode;
                }
                previous = newNode;
            }
            for (var n = node; n != null; n = n.next) {
                var r = map.get(n.random);
                map.get(n).random = r;
            }
        }
        return retval;
    }
}
