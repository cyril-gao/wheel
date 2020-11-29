package com.cybernumen;

import java.util.*;

public class BinaryTree {
    public static class TreeNode {
        int val;
        TreeNode left;
        TreeNode right;

        TreeNode() {
        }

        TreeNode(int val) {
            this.val = val;
        }

        TreeNode(int val, TreeNode left, TreeNode right) {
            this.val = val;
            this.left = left;
            this.right = right;
        }
    }

    private static class Internal {
        int height;
        boolean valid;

        public Internal(int h, boolean v) {
            height = h;
            valid = v;
        }

        public Internal() {
            this(0, true);
        }
    }

    private static Internal getInternal(TreeNode root) {
        Internal retval = new Internal();
        if (root != null) {
            Internal lr = getInternal(root.left);
            Internal rr = getInternal(root.right);
            retval.valid = false;
            if (lr.valid && rr.valid && Math.abs(lr.height - rr.height) <= 1) {
                retval.valid = true;
                retval.height = 1 + Math.max(lr.height, rr.height);
            }
        }
        return retval;
    }

    public boolean isBalanced(TreeNode root) {
        Internal result = getInternal(root);
        return result.valid;
    }

    public List<List<Integer>> levelOrder(TreeNode root) {
        List<List<Integer>> retval = new LinkedList<>();
        if (root != null) {
            List<TreeNode> current = new LinkedList<>();
            current.add(root);
            while (!current.isEmpty()) {
                List<Integer> line = new LinkedList<>();
                List<TreeNode> next = new LinkedList<>();
                for (TreeNode node : current) {
                    line.add(node.val);
                    if (node.left != null) {
                        next.add(node.left);
                    }
                    if (node.right != null) {
                        next.add(node.right);
                    }
                }
                retval.add(line);
                current = next;
            }
        }
        return retval;
    }

    public boolean isSameTree(TreeNode p, TreeNode q) {
        boolean retval = p == q;
        if (!retval) {
            if (p != null && q != null) {
                if (p.val == q.val) {
                    if (isSameTree(p.left, q.left) && isSameTree(p.right, q.right)) {
                        retval = true;
                    }
                }
            }
        }
        return retval;
    }

    public void preorderTraversalRecursively(TreeNode root, List<Integer> output) {
        if (root != null) {
            output.add(root.val);
            preorderTraversalRecursively(root.left, output);
            preorderTraversalRecursively(root.right, output);
        }
    }

    public List<Integer> preorderTraversal(TreeNode root) {
        List<Integer> retval = new LinkedList<>();
        if (root != null) {
            Stack<TreeNode> stack = new Stack<>();
            for (TreeNode p = root; p != null || !stack.isEmpty();) {
                while (p != null) {
                    retval.add(p.val);
                    stack.push(p);
                    p = p.left;
                }
                p = stack.pop();
                p = p.right;
            }
        }
        return retval;
    }
}
