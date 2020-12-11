package com.cybernumen;

import java.util.*;

import javax.swing.tree.TreeNode;

import static org.testng.Assert.assertEquals;
import static org.testng.Assert.assertTrue;
import static org.testng.Assert.assertFalse;
import org.testng.annotations.*;

public class BinaryTreeTest {
    @Test
    public void testTraversal() {
        BinaryTree bt = new BinaryTree();

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
        {
            List<Integer> r1 = new LinkedList<>();
            bt.preorderTraversalRecursively(n1, r1);
            var r2 = bt.preorderTraversal(n1);
            assertEquals(r1, r2);
        }
        {
            List<Integer> r1 = new LinkedList<>();
            bt.inorderTraversalRecursively(n1, r1);
            var r2 = bt.inorderTraversal(n1);
            assertEquals(r1, r2);
        }
        {
            List<Integer> r1 = new LinkedList<>();
            bt.postorderTraversalRecursively(n1, r1);
            var r2 = bt.postorderTraversal(n1);
            assertEquals(r1, r2);
        }
    }

    @Test
    public void testHasPathSum() {
        BinaryTree bt = new BinaryTree();
        {
            var n5 = new BinaryTree.TreeNode(5);
            var n4 = new BinaryTree.TreeNode(4);
            var n8 = new BinaryTree.TreeNode(8);
            var n11 = new BinaryTree.TreeNode(11);
            var n13 = new BinaryTree.TreeNode(13);
            var n4_2 = new BinaryTree.TreeNode(4);
            var n7 = new BinaryTree.TreeNode(7);
            var n2 = new BinaryTree.TreeNode(2);
            var n1 = new BinaryTree.TreeNode(1);
            n5.left = n4;
            n5.right = n8;
            n4.left = n11;
            n8.left = n13;
            n8.right = n4_2;
            n11.left = n7;
            n11.right = n2;
            n4.right = n1;
            assertTrue(bt.hasPathSum(n5, 22));
        }
    }

    @Test
    public void testIsValidBST() {
        BinaryTree bt = new BinaryTree();
        {
            var n3 = new BinaryTree.TreeNode(3);
            var n2 = new BinaryTree.TreeNode(2);
            var n1 = new BinaryTree.TreeNode(1);
            n2.left = n1;
            assertTrue(bt.isValidBST(n2));
            n2.right = n3;
            assertTrue(bt.isValidBST(n2));
            n2.right = null;
            n1.right = n3;
            assertFalse(bt.isValidBST(n2));
        }
        {
            var n1 = new BinaryTree.TreeNode(1);
            var n3 = new BinaryTree.TreeNode(3);
            var n4 = new BinaryTree.TreeNode(4);
            var n5 = new BinaryTree.TreeNode(5);
            var n6 = new BinaryTree.TreeNode(6);
            n5.left = n1;
            n5.right = n4;
            n4.left = n3;
            n4.right = n6;
            assertFalse(bt.isValidBST(n5));
            assertTrue(bt.isValidBST(n4));
        }
        {
            var n5 = new BinaryTree.TreeNode(5);
            var n6 = new BinaryTree.TreeNode(6);
            var n10 = new BinaryTree.TreeNode(10);
            var n15 = new BinaryTree.TreeNode(15);
            var n20 = new BinaryTree.TreeNode(20);
            n10.left = n5;
            n10.right = n15;
            n15.left = n6;
            n15.right = n20;

            assertFalse(bt.isValidBST(n10));
            assertTrue(bt.isValidBST(n15));
        }
    }

    @Test
    public void testMinDepth() {
        BinaryTree bt = new BinaryTree();
        {
            var n3 = new BinaryTree.TreeNode(3);
            var n9 = new BinaryTree.TreeNode(9);
            var n20 = new BinaryTree.TreeNode(20);
            var n15 = new BinaryTree.TreeNode(15);
            var n7 = new BinaryTree.TreeNode(7);
            n3.left = n9;
            n3.right = n20;
            n20.left = n15;
            n20.right = n7;
            assertEquals(bt.minDepth(n3), 2);
        }
        {
            var n1 = new BinaryTree.TreeNode(1);
            var n2 = new BinaryTree.TreeNode(2);
            var n3 = new BinaryTree.TreeNode(3);
            var n4 = new BinaryTree.TreeNode(4);
            var n5 = new BinaryTree.TreeNode(5);
            var n6 = new BinaryTree.TreeNode(6);
            n1.right = n2;
            n2.right = n3;
            n3.right = n4;
            n4.right = n5;
            n5.right = n6;
            assertEquals(bt.minDepth(n1), 6);
        }
    }

    private void printTree(BinaryTree.TreeNode root) {
        assert (root != null);
        List<List<String>> result = new LinkedList<>();
        List<BinaryTree.TreeNode> current = new LinkedList<>();
        {
            current.add(root);
            List<String> line = new LinkedList<>();
            line.add(Integer.valueOf(root.val).toString());
            result.add(line);
        }
        while (!current.isEmpty()) {
            List<String> line = new LinkedList<>();
            List<BinaryTree.TreeNode> next = new LinkedList<>();
            for (var t : current) {
                if (t.left != null) {
                    next.add(t.left);
                    line.add(Integer.valueOf(t.left.val).toString());
                } else {
                    line.add("null");
                }
                if (t.right != null) {
                    next.add(t.right);
                    line.add(Integer.valueOf(t.right.val).toString());
                } else {
                    line.add("null");
                }
            }
            if (!next.isEmpty()) {
                result.add(line);
            }
            current = next;
        }
        System.out.println(result);
    }

    @Test
    public void testGenerateTrees() {
        BinaryTree bt = new BinaryTree();
        for (int n = 1; n < 9; ++n) {
            int l = bt.numTrees(n);
            // System.out.println(l);
            var r = bt.generateTrees(n);
            /*
             * for (var t : r) { printTree(t); } System.out.println("\n\n");
             */
            assertEquals(l, r.size());
        }
    }

    @Test
    public void testLowestCommonAncestor() {
        BinaryTree bt = new BinaryTree();
        {
            var n0 = new BinaryTree.TreeNode(10);
            var n1 = new BinaryTree.TreeNode(1);
            var n2 = new BinaryTree.TreeNode(2);
            var n3 = new BinaryTree.TreeNode(3);
            var n4 = new BinaryTree.TreeNode(4);
            var n5 = new BinaryTree.TreeNode(5);
            var n6 = new BinaryTree.TreeNode(6);
            var n7 = new BinaryTree.TreeNode(7);
            var n8 = new BinaryTree.TreeNode(8);

            n3.left = n5;
            n3.right = n1;
            n5.left = n6;
            n5.right = n2;
            n1.left = n0;
            n1.right = n8;
            n2.left = n7;
            n2.right = n4;

            var root = n3;
            assertEquals(bt.lowestCommonAncestor(root, n6, n7), n5);
            assertEquals(bt.lowestCommonAncestor(root, n4, n0), n3);
            assertEquals(bt.lowestCommonAncestor(root, n5, n7), n5);
            assertEquals(bt.lowestCommonAncestor(root, n8, n7), n3);
        }
    }
}
