import { TreeNode } from './tree.node';

/*
Given the root of a binary tree, determine if it is a valid binary search tree (BST).

A valid BST is defined as follows:
    1. The left subtree of a node contains only nodes with keys less than the node's key.
    2. The right subtree of a node contains only nodes with keys greater than the node's key.
    3. Both the left and right subtrees must also be binary search trees.
*/

class State {
    constructor(
        public readonly smallest: number,
        public readonly biggest: number,
        public readonly valid: boolean
    ) {}
}

function getState(root: TreeNode): State {
    let smallest = root.val;
    let biggest = root.val;
    let valid = true;

    if (root.left !== null) {
        let s = getState(root.left);
        smallest = s.smallest;
        if (!s.valid || s.smallest > s.biggest || s.biggest >= root.val) {
            valid = false;
        }
    }
    if (valid) {
        if (root.right !== null) {
            let s = getState(root.right);
            biggest = s.biggest;
            if (!s.valid || s.smallest > s.biggest || s.smallest <= root.val) {
                valid = false;
            }
        }
    }

    return new State(smallest, biggest, valid);
}

export function isValidBST(root: TreeNode | null): boolean {
    let retval = true;
    if (root !== null) {
        let s = getState(root);
        retval = s.valid;
    }
    return retval;
}
