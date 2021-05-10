function calculateSuffixArray(input: string): number[] {
    let sa = new Array<number>(input.length + 1);
    sa[0] = -1;
    let previous = -1;
    let i = 0;
    while (i < input.length) {
        while (previous >= 0 && input[i] !== input[previous]) {
            previous = sa[previous];
        }
        ++previous;
        ++i;
        sa[i] = previous;
    }
    return sa;
}

// return the index of the first character of the toBeFound substring in txt, or -1.
export function kmpSearch(txt: string, toBeFound: string): number {
    if (txt.length >= toBeFound.length) {
        if (toBeFound.length > 0) {
            let suffixArray = calculateSuffixArray(toBeFound);
            for (let i = 0, j = 0; i < txt.length;)  {
                while (j >= 0 && toBeFound[j] !== txt[i]) {
                    j = suffixArray[j];
                }
                ++i;
                ++j;
                if (j === toBeFound.length) {
                    return i - j;
                }
            }
        } else {
            return 0;
        }
    }
    return -1;
}
