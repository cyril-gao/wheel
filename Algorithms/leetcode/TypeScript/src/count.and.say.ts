/*
The count-and-say sequence is a sequence of digit strings defined by the recursive formula:

countAndSay(1) = "1"
countAndSay(n) is the way you would "say" the digit string from countAndSay(n-1), which is then converted into a different digit string.
To determine how you "say" a digit string, split it into the minimal number of groups so that each group is a contiguous section all of the same character. Then for each group, say the number of characters, then say the character. To convert the saying into a digit string, replace the counts with a number and concatenate every saying.
*/

function _countAndSay(input: string): string {
    let cache = new Array<string>();
    for (let i = 0; i < input.length;) {
        let count = 1;
        let j = i + 1;
        while (j < input.length && input[j] == input[i]) {
            ++count;
            ++j;
        }
        cache.push(count.toString());
        cache.push(input[i]);
        i = j;
    }
    return cache.join('');
}

export function countAndSay(n: number): string {
    if (n > 0) {
        let retval = '1';
        for (let i = 1; i < n; ++i) {
            retval = _countAndSay(retval);
        }
        return retval;
    }
    throw new Error(`Bad input argement: ${n}, it should be larger than 0`);
}
