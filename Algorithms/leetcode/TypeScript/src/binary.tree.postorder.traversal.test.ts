import { TreeNode } from './tree.node';
import { postorderTraversal } from './binary.tree.postorder.traversal';

function equals<T>(elements1: T[], elements2: T[]): boolean {
    let retval = elements1.length === elements2.length;
    if (retval) {
        for (let i = 0; i < elements1.length; ++i) {
            if (elements1[i] !== elements2[i]) {
                retval = false;
                break;
            }
        }
    }
    return retval;
}

test(
    "check the result value of the call to the function postorderTraversal",
    () => {
        {
            let n2 = new TreeNode(2);
            let n1 = new TreeNode(1);
            let n3 = new TreeNode(3);
            n2.left = n1;
            n2.right = n3;

            let result = postorderTraversal(n2);
            let expectation = [1, 3, 2];
            expect(equals(result, expectation)).toBeTruthy();
        }
        {
            let n1 = new TreeNode(1);
            let n2 = new TreeNode(2);
            let n3 = new TreeNode(3);
            n1.right = n2;
            n2.left = n3;

            let result = postorderTraversal(n1);
            let expectation = [3, 2, 1];
            expect(equals(result, expectation)).toBeTruthy();
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

            let result = postorderTraversal(n5);
            let expectation = [1, 3, 6, 4, 5];
            expect(equals(result, expectation)).toBeTruthy();
        }
        {
            let n1 = new TreeNode(1);
            let n2 = new TreeNode(2);
            let n3 = new TreeNode(3);
            let n4 = new TreeNode(4);
            let n5 = new TreeNode(5);
            let n6 = new TreeNode(6);
            let n7 = new TreeNode(7);
            let n8 = new TreeNode(8);
            let n9 = new TreeNode(9);
            let n10 = new TreeNode(10);
            let n11 = new TreeNode(11);
            let n12 = new TreeNode(12);
            let n13 = new TreeNode(13);
            let n14 = new TreeNode(14);
            let n15 = new TreeNode(15);
            let n16 = new TreeNode(16);
            let n17 = new TreeNode(17);
            let n18 = new TreeNode(18);

            n1.left   = n2;
            n1.right  = n3;
            n2.left   = n4;
            n2.right  = n5;
            n3.right  = n6;
            n4.right  = n7;
            n5.left   = n8;
            n6.left   = n9;
            n6.right  = n10;
            n7.left   = n11;
            n8.right  = n12;
            n10.left  = n13;
            n10.right = n14;
            n11.left  = n15;
            n12.right = n16;
            n13.left  = n17;
            n14.right = n18;

            let result = postorderTraversal(n1);
            let expectation = [15, 11, 7, 4, 16, 12, 8, 5, 2, 9, 17, 13, 18, 14, 10, 6, 3, 1];
            expect(equals(result, expectation)).toBeTruthy();
        }
    }
);
