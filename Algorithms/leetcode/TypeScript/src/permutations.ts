/*
Given an array of distinct elements, return all the possible permutations.
You can return the answer in any order.
*/

function nextStep<T>(
    elements: T[],
    index: number,
    no: number,
    visited: boolean[],
    selected: T[],
    result: T[][]
): void {
    if (no < elements.length) {
        for (let i = no, j = index; i < elements.length; ++i) {
            while (visited[j]) {
                ++j;
                if (j >= elements.length) {
                    j = 0;
                }
            }
            let oj = j;
            selected.push(elements[j]);
            visited[oj] = true;
            ++j;
            if (j >= elements.length) {
                j = 0;
            }
            nextStep(elements, j, no + 1, visited, selected, result);
            visited[oj] = false;
            selected.pop();
        }
    } else {
        result.push([...selected]);
    }
}

export function permute<T>(elements: T[]): T[][] {
    let retval = [];
    if (elements.length > 1) {
        let visited = new Array<boolean>(elements.length);
        visited.fill(false);
        nextStep(elements, 0, 0, visited, [], retval);
    } else if (elements.length === 1) {
        retval.push(elements);
    }
    return retval;
}
