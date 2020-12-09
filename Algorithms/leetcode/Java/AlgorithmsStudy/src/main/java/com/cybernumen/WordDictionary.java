package com.cybernumen;

import java.util.*;

// Trie
public class WordDictionary {
    static class Node {
        boolean exist;
        Map<Character, Node> children;

        public Node() {
            exist = false;
            children = new HashMap<Character, Node>();
        }

        @Override
        public String toString() {
            StringBuffer sb = new StringBuffer();
            sb.append('[');
            boolean firstTime = true;
            for (Character c : children.keySet()) {
                if (!firstTime) {
                    sb.append(',');
                } else {
                    firstTime = false;
                }
                sb.append(c.charValue());
            }
            sb.append(']');
            return sb.toString();
        }
    }

    private Node root;
    private int count;

    private static boolean atLeastOneChildExists(Node node) {
        if (node != null) {
            if (!node.exist) {
                for (Character c : node.children.keySet()) {
                    if (atLeastOneChildExists(node.children.get(c))) {
                        return true;
                    }
                }
            } else {
                return true;
            }
        }
        return false;
    }

    private static Node search(Node first, String s, int start, boolean appending, boolean atLeastOneChildMustExist) {
        Node retval = first;
        int n = s != null ? s.length() : 0;
        for (int i = start; i < n; ++i) {
            char c = s.charAt(i);
            if (c != '.') {
                Node next = retval.children.get(c);
                if (next != null) {
                    retval = next;
                } else {
                    if (appending) {
                        while (i < n) {
                            c = s.charAt(i);
                            Node newNode = new Node();
                            retval.children.put(c, newNode);
                            retval = newNode;
                            ++i;
                        }
                    } else {
                        retval = null;
                    }
                    break;
                }
            } else {
                assert (!appending);
                first = retval;
                retval = null;
                for (Character k : first.children.keySet()) {
                    Node r = search(first.children.get(k), s, i + 1, false, atLeastOneChildMustExist);
                    if (!atLeastOneChildMustExist) {
                        if (r != null && r.exist) {
                            retval = r;
                            break;
                        }
                    } else {
                        if (r != null) {
                            retval = r;
                            break;
                        }
                    }
                }
                break;
            }
        }
        if (atLeastOneChildMustExist) {
            if (retval != null) {
                if (!atLeastOneChildExists(retval)) {
                    retval = null;
                }
            }
        }
        return retval;
    }

    private static Node search(Node first, String s, boolean appending, boolean atLeastOneChildMustExist) {
        return search(first, s, 0, appending, atLeastOneChildMustExist);
    }

    public WordDictionary() {
        root = new Node();
        count = 0;
    }

    public boolean add(String s) {
        Node r = search(root, s, true, false);
        boolean retval = !r.exist;
        r.exist = true;
        if (retval) {
            ++count;
        }
        return retval;
    }

    public boolean remove(String s) {
        Node r = search(root, s, false, false);
        boolean retval = r != null ? r.exist : false;
        if (r != null) {
            r.exist = false;
        }
        if (retval) {
            --count;
        }
        return retval;
    }

    public boolean contains(String s) {
        Node r = search(root, s, false, false);
        return (r != null && r.exist);
    }

    public boolean isEmpty() {
        return count == 0;
    }

    public int size() {
        return count;
    }

    public boolean startsWith(String prefix) {
        return search(root, prefix, false, true) != null;
    }
}
