package com.example;

import java.util.*;

public class FourSum {
    private int binarySearch(int[] items, int begin, int end, int target) {
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

    public List<List<Integer>> fourSum(int[] nums, int target) {
        Set<List<Integer>> set = new HashSet<>();
        List<List<Integer>> retval = new LinkedList<List<Integer>>();
        if (nums.length >= 4) {
            Arrays.sort(nums);
            for (int i = 0; i < nums.length - 3; ++i) {
                if ((nums[i] + nums[i + 1] + nums[i + 2] + nums[i + 3]) > target) {
                    break;
                }
                for (int j = i + 1; j < nums.length - 2; ++j) {
                    if ((nums[i] + nums[j] + nums[j + 1] + nums[j + 2]) > target) {
                        break;
                    }
                    for (int k = j + 1; k < nums.length - 1; ++k) {
                        int s = nums[i] + nums[j] + nums[k];
                        int r = target - s;
                        int begin = k + 1;
                        int p = binarySearch(nums, begin, nums.length, r);
                        if (p != nums.length && nums[p] == r) {
                            List<Integer> group = new ArrayList<>(4);
                            group.add(nums[i]);
                            group.add(nums[j]);
                            group.add(nums[k]);
                            group.add(r);
                            if (!set.contains(group)) {
                                set.add(group);
                                retval.add(group);
                            }
                        }
                    }
                }
            }
        }
        return retval;
    }
}