/*
The string "PAYPALISHIRING" is written in a zigzag pattern on a given number of rows like this:
(you may want to display this pattern in a fixed font for better legibility)

P   A   H   N
A P L S I I G
Y   I   R
And then read line by line: "PAHNAPLSIIGYIR"

Write the code that will take a string and make this conversion given a number of rows:
string convert(string s, int numRows);

Example 1:
Input: s = "PAYPALISHIRING", numRows = 3
Output: "PAHNAPLSIIGYIR"

Example 2:
Input: s = "PAYPALISHIRING", numRows = 4
Output: "PINALSIGYAHRPI"
Explanation:
P     I    N
A   L S  I G
Y A   H R
P     I

Example 3:
Input: s = "A", numRows = 1
Output: "A"
*/

export function convert(s: string, numRows: number): string {
    let retval = s;
    if (s.length > 1 && numRows > 1) {
        let cache = [];
        let sectionLength = (numRows - 1) * 2;
        let sectionSize = Math.floor((s.length + sectionLength - 1) / sectionLength);
        for (let i = 0; i < sectionSize; ++i) {
            cache.push(s[i * sectionLength]);
        }
        for (let i = 1, last = numRows - 1; i < last; ++i) {
            for (let j = 0; j < sectionSize; ++j) {
                let first = i;
                let increment = j * sectionLength;
                first += increment;
                if (first < s.length) {
                    cache.push(s[first]);
                    let second = sectionLength - i + increment;
                    if (second < s.length) {
                        cache.push(s[second]);
                    }
                }
            }
        }
        for (let i = 0; i < sectionSize; ++i) {
            let j = numRows - 1 + i * sectionLength;
            if (j < s.length) {
                cache.push(s[j]);
            }
        }
        retval = cache.join('');
    }
    return retval;
}
