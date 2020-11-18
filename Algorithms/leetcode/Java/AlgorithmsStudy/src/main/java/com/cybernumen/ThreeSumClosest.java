package com.cybernumen;

import java.util.Arrays;

public class ThreeSumClosest {
    private int binarySearch(int[] items, int begin, int end, int target)
    {
        int mid = end;
        while (begin < end) {
            mid = (begin + end) / 2;
            if (items[mid] < target) {
                begin = mid + 1;
                mid = end;
            } else if (items[mid] > target) {
                end = mid;
                mid = begin;
            } else {
                break;
            }
        }
        return mid;
    }

    public int threeSumClosest(int[] nums, int target) {
        int retval = 0;
        if (nums != null && nums.length > 0) {
            Arrays.sort(nums);
            int diff = Integer.MAX_VALUE;
            for (int i = 0; i < nums.length - 2 && diff != 0; ++i) {
                for (int j = i + 1, begin = j + 1; j < nums.length - 1; j = begin++) {
                    int s = nums[i] + nums[j];
                    int d = target - s;
                    int k = binarySearch(nums, begin, nums.length, d);
                    if (k != nums.length && nums[k] != d && k > begin) {
                        int t1 = s + nums[k-1], d1 = target - t1;
                        int t2 = s + nums[k], d2 = t2 - target;
                        int t = t2;
                        d = d2;
                        if (d1 < d2) {
                            t = t1;
                            d = d1;
                        }
                        if (d <= diff) {
                            diff = d;
                            retval = t;
                        }
                    } else {
                        if (k == nums.length) {
                            --k;
                        }
                        s += nums[k];
                        d = Math.abs(target - s);
                        if (d <= diff) {
                            diff = d;
                            retval = s;
                        }
                    }
                }
            }
        }

        return retval;
    }
}