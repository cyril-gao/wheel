package com.cybernumen;

import java.util.*;

public class ThreeSum {
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

    private List<List<Integer>> twoSum(int[] nums, int start, int target)
    {
        List<List<Integer>> retval = new LinkedList<List<Integer>>();
        Set<ArrayList<Integer>> cache = new HashSet<ArrayList<Integer>>();
        for (int i = start; i < nums.length - 1;) {
            int nextI = i + 1;
            int a = nums[i];
            int b = target - a;
            if (a <= b) {
                int j = binarySearch(nums, nextI, nums.length, b);
                if (j != nums.length && nums[j] == b) {
                    ArrayList<Integer> item = new ArrayList<Integer>(3);
                    item.add(a);
                    item.add(b);
                    if (!cache.contains(item)) {
                        cache.add(item);
                        retval.add(item);
                    }
                }
            } else {
                break;
            }
            i = nextI;
        }
        return retval;
    }

    public List<List<Integer>> threeSum(int[] nums) {
        List<List<Integer>> retval = new LinkedList<List<Integer>>();
        Set<List<Integer>> cache = new HashSet<List<Integer>>();
        Arrays.sort(nums);
        for (int i = 0; i < nums.length - 2;) {
            int nextI = i + 1;
            int a = nums[i];
            if ((a + nums[nextI] + nums[nextI+1]) > 0) {
                break;
            }
            List<List<Integer>> result = twoSum(nums, nextI, -a);
            for (List<Integer> item : result) {
                item.add(0, a);
                if (!cache.contains(item)) {
                    cache.add(item);
                    retval.add(item);
                }
            }
            i = nextI;
        }
        return retval;
    }
}