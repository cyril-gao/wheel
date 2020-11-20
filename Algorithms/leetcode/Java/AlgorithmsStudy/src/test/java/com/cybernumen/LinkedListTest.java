package com.cybernumen;

import static org.testng.Assert.assertTrue;
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
}
