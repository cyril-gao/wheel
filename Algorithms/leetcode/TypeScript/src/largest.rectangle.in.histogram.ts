/*
Given an array of integers heights representing the histogram's bar height
where the width of each bar is 1, return the area of the largest rectangle
in the histogram.
*/

function _largestRectangleArea(heights: number[], begin: number, end: number): number {
    let retval = 0;
    if (begin < end) {
        let mid = Math.floor((begin + end) / 2);
        if (mid !== begin) {
            const r1 = _largestRectangleArea(heights, begin, mid);
            const r2 = _largestRectangleArea(heights, mid, end);
            let r3 = 0;
            let r4 = 0;
            let i = mid - 1;
            let j = mid;
            let h = Math.min(heights[i], heights[j]);
            while (i >= begin || j < end) {
                while (i >= begin && heights[i] >= h) {
                    r3 += h;
                    --i;
                }
                while (j < end && heights[j] >= h) {
                    r3 += h;
                    ++j;
                }
                let h2 = 0;
                if (i >= begin) {
                    h2 = heights[i];
                }
                let h3 = 0;
                if (j < end) {
                    h3 = heights[j];
                }
                h2 = Math.max(h2, h3);
                r4 = Math.max(r3, r4);
                if (h2 !== h) {
                    h = h2;
                    r3 = (j - i - 1) * h;
                }
            }
            retval = Math.max(r1, r2, r3, r4);
        } else {
            retval = heights[begin];
        }
    }
    return retval;
}

export function largestRectangleArea(heights: number[]): number {
    return _largestRectangleArea(heights, 0, heights.length);
}
