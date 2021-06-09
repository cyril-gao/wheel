import { TreeNode } from './tree.node';

/*
Given the root of a binary tree and an integer targetSum, return all root-to-leaf paths where each path's sum equals targetSum.

A leaf is a node with no children.
*/
function copy(prefix: number, source: number[][], target: number[][]) {
    for (let i = 0; i < source.length; ++i) {
        target.push([prefix, ...source[i]]);
    }
}

export function pathSum(root: TreeNode | null, targetSum: number): number[][] {
    let retval = [];
    if (root !== null) {
        let remains = targetSum - root.val;
        if (root.left !== null || root.right !== null) {
            let result = pathSum(root.left, remains);
            copy(root.val, result, retval);
            result = pathSum(root.right, remains);
            copy(root.val, result, retval);
        } else {
            if (remains === 0) {
                retval.push([root.val]);
            }
        }
    }
    return retval;
}
