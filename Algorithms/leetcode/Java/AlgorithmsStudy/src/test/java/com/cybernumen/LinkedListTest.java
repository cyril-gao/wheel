package com.cybernumen;

import static org.testng.Assert.assertTrue;
import static org.testng.Assert.assertEquals;
import org.testng.annotations.*;

public class LinkedListTest {
    @Test
    public void testHasCycle() {
        SinglyLinkedList sll = new SinglyLinkedList();
        assertTrue(!sll.hasCycle(null));
        {
            var n3 = new SinglyLinkedList.ListNode(3);
            var n2 = new SinglyLinkedList.ListNode(2);
            var n0 = new SinglyLinkedList.ListNode(0);
            var nn4 = new SinglyLinkedList.ListNode(-4);
            n3.next = n2;
            n2.next = n0;
            n0.next = nn4;
            nn4.next = n2;

            assertTrue(sll.hasCycle((n3)));
        }
        {
            var n1 = new SinglyLinkedList.ListNode(1);
            var n2 = new SinglyLinkedList.ListNode(2);
            n1.next = n2;
            n2.next = n1;

            assertTrue(sll.hasCycle((n1)));
        }
        {
            var n1 = new SinglyLinkedList.ListNode(1);
            n1.next = n1;
            assertTrue(sll.hasCycle((n1)));
        }
        {
            var n3 = new SinglyLinkedList.ListNode(3);
            var n2 = new SinglyLinkedList.ListNode(2);
            var n0 = new SinglyLinkedList.ListNode(0);
            var nn4 = new SinglyLinkedList.ListNode(-4);
            n3.next = n2;
            n2.next = n0;
            n0.next = nn4;
            assertTrue(!sll.hasCycle(n3));
        }
    }

    @Test
    public void testSort() {
        SinglyLinkedList sll = new SinglyLinkedList();
        {
            assertEquals(sll.insertionSortList(null), null);
        }
        {
            var n1 = new SinglyLinkedList.ListNode(1);
            var n2 = new SinglyLinkedList.ListNode(2);
            var n3 = new SinglyLinkedList.ListNode(3);
            var n4 = new SinglyLinkedList.ListNode(4);
            assertEquals(sll.insertionSortList(n1), n1);
            n1.next = n2;
            assertEquals(sll.insertionSortList(n1), n1);
            n2.next = n3;
            assertEquals(sll.insertionSortList(n1), n1);
            n3.next = n4;
            var r = sll.insertionSortList(n1);
            assertEquals(r, n1);
            assertTrue(sll.isSorted(r));
        }
        {
            var n1 = new SinglyLinkedList.ListNode(1);
            var n2 = new SinglyLinkedList.ListNode(2);
            var n3 = new SinglyLinkedList.ListNode(3);
            var n4 = new SinglyLinkedList.ListNode(4);
            assertEquals(sll.insertionSortList(n1), n1);
            n1.next = null;
            n2.next = n1;
            assertEquals(sll.insertionSortList(n2), n1);
            n1.next = null;
            n2.next = n1;
            n3.next = n2;
            assertEquals(sll.insertionSortList(n3), n1);
            n1.next = null;
            n2.next = n1;
            n3.next = n2;
            n4.next = n3;
            var r = sll.insertionSortList(n4);
            assertEquals(r, n1);
            assertTrue(sll.isSorted(r));

            assertTrue(sll.isSorted(sll.sort(n4)));
            {
                n1.next = null;
                n2.next = n1;
                n3.next = n2;
                n4.next = n3;
                r = sll.mergeSort(n4);
                assertTrue(sll.isSorted(r));
                assertEquals(sll.length(r), 4);
            }
        }
        {
            var n1 = new SinglyLinkedList.ListNode(1);
            var n2 = new SinglyLinkedList.ListNode(2);
            var n3 = new SinglyLinkedList.ListNode(3);
            var n4 = new SinglyLinkedList.ListNode(4);
            n4.next = n2;
            n2.next = n1;
            n1.next = n3;
            var r = sll.insertionSortList(n4);
            assertEquals(r, n1);
            assertTrue(sll.isSorted(r));
            {
                n4.next = n2;
                n2.next = n1;
                n1.next = n3;
                n3.next = null;
                r = sll.mergeSort(n4);
                assertTrue(sll.isSorted(r));
                assertEquals(sll.length(r), 4);
            }
        }
        {
            var n_1 = new SinglyLinkedList.ListNode(-1);
            var n5 = new SinglyLinkedList.ListNode(5);
            var n3 = new SinglyLinkedList.ListNode(3);
            var n4 = new SinglyLinkedList.ListNode(4);
            var n0 = new SinglyLinkedList.ListNode(0);

            {
                n_1.next = n5;
                n5.next = n3;
                n3.next = n4;
                n4.next = n0;
                var r = sll.insertionSortList(n_1);
                assertEquals(r, n_1);
                assertTrue(sll.isSorted(r));
            }
            {
                n_1.next = n5;
                n5.next = n3;
                n3.next = n4;
                n4.next = n0;
                n0.next = null;
                var r = sll.mergeSort(n_1);
                assertTrue(sll.isSorted(r));
                assertEquals(sll.length(r), 5);
            }
        }
    }

    @Test
    public void testReorderList() {
        SinglyLinkedList sll = new SinglyLinkedList();
        var n1 = new SinglyLinkedList.ListNode(1);
        var n2 = new SinglyLinkedList.ListNode(2);
        var n3 = new SinglyLinkedList.ListNode(3);
        var n4 = new SinglyLinkedList.ListNode(4);
        {
            n1.next = n2;
            n2.next = n3;
            n3.next = n4;
            sll.reorderList(n1);
            assertTrue(sll.length(n1) == 4 && n1.next.val == 4 && n1.next.next.val == 2 && n1.next.next.next.val == 3);
        }
        var n5 = new SinglyLinkedList.ListNode(5);
        {
            n1.next = n2;
            n2.next = n3;
            n3.next = n4;
            n4.next = n5;
            sll.reorderList(n1);
            assertTrue(sll.length(n1) == 5 && n1.next.val == 5 && n1.next.next.val == 2 && n1.next.next.next.val == 4
                    && n1.next.next.next.next.val == 3);
        }
    }

    @Test
    public void testRotateRight() {
        SinglyLinkedList sll = new SinglyLinkedList();
        var n1 = new SinglyLinkedList.ListNode(1);
        var n2 = new SinglyLinkedList.ListNode(2);
        var n3 = new SinglyLinkedList.ListNode(3);
        var n4 = new SinglyLinkedList.ListNode(4);
        var n5 = new SinglyLinkedList.ListNode(5);
        {
            n1.next = n2;
            n2.next = n3;
            n3.next = n4;
            n4.next = n5;
            n5.next = null;
            var r = sll.rotateRight(n1, 1);
            assertEquals(r, n5);
        }
        {
            n1.next = n2;
            n2.next = n3;
            n3.next = n4;
            n4.next = n5;
            n5.next = null;
            var r = sll.rotateRight(n1, 2);
            assertEquals(r, n4);
        }
        {
            n1.next = n2;
            n2.next = n3;
            n3.next = n4;
            n4.next = n5;
            n5.next = null;
            var r = sll.rotateRight(n1, 3);
            assertEquals(r, n3);
        }
        {
            n1.next = n2;
            n2.next = n3;
            n3.next = n4;
            n4.next = n5;
            n5.next = null;
            var r = sll.rotateRight(n1, 4);
            assertEquals(r, n2);
        }
        {
            n1.next = n2;
            n2.next = n3;
            n3.next = n4;
            n4.next = n5;
            n5.next = null;
            var r = sll.rotateRight(n1, 5);
            assertEquals(r, n1);
        }
        {
            n1.next = n2;
            n2.next = n3;
            n3.next = n4;
            n4.next = n5;
            n5.next = null;
            var r = sll.rotateRight(n1, 6);
            assertEquals(r, n5);
        }
    }

    @Test
    public void testPartition() {
        SinglyLinkedList sll = new SinglyLinkedList();
        var n1 = new SinglyLinkedList.ListNode(1);
        var n2i = new SinglyLinkedList.ListNode(2);
        var n2ii = new SinglyLinkedList.ListNode(2);
        var n3 = new SinglyLinkedList.ListNode(3);
        var n4 = new SinglyLinkedList.ListNode(4);
        var n5 = new SinglyLinkedList.ListNode(5);

        {
            n1.next = n4;
            n4.next = n3;
            n3.next = n2i;
            n2i.next = n5;
            n5.next = n2ii;
            n2ii.next = null;
            var r = sll.partition(n1, 3);
            assertTrue(r.val == 1 && r.next.val == 2 && r.next.next.val == 2 && r.next.next.next.val == 4
                    && r.next.next.next.next.val == 3 && r.next.next.next.next.next.val == 5
                    && r.next.next.next.next.next.next == null);
        }
        {
            n1.next = n4;
            n4.next = n3;
            n3.next = n2i;
            n2i.next = n5;
            n5.next = n2ii;
            n2ii.next = null;
            var r = sll.partition(n1, 2);
            assertTrue(r.val == 1 && r.next.val == 4 && r.next.next.val == 3 && r.next.next.next.val == 2
                    && r.next.next.next.next.val == 5 && r.next.next.next.next.next.val == 2
                    && r.next.next.next.next.next.next == null);
        }
        {
            n1.next = n4;
            n4.next = n3;
            n3.next = n2i;
            n2i.next = n5;
            n5.next = n2ii;
            n2ii.next = null;
            var r = sll.partition(n1, 1);
            assertTrue(r.val == 1 && r.next.val == 4 && r.next.next.val == 3 && r.next.next.next.val == 2
                    && r.next.next.next.next.val == 5 && r.next.next.next.next.next.val == 2
                    && r.next.next.next.next.next.next == null);
        }
        {
            n1.next = n4;
            n4.next = n3;
            n3.next = n2i;
            n2i.next = n5;
            n5.next = n2ii;
            n2ii.next = null;
            var r = sll.partition(n1, 6);
            assertTrue(r.val == 1 && r.next.val == 4 && r.next.next.val == 3 && r.next.next.next.val == 2
                    && r.next.next.next.next.val == 5 && r.next.next.next.next.next.val == 2
                    && r.next.next.next.next.next.next == null);
        }
    }

    private int[] goThrough(SinglyLinkedList.ListNode node, int n) {
        int[] result = new int[n];
        int c = 0;
        for (var i = node; i != null; i = i.next) {
            result[c++] = i.val;
        }
        assertEquals(c, n);
        return result;
    }

    private void reverseBetween(int[] inout, int m, int n) {
        --m;
        --n;
        while (m < n) {
            int v = inout[m];
            inout[m] = inout[n];
            inout[n] = v;
            ++m;
            --n;
        }
    }

    @Test
    public void testReverseBetween() {
        SinglyLinkedList sll = new SinglyLinkedList();
        var n1 = new SinglyLinkedList.ListNode(1);
        var n2 = new SinglyLinkedList.ListNode(2);
        var n3 = new SinglyLinkedList.ListNode(3);
        var n4 = new SinglyLinkedList.ListNode(4);
        var n5 = new SinglyLinkedList.ListNode(5);
        int limit = 5;

        for (int distance = 0; distance < limit; ++distance) {
            int m = 1, n = m + distance;
            while (n <= limit) {
                n1.next = n2;
                n2.next = n3;
                n3.next = n4;
                n4.next = n5;
                n5.next = null;
                var r = sll.reverseBetween(n1, m, n);
                var result = goThrough(r, limit);
                int[] expection = { 1, 2, 3, 4, 5 };
                reverseBetween(expection, m, n);

                if (java.util.Arrays.compare(result, expection) != 0) {
                    System.out.printf("m: %d, n: %d%n", m, n);
                    assertEquals(result, expection);
                }
                ++m;
                ++n;
            }
        }
    }

    @Test
    public void testDeleteDuplicates2() {
        SinglyLinkedList sll = new SinglyLinkedList();
        {
            var n1 = new SinglyLinkedList.ListNode(1);
            var n2 = new SinglyLinkedList.ListNode(2);
            var n3_1 = new SinglyLinkedList.ListNode(3);
            var n3_2 = new SinglyLinkedList.ListNode(3);
            var n4_1 = new SinglyLinkedList.ListNode(4);
            var n4_2 = new SinglyLinkedList.ListNode(4);
            var n5_1 = new SinglyLinkedList.ListNode(5);
            var n5_2 = new SinglyLinkedList.ListNode(5);

            {
                n1.next = n2;
                n2.next = n3_1;
                n3_1.next = n3_2;
                n3_2.next = n4_1;
                n4_1.next = n4_2;
                n4_2.next = n5_1;
                var r = sll.deleteDuplicates2(n1);
                var result = goThrough(r, 3);
                int[] expection = { 1, 2, 5 };
                assertEquals(result, expection);
            }
            {
                n1.next = n2;
                n2.next = n3_1;
                n3_1.next = n3_2;
                n3_2.next = n4_1;
                n4_1.next = n4_2;
                n4_2.next = n5_1;
                n5_1.next = n5_2;
                n5_2.next = null;
                var r = sll.deleteDuplicates2(n1);
                var result = goThrough(r, 2);
                int[] expection = { 1, 2 };
                assertEquals(result, expection);
            }
            {
                var n1_2 = new SinglyLinkedList.ListNode(1);
                n1_2.next = n1;
                n1.next = n2;
                n2.next = n3_1;
                n3_1.next = n3_2;
                n3_2.next = n4_1;
                n4_1.next = n4_2;
                n4_2.next = n5_1;
                n5_1.next = n5_2;
                n5_2.next = null;
                var r = sll.deleteDuplicates2(n1_2);
                var result = goThrough(r, 1);
                int[] expection = { 2 };
                assertEquals(result, expection);
            }
            {
                var n1_2 = new SinglyLinkedList.ListNode(1);
                n1_2.next = n1;
                n1.next = n2;
                n2.next = n3_1;
                n3_1.next = n4_1;
                n4_1.next = n4_2;
                n4_2.next = n5_1;
                n5_1.next = n5_2;
                n5_2.next = null;
                var r = sll.deleteDuplicates2(n1_2);
                var result = goThrough(r, 2);
                int[] expection = { 2, 3 };
                assertEquals(result, expection);
            }
            {
                var n1_2 = new SinglyLinkedList.ListNode(1);
                n1_2.next = n1;
                n1.next = null;
                var r = sll.deleteDuplicates2(n1_2);
                assertEquals(r, null);
            }
        }
    }

    @Test
    public void testDetectCycle() {
        SinglyLinkedList sll = new SinglyLinkedList();
        {
            var n3 = new SinglyLinkedList.ListNode(3);
            var n2 = new SinglyLinkedList.ListNode(2);
            var n0 = new SinglyLinkedList.ListNode(0);
            var n4 = new SinglyLinkedList.ListNode(4);
            n3.next = n2;
            n2.next = n0;
            n0.next = n4;
            n4.next = n2;

            var r = sll.detectCycle(n3);
            assertEquals(r, n2);
        }
        {
            var n1 = new SinglyLinkedList.ListNode(1);
            var n2 = new SinglyLinkedList.ListNode(2);
            n1.next = n2;
            n2.next = n1;

            var r = sll.detectCycle(n1);
            assertEquals(r, n1);
        }
        {
            var n3 = new SinglyLinkedList.ListNode(3);
            var n2 = new SinglyLinkedList.ListNode(2);
            var n0 = new SinglyLinkedList.ListNode(0);
            var n4 = new SinglyLinkedList.ListNode(4);
            n3.next = n2;
            n2.next = n0;
            n0.next = n4;

            var r = sll.detectCycle(n3);
            assertEquals(r, null);
        }
    }

    @Test
    public void testRemoveElements() {
        SinglyLinkedList sll = new SinglyLinkedList();
        {
            var n1 = new SinglyLinkedList.ListNode(1);
            var n2 = new SinglyLinkedList.ListNode(2);
            var n3 = new SinglyLinkedList.ListNode(3);
            var n4 = new SinglyLinkedList.ListNode(4);
            var n5 = new SinglyLinkedList.ListNode(5);
            var n6_1 = new SinglyLinkedList.ListNode(6);
            var n6_2 = new SinglyLinkedList.ListNode(6);
            var n6_3 = new SinglyLinkedList.ListNode(6);
            var n6_4 = new SinglyLinkedList.ListNode(6);

            n6_1.next = n1;
            n1.next = n2;
            n2.next = n6_2;
            n6_2.next = n3;
            n3.next = n4;
            n4.next = n6_3;
            n6_3.next = n5;
            n5.next = n6_4;
            n6_4.next = null;

            var r = sll.removeElements(n6_1, 6);
            assertEquals(r, n1);
            assertEquals(r.next, n2);
            assertEquals(r.next.next, n3);
            assertEquals(r.next.next.next, n4);
            assertEquals(r.next.next.next.next, n5);
            assertEquals(r.next.next.next.next.next, null);
        }
    }
}
