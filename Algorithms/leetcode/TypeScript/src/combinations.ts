/*
Given two integers n and k, return all possible combinations of k numbers out of the range [1, n].

You may return the answer in any order.
*/

function nextStep(
    n: number,
    start: number,
    remains: number,
    selected: number[],
    result: number[][]
): void {
    if (remains > 0) {
        for (let i = start + 1, ie = n - remains + 1; i < ie; ++i) {
            selected.push(i + 1);
            nextStep(n, i, remains - 1, selected, result);
            selected.pop();
        }
    } else {
        result.push([...selected]);
    }
}

export function combine(n: number, k: number): number[][] {
    let retval = [];
    if (k < n) {
        for (let i = 0, ie = n - k + 1; i < ie; ++i) {
            nextStep(n, i, k - 1, [i + 1], retval);
        }
    } else if (k === n) {
        let result = new Array<number>(n);
        for (let i = 0, j = 1; i < n; ++i, ++j) {
            result[i] = j;
        }
        retval.push(result);
    }
    return retval;
}
