export class TreeNode {
    val: number
    left: TreeNode | null
    right: TreeNode | null
    constructor(val?: number, left?: TreeNode | null, right?: TreeNode | null) {
        this.val = (val === undefined ? 0 : val)
        this.left = (left === undefined ? null : left)
        this.right = (right === undefined ? null : right)
    }
}

/*
Given a non-empty binary tree, find the maximum path sum.

For this problem, a path is defined as any node sequence from some starting node to any node in the tree along the parent-child connections. The path must contain at least one node and does not need to go through the root.

Example 1:
Input: root = [1,2,3]
Output: 6

Example 2:
Input: root = [-10,9,20,null,null,15,7]
Output: 42
*/

function getInternal(root: TreeNode): number[] {
    if (root.left == null && root.right == null) {
        return [root.val, root.val];
    } else {
        let leftResult = [0, 0];
        let leftResultRetrieved = false;
        if (root.left !== null) {
            leftResult = getInternal(root.left);
            leftResultRetrieved = true;
        }
        let rightResult = [0, 0];
        let rightResultRetrieved = false;
        if (root.right !== null) {
            rightResult = getInternal(root.right);
            rightResultRetrieved = true;
        }
        let maxPath = root.val;
        let maxSum = maxPath;
        if (leftResultRetrieved) {
            maxPath = Math.max(maxPath, leftResult[1] + root.val);
            maxSum = Math.max(leftResult[0], maxPath);
        }
        if (rightResultRetrieved) {
            maxPath = Math.max(maxPath, rightResult[1] + root.val);
            maxSum = Math.max(rightResult[0], maxPath, maxSum);
        }
        if (leftResultRetrieved && rightResultRetrieved) {
            maxSum = Math.max(maxSum, leftResult[1] + root.val + rightResult[1]);
        }
        return [maxSum, maxPath];
    }
}

export function maxPathSum(root: TreeNode | null): number {
    let retval = Number.MIN_VALUE;
    if (root != null) {
        let result = getInternal(root);
        retval = result[0];
    }
    return retval;
};
