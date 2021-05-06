/*
Given two non-negative integers num1 and num2 represented as strings,
return the product of num1 and num2, also represented as a string.
*/

function add(num1: number[], num2: number[]): number[] {
    let retval = new Array<number>(Math.max(num1.length, num2.length));
    let outputIndex = 0;
    let inc = 0;
    let i = 0;
    let j = 0;
    while (i < num1.length && j < num2.length) {
        let s = num1[i] + num2[j] + inc;
        inc = 0;
        if (s > 9) {
            s -= 10;
            inc = 1;
        }
        retval[outputIndex++] = s; //retval.push(s);
        ++i;
        ++j;
    }
    let num = num1;
    if (j < num2.length) {
        i = j;
        num = num2;
    }
    while (i < num.length) {
        let s = num[i] + inc;
        inc = 0;
        if (s > 9) {
            s -= 10;
            inc = 1;
        }
        retval[outputIndex++] = s; //retval.push(s);
        ++i;
    }
    if (inc > 0) {
        retval.push(inc);
    }
    return retval;
}

function multiplyBySingleDigitNumber(num1: number[], num2: number, zero: number): number[] {
    let retval = [];
    if (num2 != 0 && (num1.length > 1 || (num1.length == 1 && num1[0] != 0))) {
        for (let i = 0; i < zero; ++i) {
            retval.push(0);
        }
        let inc = 0;
        for (let i = 0; i < num1.length; ++i) {
            let m = num2 * num1[i] + inc;
            inc = Math.floor(m / 10);
            retval.push(m % 10);
        }
        if (inc != 0) {
            retval.push(inc);
        }
    } else {
        retval.push(0);
    }
    return retval;
}

function multiplyNumbers(num1: number[], num2: number[]): number[] {
    let retval = multiplyBySingleDigitNumber(num1, num2[0], 0);
    for (let i = 1; i < num2.length; ++i) {
        let tmp = multiplyBySingleDigitNumber(num1, num2[i], i);
        retval = add(retval, tmp);
    }
    return retval;
}

function getDigitMap(): Map<string, number> {
    let retval = new Map<string, number>();
    for (let i = 0; i < 10; ++i) {
        retval.set(i.toString(), i);
    }
    return retval;
}

const digitMap = getDigitMap();

function toNumberArray(input: string): number[] {
    let retval = [];
    if (input.length > 0) {
        for (let i = input.length - 1; i >= 0; --i) {
            let d = digitMap.get(input[i]);
            if (d !== undefined) {
                retval.push(d);
            }
        }
    } else {
        retval.push(0);
    }
    return retval;
}

export function multiply(num1: string, num2: string): string {
    let result = multiplyNumbers(
        toNumberArray(num1), toNumberArray(num2)
    );
    result.reverse();
    return result.join('');
}
