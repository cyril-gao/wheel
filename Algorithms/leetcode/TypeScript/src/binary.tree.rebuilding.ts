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

export class ListNode {
    val: number;
    next: ListNode | null;
    constructor(val?: number, next?: ListNode | null) {
        this.val = (val === undefined ? 0 : val);
        this.next = (next === undefined ? null : next);
    }
}

/*
Given the head of a singly linked list where elements are sorted in ascending order,
convert it to a height balanced BST.

For this problem, a height-balanced binary tree is defined as a binary tree in which
the depth of the two subtrees of every node never differ by more than 1.
*/

function getNode(head: ListNode, index: number): ListNode {
    let retval = head;
    while (index > 0) {
        retval = retval.next;
        --index;
    }
    return retval;
}

function length(head: ListNode | null): number {
    let retval = 0;
    for (let i = head; i !== null; i = i.next) {
        ++retval;
    }
    return retval;
}

function buildBST(head: ListNode | null, length: number): TreeNode | null {
    let retval: TreeNode = null;
    if (length > 1) {
        let n = Math.floor(length / 2);
        let node = getNode(head!, n);
        retval = new TreeNode(node.val);
        retval.left = buildBST(head, n);
        retval.right = buildBST(node.next, length - n - 1);
    } else if (length > 0) {
        retval = new TreeNode(head.val);
    }
    return retval;
}

export function sortedListToBST(head: ListNode | null): TreeNode | null {
    let retval = null;
    if (head !== null) {
        let n = length(head);
        retval = buildBST(head, n);
    }
    return retval;
}
