import { TreeNode } from "./tree.node";

export function postorderTraversal(root: TreeNode | null): number[] {
    let retval = [];
    let stack: TreeNode[] = [];
    for (let p = root; p !== null || stack.length > 0;) {
        while (p !== null) {
            stack.push(p, p);
            p = p.left;
        }
        p = stack.pop().right;
        if (p === null) {
            while (stack.length > 0) {
                p = stack.pop();
                retval.push(p.val);
                let child = p;
                p = null;
                if (stack.length > 0) {
                    let top = stack[stack.length - 1];
                    if (child === top.left) {
                        p = stack.pop().right;
                        if (p !== null) {
                            break;
                        }
                    }
                }
            }
        }
    }
    return retval;
}
