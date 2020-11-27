package com.cybernumen;

public class SinglyLinkedList {
    public static class ListNode {
        int val;
        ListNode next;

        ListNode(int x, ListNode next) {
            this.val = x;
            this.next = next;
        }

        ListNode(int x) {
            this(x, null);
        }

        ListNode() {
            this(0, null);
        }

        @Override
        public String toString() {
            return String.format("%d%s", this.val, this.next != null ? "->" : "");
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

    public boolean isSorted(ListNode head) {
        boolean retval = true;
        if (head != null && head.next != null) {
            for (ListNode i = head, j = i.next; j != null; i = j, j = j.next) {
                if (i.val > j.val) {
                    retval = false;
                    break;
                }
            }
        }
        return retval;
    }

    public ListNode reverse(ListNode head) {
        ListNode retval = head;
        if (head != null && head.next != null) {
            ListNode i = head.next;
            retval.next = null;
            while (i != null) {
                ListNode j = i.next;
                i.next = retval;
                retval = i;
                i = j;
            }
        }
        return retval;
    }

    public ListNode insertionSortList(ListNode head) {
        ListNode retval = head;
        if (head != null && head.next != null) {
            ListNode newHead = head;
            ListNode i = newHead.next;
            newHead.next = null;
            while (i != null) {
                ListNode next = i.next;
                ListNode previous = null;
                ListNode j = newHead;
                while (j != null) {
                    if (i.val < j.val) {
                        previous = j;
                        j = j.next;
                    } else {
                        break;
                    }
                }
                if (previous != null) {
                    i.next = j;
                    previous.next = i;
                } else {
                    i.next = newHead;
                    newHead = i;
                }
                i = next;
            }
            retval = reverse(newHead);
        }
        return retval;
    }

    public static void main(String[] args) {
        SinglyLinkedList sll = new SinglyLinkedList();
        {
            var n1 = new SinglyLinkedList.ListNode(1);
            var n2 = new SinglyLinkedList.ListNode(2);
            var n3 = new SinglyLinkedList.ListNode(3);
            var n4 = new SinglyLinkedList.ListNode(4);
            n2.next = n1;
            sll.insertionSortList(n2);
            n3.next = n2;
            sll.insertionSortList(n3);
            n4.next = n3;
            sll.insertionSortList(n4);
        }
    }
}
