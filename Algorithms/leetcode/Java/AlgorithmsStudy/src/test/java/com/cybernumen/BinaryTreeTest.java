package com.cybernumen;

import java.util.*;

import static org.testng.Assert.assertEquals;
import org.testng.annotations.*;

public class BinaryTreeTest {
    @Test
    public void testPreorderTraversal() {
        BinaryTree bt = new BinaryTree();
        {
            var n1 = new BinaryTree.TreeNode(1);
            var n2 = new BinaryTree.TreeNode(2);
            var n3 = new BinaryTree.TreeNode(3);
            var n4 = new BinaryTree.TreeNode(4);
            var n5 = new BinaryTree.TreeNode(5);
            var n6 = new BinaryTree.TreeNode(6);
            var n7 = new BinaryTree.TreeNode(7);
            var n8 = new BinaryTree.TreeNode(8);
            var n9 = new BinaryTree.TreeNode(9);
            var n10 = new BinaryTree.TreeNode(10);
            var n11 = new BinaryTree.TreeNode(11);
            var n12 = new BinaryTree.TreeNode(12);
            var n13 = new BinaryTree.TreeNode(13);
            var n14 = new BinaryTree.TreeNode(14);
            var n15 = new BinaryTree.TreeNode(15);
            var n16 = new BinaryTree.TreeNode(16);
            var n17 = new BinaryTree.TreeNode(17);
            var n18 = new BinaryTree.TreeNode(18);
            n1.left = n2;
            n1.right = n3;
            n2.left = n4;
            n2.right = n5;
            n3.right = n6;
            n4.right = n7;
            n5.right = n8;
            n6.left = n9;
            n6.right = n10;
            n7.left = n11;
            n7.right = n12;
            n8.right = n13;
            n9.left = n14;
            n10.right = n15;
            n11.left = n16;
            n13.left = n17;
            n15.left = n18;

            List<Integer> r1 = new LinkedList<>();
            bt.preorderTraversalRecursively(n1, r1);
            var r2 = bt.preorderTraversal(n1);
            assertEquals(r1, r2);
        }
    }
}
