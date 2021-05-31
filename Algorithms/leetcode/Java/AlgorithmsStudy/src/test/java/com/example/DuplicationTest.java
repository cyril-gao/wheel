package com.example;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertNull;
import org.testng.annotations.*;

public class DuplicationTest {
    @Test
    public void testGraphDuplication() {
        var n1 = new Duplication.Node<Integer>(1);
        var n2 = new Duplication.Node<Integer>(2);
        var n3 = new Duplication.Node<Integer>(3);
        var n4 = new Duplication.Node<Integer>(4);
        
        n1.neighbors.add(n2);
        n1.neighbors.add(n4);

        n2.neighbors.add(n1);
        n2.neighbors.add(n3);

        n3.neighbors.add(n2);
        n3.neighbors.add(n4);

        n4.neighbors.add(n1);
        n4.neighbors.add(n3);

        var clone = Duplication.copy(n1);
        assertEquals(clone.value, Integer.valueOf(1));
        assertEquals(clone.neighbors.size(), 2);
        n2 = clone.neighbors.get(0);
        n4 = clone.neighbors.get(1);
        assertEquals(n2.value, Integer.valueOf(2));
        assertEquals(n4.value, Integer.valueOf(4));

        assertEquals(n2.neighbors.size(), 2);
        n1 = n2.neighbors.get(0);
        n3 = n2.neighbors.get(1);
        assertEquals(n1.value, Integer.valueOf(1));
        assertEquals(n3.value, Integer.valueOf(3));

        assertEquals(n3.neighbors.size(), 2);
        n2 = n3.neighbors.get(0);
        n4 = n3.neighbors.get(1);
        assertEquals(n2.value, Integer.valueOf(2));
        assertEquals(n4.value, Integer.valueOf(4));

        assertEquals(n4.neighbors.size(), 2);
        n1 = n4.neighbors.get(0);
        n3 = n4.neighbors.get(1);
        assertEquals(n1.value, Integer.valueOf(1));
        assertEquals(n3.value, Integer.valueOf(3));
    }

    @Test
    public void testNodeWithRandomNeighborDuplication() {
        var n1 = new Duplication.NodeWithRandomNeighbor<Integer>(1);
        var n2 = new Duplication.NodeWithRandomNeighbor<Integer>(2);
        var n3 = new Duplication.NodeWithRandomNeighbor<Integer>(3);
        var n4 = new Duplication.NodeWithRandomNeighbor<Integer>(4);
        var n5 = new Duplication.NodeWithRandomNeighbor<Integer>(5);

        n1.next = n2;
        n2.next = n3;
        n3.next = n4;
        n4.next = n5;
        n1.random = null;
        n2.random = n1;
        n3.random = n5;
        n4.random = n3;
        n5.random = n1;

        var result = Duplication.copy(n1);
        assertEquals(result.value, Integer.valueOf(1));
        assertNull(result.random);

        assertEquals(result.next.value, Integer.valueOf(2));
        assertEquals(result.next.random, result);

        assertEquals(result.next.next.value, Integer.valueOf(3));
        assertEquals(result.next.next.random, result.next.next.next.next);

        assertEquals(result.next.next.next.value, Integer.valueOf(4));
        assertEquals(result.next.next.next.random, result.next.next);

        assertEquals(result.next.next.next.next.value, Integer.valueOf(5));
        assertEquals(result.next.next.next.next.random, result);

        assertNull(result.next.next.next.next.next);
    }
}
