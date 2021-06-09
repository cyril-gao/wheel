import { TreeNode } from './tree.node';

/*
Given the root of a binary tree, return the zigzag level order traversal
of its nodes' values. (i.e., from left to right, then right to left for
the next level and alternate between).
*/
export function zigzagLevelOrder(root: TreeNode | null): number[][] {
    let retval: number[][] = [];
    if (root !== null) {
        let nodes = [root];
        for (let count = 0; nodes.length > 0; ++count) {
            let nextLevel: TreeNode[] = [];
            let values = [];
            for (let n of nodes) {
                values.push(n.val);
                if (n.left !== null) {
                    nextLevel.push(n.left);
                }
                if (n.right !== null) {
                    nextLevel.push(n.right);
                }
            }
            if ((count & 1) === 1) {
                values.reverse();
            }
            retval.push(values);
            nodes = nextLevel;
        }
        /*
        let nodes = [root];
        while (nodes.length > 0) {
            let nextLevel: TreeNode[] = [];
            let values = [];
            for (let n of nodes) {
                values.push(n.val);
                if (n.left !== null) {
                    nextLevel.push(n.left);
                }
                if (n.right !== null) {
                    nextLevel.push(n.right);
                }
            }
            retval.push(values);
            values = [];
            nodes = [];
            for (let i = nextLevel.length - 1; i >= 0; --i) {
                let n = nextLevel[i];
                values.push(n.val);
                if (n.right !== null) {
                    nodes.push(n.right);
                }
                if (n.left !== null) {
                    nodes.push(n.left);
                }
            }
            if (values.length !== 0) {
                retval.push(values);
            }
            nodes.reverse();
        }
        */
    }
    return retval;
}
