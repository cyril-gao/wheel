import { TreeNode } from './tree.node';
import { buildTree, ListNode, sortedListToBST } from './binary.tree.rebuilding';

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

test(
    "check the result value of the call to the function sortedListToBST",
    () => {
        {
            let n1 = new ListNode(1);
            let n2 = new ListNode(2);
            let n3 = new ListNode(3);
            let n4 = new ListNode(4);
            let n5 = new ListNode(5);
            n1.next = n2;
            n2.next = n3;
            n3.next = n4;
            n4.next = n5;

            let result = sortedListToBST(n1);
            expect(result !== null).toBe(true);
            expect(result.val).toEqual(3);
            expect(result.left.val).toEqual(2);
            expect(result.right.val).toEqual(5);
            expect(result.left.left.val).toEqual(1);
            expect(result.left.right).toBeNull();
            expect(result.left.left.left).toBeNull();
            expect(result.left.left.right).toBeNull();
            expect(result.right.left.val).toEqual(4);
            expect(result.right.right).toBeNull();
            expect(result.right.left.left).toBeNull();
            expect(result.right.left.right).toBeNull();
        }
        {
            let n1 = new ListNode(1);
            let n2 = new ListNode(2);
            let n3 = new ListNode(3);
            let n4 = new ListNode(4);
            n1.next = n2;
            n2.next = n3;
            n3.next = n4;

            let result = sortedListToBST(n1);
            expect(result !== null).toBe(true);
            expect(result.val).toEqual(3);
            expect(result.left.val).toEqual(2);
            expect(result.right.val).toEqual(4);
            expect(result.left.left.val).toEqual(1);
            expect(result.left.right).toBeNull();
            expect(result.left.left.left).toBeNull();
            expect(result.left.left.right).toBeNull();
            expect(result.right.left).toBeNull();
            expect(result.right.right).toBeNull();
        }
    }
);
