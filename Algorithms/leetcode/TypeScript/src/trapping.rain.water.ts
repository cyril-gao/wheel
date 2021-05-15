/*
Given n non-negative integers representing an elevation map
where the width of each bar is 1, compute how much water
it can trap after raining.
*/

export function trap(height: number[]): number {
    let retval = 0;
    if (height.length > 2) {
        let left = 0;
        let right = height.length - 1;
        for (let i = left + 1; i <= right && height[left] <= height[i]; left = i++) {}
        for (let i = right - 1; i >= left && height[right] <= height[i]; right = i--) {}
        while (left < right) {
            let leftHeight = height[left];
            let rightHeight = height[right];
            if (leftHeight <= rightHeight) {
                for (++left; left < right && height[left] <= leftHeight; ++left) {
                    retval += (leftHeight - height[left]);
                }
            } else {
                for (--right; right > left && height[right] <= rightHeight; --right) {
                    retval += (rightHeight - height[right]);
                }
            }
        }
    }
    return retval;
}
