import { TreeNode, maxPathSum } from "./binary.tree.maximum.path.sum";

test(
    "check the result value of the call to the function maxPathSum",
    () => {
        function run1() {
            let n1 = new TreeNode(1);
            let n2 = new TreeNode(2);
            let n3 = new TreeNode(3);
            n1.left = n2;
            n1.right = n3;
            let result = maxPathSum(n1);
            expect(result).toEqual(6);
        };
        run1();

        function run2() {
            let n_10 = new TreeNode(-10);
            let n9 = new TreeNode(9);
            let n20 = new TreeNode(20);
            let n15 = new TreeNode(15);
            let n7 = new TreeNode(7);
            n_10.left = n9;
            n_10.right = n20;
            n20.left = n15;
            n20.right = n7;

            let result = maxPathSum(n_10);
            expect(result).toEqual(42);
        };
        run2();

        function run3() {
            let n_7 = new TreeNode(-7);
            let n10 = new TreeNode(10);
            let n3 = new TreeNode(3);
            let n_6 = new TreeNode(-6);
            let n_4 = new TreeNode(-4);
            let n16 = new TreeNode(16);
            let n20 = new TreeNode(20);
            let n7 = new TreeNode(7);
            let n4 = new TreeNode(4);
            let n1 = new TreeNode(1);
            let n_16 = new TreeNode(-16);
            let n_40 = new TreeNode(-40);
            let n11 = new TreeNode(11);
            let n38 = new TreeNode(38);
            let n34 = new TreeNode(34);
            let n12 = new TreeNode(12);
            let n_17 = new TreeNode(-17);

            n_7.left = n10;
            n_7.right = n3;
            n3.left = n_6;
            n3.right = n_4;
            n_6.left = n16;
            n_6.right = n20;
            n_4.left = n7;
            n_4.right = n4;
            n20.left = n1;
            n20.right = n_16;
            n7.right = n_40;
            n4.left = n11;
            n_40.left = n38;
            n_40.right = n34;
            n34.left = n12;
            n34.right = n_17;

            let result = maxPathSum(n_7);
            expect(result).toEqual(46);
            n_40.right = null;
            result = maxPathSum(n_7);
            expect(result).toEqual(38);
            n_40.left = null;
            result = maxPathSum(n_7);
            expect(result).toEqual(31);
        };
        run3();

        function run4() {
            let n_1 = new TreeNode(-1);
            let n_2 = new TreeNode(-2);
            let n_4 = new TreeNode(-4);
            let n3 = new TreeNode(3);
            let n2 = new TreeNode(2);
            n_1.left = n_2;
            n_1.right = n_4;

            let result = maxPathSum(n_1);
            expect(result).toEqual(-1);
            n_4.right = n2;
            result = maxPathSum(n_1);
            expect(result).toEqual(2);
            n_4.left = n3;
            result = maxPathSum(n_1);
            expect(result).toEqual(3);
        };
        run4();
    }
);
