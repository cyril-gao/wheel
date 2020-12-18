package com.example;

import static org.testng.Assert.assertTrue;

import org.testng.annotations.*;

public class PopulatingNextRightPointersInEachNodeTest {
    @Test
    public void testConnect() {
        var pnr = new PopulatingNextRightPointersInEachNode();
        {
            var n1 = new PopulatingNextRightPointersInEachNode.Node(1);
            var n2 = new PopulatingNextRightPointersInEachNode.Node(2);
            var n3 = new PopulatingNextRightPointersInEachNode.Node(3);
            var n4 = new PopulatingNextRightPointersInEachNode.Node(4);
            var n5 = new PopulatingNextRightPointersInEachNode.Node(5);
            var n6 = new PopulatingNextRightPointersInEachNode.Node(6);
            var n7 = new PopulatingNextRightPointersInEachNode.Node(7);
            var n8 = new PopulatingNextRightPointersInEachNode.Node(8);
            var n9 = new PopulatingNextRightPointersInEachNode.Node(9);
            var n10 = new PopulatingNextRightPointersInEachNode.Node(10);
            var n11 = new PopulatingNextRightPointersInEachNode.Node(11);
            var n12 = new PopulatingNextRightPointersInEachNode.Node(12);
            var n13 = new PopulatingNextRightPointersInEachNode.Node(13);

            n1.left = n2;
            n1.right = n3;
            n2.left = n4;
            n3.right = n5;
            n4.right = n6;
            n5.left = n7;
            n6.left = n8;
            n6.right = n9;
            n7.right = n10;
            n9.left = n11;
            n10.left = n12;
            n10.right = n13;

            var root = pnr.connect(n1);
            assertTrue(root == n1);
            assertTrue(n1.next == null);
            assertTrue(n2.next == n3 && n3.next == null);
            assertTrue(n4.next == n5 && n5.next == null);
            assertTrue(n6.next == n7 && n7.next == null);
            assertTrue(n8.next == n9 && n9.next == n10 && n10.next == null);
            assertTrue(n11.next == n12 && n12.next == n13 && n13.next == null);
        }
    }
}
