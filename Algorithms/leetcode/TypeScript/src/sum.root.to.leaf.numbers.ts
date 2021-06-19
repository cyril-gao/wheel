import { TreeNode } from './tree.node';

/*
You are given the root of a binary tree containing digits from 0 to 9 only.

Each root-to-leaf path in the tree represents a number.

For example, the root-to-leaf path 1 -> 2 -> 3 represents the number 123.

Return the total sum of all root-to-leaf numbers. Test cases are generated so that the answer will fit in a 32-bit integer.

A leaf node is a node with no children.
*/

function numbers(root: TreeNode): string[] {
    let retval = [];
    if (root.left !== null || root.right !== null) {
        if (root.left !== null) {
            for (let v of numbers(root.left)) {
                retval.push(root.val.toString() + v);
            }
        }
        if (root.right !== null) {
            for (let v of numbers(root.right)) {
                retval.push(root.val.toString() + v);
            }
        }
    } else {
        retval.push(root.val.toString());
    }
    return retval;
}

export function sumNumbers(root: TreeNode | null): number {
    let retval = 0;
    if (root !== null) {
        for (let str of numbers(root)) {
            retval += parseInt(str);
        }
    }
    return retval;
}
