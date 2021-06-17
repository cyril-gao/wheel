/*
You are given a perfect binary tree where all leaves are on the same level, and every parent has two children. The binary tree has the following definition:

struct Node {
    int val;
    Node *left;
    Node *right;
    Node *next;
}
Populate each next pointer to point to its next right node. If there is no next right node, the next pointer should be set to NULL.

Initially, all next pointers are set to NULL.


Follow up:
    - You may only use constant extra space.
    - Recursive approach is fine, you may assume implicit stack space does not count as extra space for this problem.
*/

export class Node {
    val: number;
    left: Node | null;
    right: Node | null;
    next: Node | null;

    constructor(val?: number, left?: Node, right?: Node, next?: Node) {
        this.val = (val===undefined ? 0 : val);
        this.left = (left===undefined ? null : left);
        this.right = (right===undefined ? null : right);
        this.next = (next===undefined ? null : next);
    }
}

export function connect(root: Node | null): Node | null {
    let retval = root;
    if (root !== null) {
        root.next = null;
        let parent = root;
        let child = null;
        let previous = null;
        while (parent !== null) {
            for (let p = parent; p !== null; p = p.next) {
                if (p.left !== null) {
                    if (previous !== null) {
                        previous.next = p.left;
                    } else {
                        child = p.left;
                    }
                    previous = p.left;
                }
                if (p.right !== null) {
                    if  (previous !== null) {
                        previous.next = p.right;
                    } else {
                        child = p.right;
                    }
                    previous = p.right;
                }
            }
            if (previous !== null) {
                previous.next = null;
            }
            parent = child;
            child = null;
            previous = null;
        }
    }
    return retval;
}
