import { Node, connect } from './populating.next.right.pointers.in.each.node';

test(
    "check the result value of the call to the function connect",
    () => {
        {
            let n1 = new Node(1);
            let n2 = new Node(2);
            let n3 = new Node(3);
            n1.left = n2;
            n1.right = n3;

            let n4 = new Node(4);
            let n5 = new Node(5);
            n2.left = n4;
            n2.right = n5;

            let n6 = new Node(6);
            let n7 = new Node(7);
            n3.left = n6;
            n3.right = n7;

            let result = connect(n1);
            expect(result.next).toBe(null);
            expect(result.left.next).toEqual(n3);
            expect(result.left.next.next).toEqual(null);
            expect(result.left.left.next).toEqual(n5);
            expect(result.left.left.next.next).toEqual(n6);
            expect(result.left.left.next.next.next).toEqual(n7);
            expect(result.left.left.next.next.next.next).toEqual(null);
        }
    }
);
