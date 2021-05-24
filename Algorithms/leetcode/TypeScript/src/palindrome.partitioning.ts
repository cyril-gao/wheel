/*
Given a string s, partition s such that every substring of the partition is a palindrome. Return all possible palindrome partitioning of s.

A palindrome string is a string that reads the same backward as forward.
*/

function isPalindrome(input: string, begin: number, end: number): boolean {
    let retval = true;
    for (let last = end - 1; begin < last; ++begin, --last) {
        if (input[begin] !== input[last]) {
            retval = false;
            break;
        }
    }
    return retval;
}

function nextStep(
    input: string,
    index: number,
    selected: string[],
    result: string[][]
) {
    if (index < input.length) {
        for (let i = index + 1; i <= input.length; ++i) {
            if (isPalindrome(input, index, i)) {
                selected.push(input.substring(index, i));
                nextStep(input, i, selected, result);
                selected.pop();
            }
        }
    } else {
        if (selected.length > 0) {
            result.push([...selected]);
        }
    }
}

export function partition(s: string): string[][] {
    let retval = [];
    if (s.length > 0) {
        nextStep(s, 0, [], retval);
    }
    return retval;
}
