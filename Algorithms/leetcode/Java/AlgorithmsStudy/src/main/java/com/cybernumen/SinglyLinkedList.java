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

    public int length(ListNode head) {
        int retval = 0;
        for (ListNode i = head; i != null; i = i.next) {
            ++retval;
        }
        return retval;
    }

    public ListNode sort(ListNode head) {
        if (head != null && head.next != null) {
            int count = length(head);
            int[] tmp = new int[count];
            int j = 0;
            for (ListNode i = head; i != null; i = i.next) {
                tmp[j++] = i.val;
            }
            java.util.Arrays.sort(tmp);
            j = 0;
            for (ListNode i = head; i != null; i = i.next) {
                i.val = tmp[j++];
            }
        }
        return head;
    }

    private ListNode mergeSort(ListNode head, int count) {
        if (count > 1) {
            int half = count / 2;
            ListNode i = head;
            for (int j = 1; j < half; ++j) {
                i = i.next;
            }
            ListNode tail = i.next;
            i.next = null;
            i = mergeSort(head, half);
            ListNode j = mergeSort(tail, count - half);
            head = null;
            tail = null;
            while (i != null && j != null) {
                if (i.val <= j.val) {
                    if (tail != null) {
                        tail.next = i;
                        tail = i;
                    } else {
                        tail = i;
                        head = i;
                    }
                    i = i.next;
                } else {
                    if (tail != null) {
                        tail.next = j;
                        tail = j;
                    } else {
                        tail = j;
                        head = j;
                    }
                    j = j.next;
                }
            }
            if (j != null) {
                assert (i == null);
                i = j;
            }
            tail.next = i;
            return head;
        } else {
            return head;
        }
    }

    public ListNode mergeSort(ListNode head) {
        return mergeSort(head, length(head));
    }

    public void reorderList(ListNode head) {
        int count = length(head);
        if (count > 1) {
            int half = count / 2;
            ListNode tail = head;
            for (int i = 1; i < half; ++i) {
                tail = tail.next;
            }
            ListNode j = tail.next;
            tail.next = null;
            j = reverse(j);
            ListNode i = head;

            head = tail = null;
            while (i != null && j != null) {
                if (tail != null) {
                    tail.next = i;
                    tail = i;
                } else {
                    head = tail = i;
                }
                i = i.next;
                tail.next = j;
                tail = j;
                j = j.next;
            }
        }
    }

    public ListNode deleteDuplicates(ListNode head) {
        for (ListNode i = head; i != null;) {
            ListNode j = i.next;
            while (j != null && j.val == i.val) {
                j = j.next;
            }
            i.next = j;
            i = j;
        }
        return head;
    }

    public ListNode rotateRight(ListNode head, int k) {
        int len = length(head);
        if (len > 1) {
            k = k % len;
            if (k > 0) {
                int i = len - k;
                ListNode j = head;
                for (int l = 1; l < i; ++l) {
                    j = j.next;
                }
                ListNode newHead = j.next;
                j.next = null;

                j = newHead;
                while (j.next != null) {
                    j = j.next;
                }
                j.next = head;
                head = newHead;
            }
        }
        return head;
    }

    public ListNode partition(ListNode head, int x) {
        if (head != null && head.next != null) {
            ListNode lh = null, lt = null;
            ListNode bh = null, bt = null;
            for (ListNode i = head; i != null; i = i.next) {
                if (i.val < x) {
                    if (lt != null) {
                        lt.next = i;
                        lt = i;
                    } else {
                        lh = lt = i;
                    }
                } else {
                    if (bt != null) {
                        bt.next = i;
                        bt = i;
                    } else {
                        bh = bt = i;
                    }
                }
            }
            if (lt != null) {
                lt.next = bh;
                if (bt != null) {
                    bt.next = null;
                }
                head = lh;
            } else {
                head = bh;
            }
        }
        return head;
    }

    public ListNode reverseBetween(ListNode head, int m, int n) {
        ListNode previous = null;
        ListNode next = head;
        int i = 1;
        while (i < m) {
            previous = next;
            next = next.next;
            ++i;
        }
        ListNode sectionTail = next;
        ListNode sectionHead = next;
        next = next.next;
        sectionTail.next = null;

        for (++i; i <= n; ++i) {
            ListNode tmp = next;
            next = next.next;
            tmp.next = sectionHead;
            sectionHead = tmp;
        }
        sectionTail.next = next;
        if (previous != null) {
            previous.next = sectionHead;
            return head;
        } else {
            return sectionHead;
        }
    }

    public ListNode deleteDuplicates2(ListNode head) {
        if (head != null && head.next != null) {
            ListNode newHead = null;
            ListNode newTail = null;
            ListNode sectionStart = head;
            while (sectionStart != null) {
                int count = 0;
                ListNode next = sectionStart.next;
                while (next != null && next.val == sectionStart.val) {
                    next = next.next;
                    ++count;
                }
                if (count == 0) {
                    if (newTail != null) {
                        newTail.next = sectionStart;
                    } else {
                        newHead = sectionStart;
                    }
                    newTail = sectionStart;
                }
                sectionStart = next;
            }
            if (newTail != null) {
                newTail.next = null;
            }
            head = newHead;
        }
        return head;
    }
}
