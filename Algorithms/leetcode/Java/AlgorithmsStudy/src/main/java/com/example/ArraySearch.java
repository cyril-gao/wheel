package com.example;

import java.util.*;

public class ArraySearch {
    /**
     * Suppose an array sorted in ascending order is rotated at some pivot unknown
     * to you beforehand.
     * 
     * (i.e., [0,1,2,4,5,6,7] might become [4,5,6,7,0,1,2]).
     * 
     * You are given a target value to search. If found in the array return its
     * index, otherwise return -1.
     * 
     * You may assume no duplicate exists in the array.
     * 
     * Your algorithm's runtime complexity must be in the order of O(log n).
     */
    private int binarySearch(int[] nums, int begin, int end, int target) {
        int m = end;
        while (begin < end) {
            m = (begin + end) / 2;
            if (nums[m] < target) {
                begin = m + 1;
                m = end;
            } else if (nums[m] > target) {
                end = m;
                m = begin;
            } else {
                break;
            }
        }
        return m;
    }

    private int search(int[] nums, int begin, int end, int target) {
        int m = -1;
        if (nums != null && nums.length > 0) {
            int originalEnd = end;
            if (target != nums[begin]) {
                int pm = begin;
                int firstElement = nums[begin++];
                for (int _begin = begin, _end = end;;) {
                    m = (_begin + _end) / 2;
                    while (m < _end && firstElement <= nums[m]) {
                        pm = m;
                        m = (m + 1 + _end) / 2;
                    }
                    if (m < _end) {
                        _begin = pm;
                        _end = m;
                    } else {
                        end = _end;
                        break;
                    }
                }
                m = binarySearch(nums, begin, end, target);
                if (m == end || nums[m] != target) {
                    if (target < firstElement) {
                        m = binarySearch(nums, end, originalEnd, target);
                    }
                }
                if (m == originalEnd || nums[m] != target) {
                    m = -1;
                }
            } else {
                m = begin;
            }
        }
        return m;
    }

    public int search(int[] nums, int target) {
        return search(nums, 0, nums.length, target);
    }

    public int[] searchRange(int[] nums, int target) {
        int lower = -1, upper = -1;
        if (nums != null && nums.length > 0) {
            int begin = 0, end = nums.length, mid = end;
            while (begin < end) {
                mid = (begin + end) / 2;
                if (nums[mid] < target) {
                    begin = mid + 1;
                    mid = end;
                } else if (nums[mid] > target) {
                    end = mid;
                    mid = begin;
                } else {
                    upper = mid;
                    end = mid;
                    while (begin < end) {
                        mid = (begin + end) / 2;
                        if (nums[mid] != target) {
                            begin = mid + 1;
                            mid = end;
                        } else {
                            end = mid;
                            mid = begin;
                        }
                    }
                    lower = mid;
                    begin = upper + 1;
                    end = nums.length;
                    mid = end;
                    while (begin < end) {
                        mid = (begin + end) / 2;
                        if (nums[mid] != target) {
                            end = mid;
                            mid = begin;
                        } else {
                            begin = mid + 1;
                            mid = end;
                        }
                    }
                    upper = mid - 1;
                    break;
                }
            }
        }
        return new int[] { lower, upper };
    }

    public int firstMissingPositive(int[] nums) {
        int retval = 1;
        if (nums != null && nums.length > 0) {
            for (int i = 0; i < nums.length; ++i) {
                int value = nums[i];
                int index = value - 1;
                if (index != i) {
                    nums[i] = 0;
                    while (index >= 0 && index < nums.length && nums[index] != (index + 1)) {
                        int tmp = nums[index];
                        nums[index] = value;
                        value = tmp;
                        index = value - 1;
                    }
                }
            }
            retval = 1;
            for (int i = 0; i < nums.length; i = retval++) {
                if (nums[i] != retval) {
                    break;
                }
            }
        }
        return retval;
    }

    private boolean searchInRotatedSortedArray(int[] nums, int begin, int end, int target) {
        if (begin < end) {
            int front = nums[begin];
            if (target < front) {
                int back = nums[--end];
                if (back < target) {
                    return false;
                }
                if (back == target) {
                    return true;
                }
                ++begin;
                while (begin < end) {
                    int mid = (begin + end) / 2;
                    if (nums[mid] > front) {
                        begin = mid + 1;
                    } else if (nums[mid] < front) {
                        if (nums[mid] > target) {
                            end = mid;
                        } else if (nums[mid] < target) {
                            begin = mid + 1;
                            int r = binarySearch(nums, begin, end, target);
                            return (r != end) && (nums[r] == target);
                        } else {
                            return true;
                        }
                    } else {
                        if (searchInRotatedSortedArray(nums, begin, mid, target)) {
                            return true;
                        }
                        return searchInRotatedSortedArray(nums, mid + 1, end, target);
                    }
                }
            } else if (target > front) {
                int back = nums[end - 1];
                while (begin < end) {
                    int mid = (begin + end) / 2;
                    if (nums[mid] < front) {
                        end = mid;
                    } else if (nums[mid] > front) {
                        if (nums[mid] > target) {
                            end = mid;
                            int r = binarySearch(nums, begin, end, target);
                            return (r != end) && (nums[r] == target);
                        } else if (nums[mid] < target) {
                            begin = mid + 1;
                        } else {
                            return true;
                        }
                    } else {
                        if (nums[mid] <= back) {
                            if (searchInRotatedSortedArray(nums, begin, mid, target)) {
                                return true;
                            }
                            return searchInRotatedSortedArray(nums, mid + 1, end, target);
                        } else {
                            begin = mid + 1;
                        }
                    }
                }
            } else {
                return true;
            }
        }
        return false;
    }

    public boolean searchInRotatedSortedArray(int[] nums, int target) {
        if (nums != null && nums.length > 0) {
            return searchInRotatedSortedArray(nums, 0, nums.length, target);
        }
        return false;
    }

    public void sortColors(int[] nums) {
        if (nums != null && nums.length > 1) {
            int zero = -1;
            int two = nums.length;
            for (int i = 0; i < two;) {
                int v = nums[i];
                assert (v >= 0 && v <= 2);
                if (v == 0) {
                    ArrayOperations.swap(nums, ++zero, i++);
                } else if (v == 2) {
                    ArrayOperations.swap(nums, --two, i);
                } else {
                    ++i;
                }
            }
        }
    }

    public int findMinInUniqueElements(int[] nums) {
        int start = nums[0];
        int back = nums[nums.length - 1];
        if (start > back) {
            int begin = 1;
            int end = nums.length;
            while (begin < end) {
                int mid = (begin + end) / 2;
                int v = nums[mid];
                if (v > back) {
                    begin = mid + 1;
                } else {
                    end = mid;
                }
            }
            return nums[begin];
        } else {
            return start;
        }
    }

    private int findMinInRotatedSortedArray(int[] nums, int begin, int end) {
        assert (begin < end && end <= nums.length);
        int front = nums[begin];
        int back = nums[end - 1];
        if (front >= back) {
            int retval = back;
            for (++begin; begin < end;) {
                int mid = (begin + end) / 2;
                int middle = nums[mid];
                if (middle > front) {
                    begin = mid + 1;
                } else if (middle < front) {
                    retval = middle;
                    end = mid;
                } else {
                    if (begin < mid) {
                        int r = findMinInRotatedSortedArray(nums, begin, mid);
                        if (retval > r) {
                            retval = r;
                        }
                    }
                    if ((mid + 1) < end) {
                        int r = findMinInRotatedSortedArray(nums, mid + 1, end);
                        if (retval > r) {
                            retval = r;
                        }
                    }
                    break;
                }
            }
            return retval;
        } else {
            return front;
        }
    }

    public int findMin(int[] nums) {
        int retval = 0;
        int n = nums != null ? nums.length : 0;
        if (n > 1) {
            retval = findMinInRotatedSortedArray(nums, 0, n);
        } else {
            if (n == 1) {
                retval = nums[0];
            }
        }
        return retval;
    }

    private int partition(int[] nums, int start, int end) {
        int ge = end;
        int v = nums[start];
        for (int i = end; i > start;) {
            --i;
            if (nums[i] >= v) {
                --ge;
                ArrayOperations.swap(nums, ge, i);
            }
        }
        return ge;
    }

    private int findKthLargest(int[] nums, int begin, int end, int k) {
        int separator = partition(nums, begin, end);
        int v = end - separator;
        if (v == k) {
            return nums[separator];
        } else {
            if (v > k) {
                return findKthLargest(nums, separator + 1, end, k);
            } else {
                return findKthLargest(nums, begin, separator, k - v);
            }
        }
    }

    public int findKthLargest(int[] nums, int k) {
        int n = nums != null ? nums.length : 0;
        assert (k <= n);
        return findKthLargest(nums, 0, n, k);
    }

    private int hIndexInSortedArray(int[] citations, int n) {
        int retval = 0;
        if (n > 0) {
            if (citations[0] < n) {
                int begin = 0, end = n;
                int mid = n;
                while (begin < end) {
                    mid = (begin + end) / 2;
                    int v = (n - mid);
                    if (v > citations[mid]) {
                        begin = mid + 1;
                        mid = end;
                    } else if (v < citations[mid]) {
                        end = mid;
                        mid = begin;
                    } else {
                        break;
                    }
                }
                if (mid != n) {
                    retval = n - mid;
                }
            } else {
                retval = n;
            }
        }
        return retval;
    }

    private int hIndexNormal(int[] citations, int n) {
        int retval = 0;
        if (citations[0] < n) {
            for (int i = 0, j = n; i < n; ++i, --j) {
                if (j <= citations[i]) {
                    retval = j;
                    break;
                }
            }
        } else {
            retval = n;
        }
        return retval;
    }

    // https://leetcode.com/problems/h-index/
    public int hIndex(int[] citations) {
        int retval = 0;
        int n = citations != null ? citations.length : 0;
        if (n > 0) {
            Arrays.sort(citations);
            retval = hIndexInSortedArray(citations, n);
        }
        return retval;
    }

    static int binarySearchInRepetitiveElements(int[] nums, int begin, int end, int target) {
        int originalBegin = begin;
        int m = end;
        while (begin < end) {
            m = (begin + end) / 2;
            if (nums[m] < target) {
                begin = m + 1;
                m = end;
            } else if (nums[m] > target) {
                end = m;
                m = begin;
            } else {
                if (m > originalBegin && nums[m - 1] == target) {
                    end = m;
                    continue;
                }
                break;
            }
        }
        return m;
    }

    // https://leetcode.com/problems/intersection-of-two-arrays-ii/
    public int[] intersect(int[] nums1, int[] nums2) {
        Arrays.sort(nums1);
        Arrays.sort(nums2);
        List<Integer> result = new ArrayList<>(nums2.length);
        int begin = 0;
        for (int v : nums2) {
            int i = binarySearchInRepetitiveElements(nums1, begin, nums1.length, v);
            if (i != nums1.length) {
                if (nums1[i] == v) {
                    result.add(v);
                    ++i;
                }
                begin = i;
            } else {
                break;
            }
        }
        return result.stream().mapToInt(Integer::intValue).toArray();
    }
}
