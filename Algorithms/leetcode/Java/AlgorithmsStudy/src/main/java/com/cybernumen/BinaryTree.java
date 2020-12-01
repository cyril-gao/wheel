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

    public boolean hasPathSum(TreeNode root, int sum) {
        if (root != null) {
            if (root.left == null && root.right == null && root.val == sum) {
                return true;
            }

            int remains = sum - root.val;
            if (hasPathSum(root.left, remains) || hasPathSum(root.right, remains)) {
                return true;
            }
        }
        return false;
    }

    private boolean isSymmetric(TreeNode left, TreeNode right) {
        if (left == null && right == null) {
            return true;
        }
        if (left != null && right != null) {
            if (left.val == right.val) {
                if (isSymmetric(left.left, right.right) && isSymmetric(left.right, right.left)) {
                    return true;
                }
            }
        }
        return false;
    }

    public boolean isSymmetric(TreeNode root) {
        if (root != null) {
            return isSymmetric(root.left, root.right);
        }
        return true;
    }

    public List<List<Integer>> zigzagLevelOrder(TreeNode root) {
        List<List<Integer>> retval = new LinkedList<>();
        if (root != null) {
            List<TreeNode> current = new LinkedList<>();
            current.add(root);
            boolean left = true;
            while (!current.isEmpty()) {
                List<Integer> row = new LinkedList<>();
                for (TreeNode i : current) {
                    row.add(i.val);
                }

                left = !left;
                List<TreeNode> next = new LinkedList<>();
                for (int i = current.size() - 1; i >= 0; --i) {
                    TreeNode t = current.get(i);
                    if (left) {
                        if (t.left != null) {
                            next.add(t.left);
                        }
                    } else {
                        if (t.right != null) {
                            next.add(t.right);
                        }
                    }
                    if (left) {
                        if (t.right != null) {
                            next.add(t.right);
                        }
                    } else {
                        if (t.left != null) {
                            next.add(t.left);
                        }
                    }
                }
                retval.add(row);
                current = next;
            }
        }
        return retval;
    }

    public void inorderTraversalRecursively(TreeNode root, List<Integer> output) {
        if (root != null) {
            inorderTraversalRecursively(root.left, output);
            output.add(root.val);
            inorderTraversalRecursively(root.right, output);
        }
    }

    public List<Integer> inorderTraversal(TreeNode root) {
        List<Integer> retval = new LinkedList<>();
        if (root != null) {
            Stack<TreeNode> stack = new Stack<>();
            for (TreeNode p = root; p != null || !stack.isEmpty();) {
                while (p != null) {
                    stack.push(p);
                    p = p.left;
                }
                p = stack.pop();
                retval.add(p.val);
                p = p.right;
            }
        }
        return retval;
    }

    private static class BstInternal {
        boolean valid;
        boolean exist;
        int minValue;
        int maxValue;

        public BstInternal(boolean v, boolean e, int i, int a) {
            valid = v;
            exist = e;
            minValue = i;
            maxValue = a;
        }

        public BstInternal() {
            this(true, false, 0, 0);
        }
    }

    private static BstInternal getBstInternal(TreeNode root) {
        BstInternal retval = new BstInternal();
        if (root != null) {
            retval.valid = false;
            if ((root.left == null || root.left.val < root.val) && (root.right == null || root.right.val > root.val)) {
                BstInternal lr = getBstInternal(root.left);
                BstInternal rr = getBstInternal(root.right);
                if (lr.valid && rr.valid) {
                    if ((!lr.exist || (lr.minValue <= lr.maxValue && lr.maxValue < root.val))
                            && (!rr.exist || (rr.minValue <= rr.maxValue && rr.minValue > root.val))) {
                        retval.valid = true;
                        retval.exist = true;
                        if (rr.exist) {
                            retval.maxValue = rr.maxValue;
                        } else {
                            retval.maxValue = root.val;
                        }
                        if (lr.exist) {
                            retval.minValue = lr.minValue;
                        } else {
                            retval.minValue = root.val;
                        }
                    }
                }
            }
        }
        return retval;
    }

    public boolean isValidBST(TreeNode root) {
        BstInternal bi = getBstInternal(root);
        return bi.valid;
    }
}
