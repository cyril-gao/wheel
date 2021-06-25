import { TreeNode } from "./tree.node";

/*
Given two integer arrays inorder and postorder where inorder is
the inorder traversal of a binary tree and postorder is the postorder
traversal of the same tree, construct and return the binary tree.
*/

function indexOf<T>(input: T[], begin: number, end: number, target: T): number {
    let retval = end;
    for (let i = begin; i != end; ++i) {
        if (input[i] === target) {
            retval = i;
            break;
        }
    }
    return retval;
}

function rebuildTree(
    inorder: number[], b1: number, e1: number,
    postorder: number[], b2: number, e2: number
): TreeNode | null {
    let retval = null;
    if (b1 < e1) {
        --e2;
        let val = postorder[e2];
        let m1 = indexOf(inorder, b1, e1, val);
        retval = new TreeNode(val);
        let m2 = b2 + m1 - b1;
        retval.left = rebuildTree(inorder, b1, m1, postorder, b2, m2);
        retval.right = rebuildTree(inorder, m1 + 1, e1, postorder, m2, e2);
    }
    return retval;
}

export function buildTree(inorder: number[], postorder: number[]): TreeNode | null {
    let retval = null;
    if (inorder.length === postorder.length && inorder.length > 0) {
        retval = rebuildTree(inorder, 0, inorder.length, postorder, 0, postorder.length);
    }
    return retval;
}
