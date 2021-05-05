/*
Given a string s, find the length of the longest substring
without repeating characters.
*/

export function lengthOfLongestSubstring(s: string): number {
    let retval = s.length;
    if (retval > 1) {
        retval = 1;
        let begin = 0;
        let map = new Map<string, number>();
        map.set(s[0], 0);
        let currentLength = 1;
        for (let i = 1; i < s.length; ++i) {
            let j = map.get(s[i]);
            map.set(s[i], i);
            if (j === undefined || j < begin) {
                ++currentLength;
                retval = Math.max(retval, currentLength);
            } else {
                begin = j + 1;
                currentLength = i - begin + 1;
            }
        }
    }
    return retval;
};
