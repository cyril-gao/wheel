import { TreeNode } from './tree.node';
import { zigzagLevelOrder } from "./zigzag.level.order.traversal";

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
    "check the result value of the call to the function zigzagLevelOrder",
    () => {
        {
            let n1 = new TreeNode(1);
            let n2 = new TreeNode(2);
            let n3 = new TreeNode(3);
            n1.left = n2;
            n1.right = n3;

            let n4 = new TreeNode(4);
            let n5 = new TreeNode(5);
            n2.right = n4;
            n3.left = n5;

            let n6 = new TreeNode(6);
            let n7 = new TreeNode(7);
            n4.left = n6;
            n4.right = n7;

            let n8 = new TreeNode(8);
            n5.right = n8;

            let n9 = new TreeNode(9);
            let n10 = new TreeNode(10);
            n6.right = n9;
            n8.left = n10;

            let result = zigzagLevelOrder(n1);
            expect(result.length).toEqual(5);
            expect(equals(result[0], [1])).toBe(true);
            expect(equals(result[1], [3, 2])).toBe(true);
            expect(equals(result[2], [4, 5])).toBe(true);
            expect(equals(result[3], [8, 7, 6])).toBe(true);
            expect(equals(result[4], [9, 10])).toBe(true);
        }
        {
            let n1 = new TreeNode(1);
            let result = zigzagLevelOrder(n1);
            expect(result.length).toEqual(1);
            expect(equals(result[0], [1])).toBe(true);
        }
        {
            let result = zigzagLevelOrder(null);
            expect(result.length).toEqual(0);
        }
    }
);
