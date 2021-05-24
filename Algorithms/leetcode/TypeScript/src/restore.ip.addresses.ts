/*
Given a string s containing only digits, return all possible valid IP addresses that can be obtained from s. You can return them in any order.

A valid IP address consists of exactly four integers, each integer is between 0 and 255, separated by single dots and cannot have leading zeros. For example, "0.1.2.201" and "192.168.1.1" are valid IP addresses and "0.011.255.245", "192.168.1.312" and "192.168@1.1" are invalid IP addresses. 

Example 1:
Input: s = "25525511135"
Output: ["255.255.11.135","255.255.111.35"]

Example 2:
Input: s = "0000"
Output: ["0.0.0.0"]

Example 3:
Input: s = "1111"
Output: ["1.1.1.1"]

Example 4:
Input: s = "010010"
Output: ["0.10.0.10","0.100.1.0"]

Example 5:
Input: s = "101023"
Output: ["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]
*/

function nextStep(
    input: string,
    part: number,
    index: number,
    selected: string[],
    result: string[]
) {
    if (part < 4) {
        let char = input[index];
        if (char !== '0') {
            for (
                let remains = 3 - part, n = input.length - remains + 1, j = index + 1;
                j < n;
                ++j
            ) {
                let v = input.substring(index, j);
                let num = parseInt(v);
                if (num > 0 && num < 256) {
                    selected.push(v);
                    nextStep(input, part + 1, j, selected, result);
                    selected.pop();
                } else {
                    break;
                }
            }
        } else {
            selected.push('0');
            nextStep(input, part + 1, index + 1, selected, result);
            selected.pop();
        }
    } else {
        if (index === input.length) {
            result.push(selected.join('.'));
        }
    }
}

export function restoreIpAddresses(s: string): string[] {
    let retval = [];
    if (s.length > 3) {
        nextStep(s, 0, 0, [], retval);
    }
    return retval;
}

/*
console.log(restoreIpAddresses("25525511135"));
console.log(restoreIpAddresses("101023"));
console.log(restoreIpAddresses("0000"));
*/
