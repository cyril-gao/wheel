import { TreeNode } from './tree.node';
import { pathSum } from './path.sum';

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
    "check the result value of the call to the methods of the class pathSum",
    () => {
        {
            let root: TreeNode = null;
            let n5 = new TreeNode(5);
            let n4 = new TreeNode(4);
            let n8 = new TreeNode(8);
            n5.left = n4;
            n5.right = n8;
            root = n5;

            let n11 = new TreeNode(11);
            n4.left = n11;

            let n7 = new TreeNode(7);
            let n2 = new TreeNode(2);
            n11.left = n7;
            n11.right = n2;

            let n13 = new TreeNode(13);
            let n4_2 = new TreeNode(4);
            n8.left = n13;
            n8.right = n4_2;

            let n5_2 = new TreeNode(5);
            let n1 = new TreeNode(1);
            n4_2.left = n5_2;
            n4_2.right = n1;

            let result = pathSum(root, 22);
            expect(result.length).toEqual(2);
            expect(equals(result[0], [5, 4, 11, 2])).toBe(true);
            expect(equals(result[1], [5, 8, 4, 5])).toBe(true);
        }
        {
            let n1 = new TreeNode(1);
            let n2 = new TreeNode(2);
            let n3 = new TreeNode(3);
            n1.left = n2;
            n1.right = n3;
            let result = pathSum(n1, 5);
            expect(result.length).toEqual(0);

            result = pathSum(n1, 3);
            expect(result.length).toEqual(1);
            expect(equals(result[0], [1, 2])).toBe(true);
        }
        {
            let n1 = new TreeNode(1);
            let n2 = new TreeNode(2);
            n1.left = n2;
            let result = pathSum(n1, 0);
            expect(result.length).toEqual(0);
        }
    }
);
