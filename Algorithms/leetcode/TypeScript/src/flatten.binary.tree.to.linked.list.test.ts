import { TreeNode } from './tree.node';
import { flatten } from './flatten.binary.tree.to.linked.list';

test(
    "check the result value of the call to the function flatten",
    () => {
        {
            let n1 = new TreeNode(1);
            let n2 = new TreeNode(2);
            let n5 = new TreeNode(5);
            n1.left  = n2;
            n1.right = n5;

            let n3 = new TreeNode(3);
            let n4 = new TreeNode(4);
            n2.left = n3;
            n2.right = n4;

            let n6 = new TreeNode(6);
            n5.right = n6;

            flatten(n1);
            expect(n1.left).toEqual(null);
            expect(n1.right).toEqual(n2);
            expect(n2.left).toEqual(null);
            expect(n2.right).toEqual(n3);
            expect(n3.left).toEqual(null);
            expect(n3.right).toEqual(n4);
            expect(n4.left).toEqual(null);
            expect(n4.right).toEqual(n5);
            expect(n5.left).toEqual(null);
            expect(n5.right).toEqual(n6);
            expect(n6.left).toEqual(null);
            expect(n6.right).toEqual(null);
        }
        {
            let n1 = new TreeNode(1);
            flatten(n1);
            expect(n1.left).toEqual(null);
            expect(n1.right).toEqual(null);
        }
    }
);
