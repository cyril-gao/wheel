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
    public void testInsertion() {
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
        }
        {
            var n_1 = new SinglyLinkedList.ListNode(-1);
            var n5 = new SinglyLinkedList.ListNode(5);
            var n3 = new SinglyLinkedList.ListNode(3);
            var n4 = new SinglyLinkedList.ListNode(4);
            var n0 = new SinglyLinkedList.ListNode(0);

            n_1.next = n5;
            n5.next = n3;
            n3.next = n4;
            n4.next = n0;
            var r = sll.insertionSortList(n_1);
            assertEquals(r, n_1);
            assertTrue(sll.isSorted(r));
        }
    }
}
