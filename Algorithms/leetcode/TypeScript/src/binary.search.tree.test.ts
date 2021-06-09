import { TreeNode } from './tree.node';
import { isValidBST } from './binary.search.tree';

test(
    "check the result value of the call to the function isValidBST",
    () => {
        {
            let n2 = new TreeNode(2);
            let n1 = new TreeNode(1);
            let n3 = new TreeNode(3);
            n2.left = n1;
            n2.right = n3;

            expect(isValidBST(n2)).toBe(true);
        }
        {
            let n5 = new TreeNode(5);
            let n1 = new TreeNode(1);
            let n4 = new TreeNode(4);
            n5.left = n1;
            n5.right = n4;
            let n3 = new TreeNode(3);
            let n6 = new TreeNode(6);
            n4.left = n3;
            n4.right = n6;

            expect(isValidBST(n5)).toBe(false);
        }
    }
);
