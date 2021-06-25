import { TreeNode } from './tree.node';
import { buildTree } from './binary.tree.rebuilding';

test(
    "check the result value of the call to the function buildTree",
    () => {
        let inorder = [9, 3, 15, 20, 7];
        let postorder = [9, 15, 7, 20, 3];
        let result = buildTree(inorder, postorder);
        expect(result !== null).toBe(true);
        expect(result.val).toEqual(3);
        expect(result.left.val).toEqual(9);
        expect(result.left.left).toEqual(null);
        expect(result.left.right).toEqual(null);
        expect(result.right.val).toEqual(20);
        expect(result.right.left.val).toEqual(15);
        expect(result.right.right.val).toEqual(7);
        expect(result.right.left.left).toEqual(null);
        expect(result.right.left.right).toEqual(null);
        expect(result.right.right.left).toEqual(null);
        expect(result.right.right.right).toEqual(null);

        inorder = [-1];
        postorder = [-1];
        result = buildTree(inorder, postorder);
        expect(result.val).toEqual(-1);
        expect(result.left).toEqual(null);
        expect(result.right).toEqual(null);
    }
);
