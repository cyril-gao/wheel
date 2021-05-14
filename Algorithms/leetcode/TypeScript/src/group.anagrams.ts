/*
Given an array of strings strs, group the anagrams together. You can return the answer in any order.

An Anagram is a word or phrase formed by rearranging the letters of a different word or phrase, typically using all the original letters exactly once.
*/

export function groupAnagrams(strs: string[]): string[][] {
    let retval: string[][] = [];
    if (strs.length > 1) {
        let group = new Map<string, string[]>();
        for (let i = 0; i < strs.length; ++i) {
            let key = strs[i].split('').sort().join('');
            let arr = group.get(key);
            if (arr !== undefined) {
                arr.push(strs[i]);
            } else {
                group.set(key, [strs[i]]);
            }
        }
        group.forEach((value) => retval.push(value));
    } else {
        if (strs.length === 1) {
            retval.push([strs[0]]);
        }
    }
    return retval;
};
