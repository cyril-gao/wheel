import { TreeNode } from './tree.node';
import { sumNumbers } from './sum.root.to.leaf.numbers';

test(
    "check the result value of the call to the methods of the class sumNumbers",
    () => {
        {
            let n1 = new TreeNode(1);
            let n2 = new TreeNode(2);
            let n3 = new TreeNode(3);
            n1.left = n2;
            n1.right = n3;
            expect(sumNumbers(n1)).toEqual(25);
        }
        {
            let n4 = new TreeNode(4);
            let n9 = new TreeNode(9)
            let n0 = new TreeNode(0);
            n4.left = n9;
            n4.right = n0;
            let n5 = new TreeNode(5);
            let n1 = new TreeNode(1);
            n9.left = n5;
            n9.right = n1;

            expect(sumNumbers(n4)).toEqual(1026);
        }
        {
            let n1 = new TreeNode(1);
            let n2 = new TreeNode(2);
            let n3 = new TreeNode(3);
            n1.left = n2;
            n1.right = n3;

            let n0 = new TreeNode(0);
            let n7 = new TreeNode(7);
            n2.left = n0;
            n2.right  = n7;

            let n4 = new TreeNode(4);
            let n5 = new TreeNode(5);
            n3.left = n4;
            n3.right = n5;

            let n9 = new TreeNode(9);
            n7.left = n9;

            let n6 = new TreeNode(6);
            n5.left = n6;
            let n8 = new TreeNode(8);
            n6.left = n8;

            expect(sumNumbers(n1)).toEqual(15101);
        }
    }
);
