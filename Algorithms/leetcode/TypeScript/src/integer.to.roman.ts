/*
Roman numerals are represented by seven different symbols: I, V, X, L, C, D and M.

Symbol       Value
I             1
V             5
X             10
L             50
C             100
D             500
M             1000

For example, 2 is written as II in Roman numeral, just two one's added together. 12 is written as XII, which is simply X + II. The number 27 is written as XXVII, which is XX + V + II.

Roman numerals are usually written largest to smallest from left to right. However, the numeral for four is not IIII. Instead, the number four is written as IV. Because the one is before the five we subtract it making four. The same principle applies to the number nine, which is written as IX. There are six instances where subtraction is used:
- I can be placed before V (5) and X (10) to make 4 and 9. 
- X can be placed before L (50) and C (100) to make 40 and 90. 
- C can be placed before D (500) and M (1000) to make 400 and 900.

Given an integer, convert it to a roman numeral.
*/

export function intToRoman(num: number): string {
    const romanNumberFormat = [
        {
            throttle: {value: 1000, symbol: 'M'},
            upper: {value: 900, symbol: 'CM'},
            middle: {value: 500, symbol: 'D'},
            lower: {value: 400, symbol: 'CD'}
        },
        {
            throttle: {value: 100, symbol: 'C'},
            upper: {value: 90, symbol: 'XC'},
            middle: {value: 50, symbol: 'L'},
            lower: {value: 40, symbol: 'XL'}
        },
        {
            throttle: {value: 10, symbol: 'X'},
            upper: {value: 9, symbol: 'IX'},
            middle: {value: 5, symbol: 'V'},
            lower: {value: 4, symbol: 'IV'}
        }
    ];

    if (num > 0) {
        let cache = [];
        for (let rnf of romanNumberFormat) {
            for (let i = 0, quotient = Math.floor(num / rnf.throttle.value); i < quotient; ++i) {
                cache.push(rnf.throttle.symbol);
            }
            num = Math.floor(num % rnf.throttle.value);
            if (num >= rnf.upper.value) {
                cache.push(rnf.upper.symbol);
                num -= rnf.upper.value;
            }
            if (num >= rnf.middle.value) {
                cache.push(rnf.middle.symbol);
                num -= rnf.middle.value;
            }
            if (num >= rnf.lower.value) {
                cache.push(rnf.lower.symbol);
                num -= rnf.lower.value;
            }
        }
        for (let i = 0; i < num; ++i) {
            cache.push('I');
        }
        return cache.join('');
    }
    throw new Error(`Bad number: ${num}, it must be great then 0`);
};