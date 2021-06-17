import { TreeNode } from './tree.node';

/*
Given the root of a binary tree, flatten the tree into a "linked list":
    1. The "linked list" should use the same TreeNode class where the right child pointer points to the next node in the list and the left child pointer is always null.
    2. The "linked list" should be in the same order as a pre-order traversal of the binary tree.
*/

export function flatten(root: TreeNode | null): void {
    /*
    let retval = null;
    let previous = null;
    let sequence = [];
    let stack = [];
    for (let p = root; p !== null || stack.length > 0;) {
        while (p !== null) {
            sequence.push(p);
            stack.push(p);
            p = p.left;
        }
        p = stack.pop();
        p = p.right;
    }
    for (let i = 0, ie = sequence.length - 1; i < ie; ++i) {
        sequence[i].left = null;
        sequence[i].right = sequence[i + 1];
    }
    if (sequence.length > 0) {
        sequence[sequence.length - 1].left = null;
        sequence[sequence.length - 1].right = null;
    }
    */
    let previous = null;
    let stack = [];
    for (let p = root; p !== null || stack.length > 0;) {
        while (p !== null) {
            if (previous !== null) {
                previous.left = p;
            }
            previous = p;
            stack.push(p);
            p = p.left;
        }
        p = stack.pop();
        p = p.right;
    }
    if (previous !== null) {
        previous.left = null;
        previous.right = null;
    }
    for (let p = root; p !== null;) {
        let next = p.left;
        p.left = null;
        p.right = next;
        p = next;
    }
}
