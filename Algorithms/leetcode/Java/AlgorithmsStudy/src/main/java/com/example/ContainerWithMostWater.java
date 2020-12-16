package com.example;

public class ContainerWithMostWater {
    public int maxArea(int[] height) {
        int first = 0, last = height.length - 1;
        int retval = Math.min(height[first], height[last]) * (last - first);
        while (first < last) {
            int v;
            if (height[first] <= height[last]) {
                v = height[first];
                for (++first; first < last && height[first] <= v; ++first) {
                }
            } else {
                v = height[last];
                for (--last; first < last && height[last] <= v; --last) {
                }
            }
            v = Math.min(height[first], height[last]) * (last - first);
            if (v > retval) {
                retval = v;
            }
        }
        return retval;
    }

    public static void main(String[] args) {
        int[] input = { 1, 8, 6, 2, 5, 4, 8, 3, 7 };
        var result = new ContainerWithMostWater().maxArea(input);
        System.out.println(result);
    }
}