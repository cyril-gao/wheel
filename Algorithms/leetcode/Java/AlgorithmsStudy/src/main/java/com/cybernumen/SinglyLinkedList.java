package com.cybernumen;

public class SinglyLinkedList {
    public static class ListNode {
        int val;
        ListNode next;
        ListNode(int x) {
            val = x;
            next = null;
        }
    }

    public boolean hasCycle(ListNode head) {
        ListNode normal = head;
        ListNode fast = head;
        while (fast != null && normal != null) {
            normal = normal.next;
            fast = fast.next;
            if (fast != null) {
                fast = fast.next;
            }
            if (fast == normal) {
                break;
            }
        }
        if (fast == null || normal == null) {
            return false;
        }
        return fast == normal;
    }
}
