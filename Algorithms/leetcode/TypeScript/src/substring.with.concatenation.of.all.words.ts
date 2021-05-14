/*
You are given a string s and an array of strings words of the same length.
Return all starting indices of substring(s) in s that is a concatenation of
each word in words exactly once, in any order, and without any intervening
characters.

You can return the answer in any order.

Example 1:
Input: s = "barfoothefoobarman", words = ["foo","bar"]
Output: [0,9]
Explanation: Substrings starting at index 0 and 9 are "barfoo" and "foobar" respectively.
The output order does not matter, returning [9,0] is fine too.

Example 2:
Input: s = "wordgoodgoodgoodbestword", words = ["word","good","best","word"]
Output: []

Example 3:
Input: s = "barfoofoobarthefoobarman", words = ["bar","foo","the"]
Output: [6,9,12]
*/

function toMap(words: string[]): Map<string, number> {
    let retval = new Map<string, number>();
    for (let w of words) {
        let n = retval.get(w);
        if (n !== undefined) {
            ++n;
        } else {
            n = 1;
        }
        retval.set(w, n);
    }
    return retval;
}

function getCandidates(s: string, map: Map<string, number>, n: number): number[] {
    let set = new Set<number>();
    for (let i = 0; i < s.length; ++i) {
        let added = false;
        map.forEach(
            (v, k) => {
                let j = s.indexOf(k, i);
                if (j >= 0 && (j + n) <= s.length) {
                    added = true;
                    set.add(j);
                }
            }
        );
        if (!added) {
            break;
        }
    }
    return [...set].sort((a, b) => a < b ? -1 : a > b ? 1 : 0);
}

export function findSubstring(s: string, words: string[]): number[] {
    let retval = [];
    if (words.length > 0) {
        let len = words[0].length;
        let totalLen = len;
        for (let i = 1; i < words.length; ++i) {
            totalLen += words[i].length;
        }
        let map = toMap(words);
        for (let i of getCandidates(s, map, totalLen)) {
            for (let j = 0, k = i + j * len, ke = k + len; j < words.length; ++j, k = ke, ke += len) {
                let v = s.substring(k, ke);
                let c = map.get(v);
                if (c !== undefined) {
                    if (c === 1) {
                        map.delete(v);
                    } else {
                        map.set(v, c - 1);
                    }
                } else {
                    break;
                }
            }
            if (map.size === 0) {
                retval.push(i);
            } else {
                map.clear();
            }
            map = toMap(words);
        }
    }
    return retval;
}
