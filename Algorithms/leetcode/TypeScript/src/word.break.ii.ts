/*
Given a string s and a dictionary of strings wordDict, add spaces in s to construct
a sentence where each word is a valid dictionary word. Return all such possible
sentences in any order.

Note that the same word in the dictionary may be reused multiple times in the
segmentation.

Example 1:
Input: s = "catsanddog", wordDict = ["cat","cats","and","sand","dog"]
Output: ["cats and dog","cat sand dog"]

Example 2:
Input: s = "pineapplepenapple", wordDict = ["apple","pen","applepen","pine","pineapple"]
Output: ["pine apple pen apple","pineapple pen apple","pine applepen apple"]
Explanation: Note that you are allowed to reuse a dictionary word.

Example 3:
Input: s = "catsandog", wordDict = ["cats","dog","sand","and","cat"]
Output: []
*/

function equals(input: string, start: number, word: string): boolean {
    let retval = (start + word.length) <= input.length;
    if (retval) {
        for (let i = 0; i < word.length; ++i, ++start) {
            if (input[start] !== word[i]) {
                retval = false;
                break;
            }
        }
    }
    return retval;
}

function nextStep(
    m: number,
    start: number,
    cache: number[][],
    wordDict: string[],
    selected: string[],
    result: string[]
): void {
    if (start < m) {
        for (let i = 0; i < cache[start].length; ++i) {
            if (cache[start][i] > 0) {
                selected.push(wordDict[i]);
                nextStep(m, start + cache[start][i], cache, wordDict, selected, result);
                selected.pop();
            }
        }
    } else {
        result.push(selected.join(' '));
    }
}

export function wordBreak(s: string, wordDict: string[]): string[] {
    let retval = [];
    let m = s.length;
    let n = wordDict.length;
    if (m > 0 && n > 0) {
        let cache = new Array<number[]>(m);
        for (let start = 0; start < m; ++start) {
            let row = new Array<number>(n);
            row.fill(-1);
            for (let i = 0; i < n; ++i) {
                if (equals(s, start, wordDict[i])) {
                    row[i] = wordDict[i].length;
                }
            }
            cache[start] = row;
        }

        for (let i = 0; i < cache[0].length; ++i) {
            if (cache[0][i] > 0) {
                nextStep(m, cache[0][i], cache, wordDict, [wordDict[i]], retval);
            }
        }
    }
    return retval;
}
