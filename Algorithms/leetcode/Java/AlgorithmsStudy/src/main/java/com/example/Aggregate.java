package com.example;

import java.util.*;

public class Aggregate {
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

    private List<List<Integer>> twoSum(int[] nums, int start, int target) {
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

    // https://leetcode.com/problems/3sum/
    public List<List<Integer>> threeSum(int[] nums) {
        List<List<Integer>> retval = new LinkedList<List<Integer>>();
        Set<List<Integer>> cache = new HashSet<List<Integer>>();
        Arrays.sort(nums);
        for (int i = 0; i < nums.length - 2;) {
            int nextI = i + 1;
            int a = nums[i];
            if ((a + nums[nextI] + nums[nextI + 1]) > 0) {
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

    // https://leetcode.com/problems/3sum-closest/
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
                        int t1 = s + nums[k - 1], d1 = target - t1;
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

    // https://leetcode.com/problems/two-sum-ii-input-array-is-sorted/
    public int[] twoSumForSortedArray(int[] numbers, int target) {
        int n = numbers.length;
        int[] retval = new int[] { n, n };
        for (int i = 0; i < n - 1; ++i) {
            if (numbers[i] <= target) {
                int j = binarySearch(numbers, i + 1, n, target - numbers[i]);
                if (j != n && (numbers[j] + numbers[i]) == target) {
                    retval[0] = i + 1;
                    retval[1] = j + 1;
                    break;
                }
            }
        }
        return retval;
    }
}
