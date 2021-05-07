/*
Given n non-negative integers a1, a2, ..., an , where each represents
a point at coordinate (i, ai). n vertical lines are drawn such that the
two endpoints of the line i is at (i, ai) and (i, 0). Find two lines, 
which, together with the x-axis forms a container, such that the container
contains the most water.
*/

export function maxArea(height: number[]): number {
    let retval = 0;
    let left = 0, right = height.length - 1;
    if (right > left) {
        retval = Math.min(height[left], height[right]) * (right - left);
        while (left < right) {
            if (height[left] <= height[right]) {
                let i = left + 1;
                while (i < right && height[left] >= height[i]) {
                    ++i;
                }
                let v = Math.min(height[i], height[right]) * (right - i);
                retval = Math.max(retval, v);
                left = i;
            } else {
                let i = right - 1;
                while (i > left && height[i] <= height[right]) {
                    --i;
                }
                let v = Math.min(height[left], height[i]) * (i - left);
                retval = Math.max(retval, v);
                right = i;
            }
        }
    }
    return retval;
}
