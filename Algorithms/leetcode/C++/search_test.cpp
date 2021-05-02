#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <iterator>
#include <vector>
#include <utility>

#include "check.h"

namespace
{
    template <typename I, typename T>
    I my_binary_search(I begin, I end, const T& target)
    {
        I mid = end;
        while (begin < end) {
            mid = begin + (end - begin) / 2;
            if (*mid > target) {
                end = mid;
                mid = begin;
            } else if (*mid < target) {
                begin = mid + 1;
                mid = end;
            } else {
                break;
            }
        }
        return mid;
    }
}

/*
There is an integer array nums sorted in ascending order (with distinct values).

Prior to being passed to your function, nums is rotated at an unknown pivot index k (0 <= k < nums.length) such that the resulting array is [nums[k], nums[k+1], ..., nums[n-1], nums[0], nums[1], ..., nums[k-1]] (0-indexed). For example, [0,1,2,4,5,6,7] might be rotated at pivot index 3 and become [4,5,6,7,0,1,2].

Given the array nums after the rotation and an integer target, return the index of target if it is in nums, or -1 if it is not in nums.

Constraints:
    All values of nums are unique.
*/

template <typename I, typename T>
I search_in_rotated_sorted_array_without_duplication(I begin, I end, T const& target)
{
    I retval = end;
    size_t n = static_cast<size_t>(end - begin);
    if (n > 1) {
        auto front = *begin;
        I last = begin + (n - 1);
        auto back = *last;
        if (front >= back) {
            if (target >= front) {
                if (target > front) {
                    ++begin;
                    while (begin < last) {
                        I mid = begin + (last - begin) / 2;
                        if (*mid > target) {
                            retval = my_binary_search(begin, mid, target);
                            break;
                        } else if (*mid < target) {
                            if (*mid >= front) {
                                begin = mid + 1;
                            } else {
                                last = mid;
                            }
                        } else {
                            retval = mid;
                            break;
                        }
                    }
                } else {
                    retval = begin;
                }
            } else {
                if (target < back) {
                    ++begin;
                    while (begin < last) {
                        I mid = begin + (last - begin) / 2;
                        if (*mid > target) {
                            if (*mid > front) {
                                begin = mid + 1;
                            } else {
                                last = mid;
                            }
                        } else if (*mid < target) {
                            retval = my_binary_search(mid + 1, last, target);
                            break;
                        } else {
                            retval = mid;
                            break;
                        }
                    }
                } else if (target == back) {
                    retval = last;
                }
            }
            if (retval != end && *retval != target) {
                retval = end;
            }
        } else {
            last = my_binary_search(begin, end, target);
            if (last != end && *last == target) {
                retval = last;
            }
        }
    } else {
        if (n == 1 && *begin == target) {
            retval = begin;
        }
    }
    return retval;
}

void search_in_rotated_sorted_array_without_duplication_test()
{
    {
        std::vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
        auto begin = nums.begin();
        auto end = nums.end();
        for (int target : nums) {
            auto result = search_in_rotated_sorted_array_without_duplication(begin, end, target);
            examine(result != end && *result == target, "search_in_rotated_sorted_array_without_duplication_test is failed for the input: %d\n", target);
        }
        std::vector<int> others = {-1, 3, 8, 9, 11};
        for (int target : others) {
            auto result = search_in_rotated_sorted_array_without_duplication(begin, end, target);
            examine(result == end, "search_in_rotated_sorted_array_without_duplication_test is failed for the input: %d\n", target);
        }
    }
    {
        std::vector<int> nums = {1, 2, 4, 5, 6, 7, 0 };
        auto begin = nums.begin();
        auto end = nums.end();
        for (int target : nums) {
            auto result = search_in_rotated_sorted_array_without_duplication(begin, end, target);
            examine(result != end && *result == target, "search_in_rotated_sorted_array_without_duplication_test is failed for the input: %d\n", target);
        }
        std::vector<int> others = {-1, 3, 8, 9, 11};
        for (int target : others) {
            auto result = search_in_rotated_sorted_array_without_duplication(begin, end, target);
            examine(result == end, "search_in_rotated_sorted_array_without_duplication_test is failed for the input: %d\n", target);
        }
    }
    {
        std::vector<int> nums = {7, 0, 1, 2, 4, 6, 7};
        auto begin = nums.begin();
        auto end = nums.end();
        for (int target : nums) {
            auto result = search_in_rotated_sorted_array_without_duplication(begin, end, target);
            examine(result != end && *result == target, "search_in_rotated_sorted_array_without_duplication_test is failed for the input: %d\n", target);
        }
        std::vector<int> others = {-1, 3, 8, 9, 11};
        for (int target : others) {
            auto result = search_in_rotated_sorted_array_without_duplication(begin, end, target);
            examine(result == end, "search_in_rotated_sorted_array_without_duplication_test is failed for the input: %d\n", target);
        }
    }
    {
        std::vector<int> nums = {6, 0};
        auto begin = nums.begin();
        auto end = nums.end();
        for (int target : nums) {
            auto result = search_in_rotated_sorted_array_without_duplication(begin, end, target);
            examine(result != end && *result == target, "search_in_rotated_sorted_array_without_duplication_test is failed for the input: %d\n", target);
        }
        std::vector<int> others = {-1, 3, 8, 9, 11};
        for (int target : others) {
            auto result = search_in_rotated_sorted_array_without_duplication(begin, end, target);
            examine(result == end, "search_in_rotated_sorted_array_without_duplication_test is failed for the input: %d\n", target);
        }
    }
    {
        std::vector<int> nums = {0, 1, 2, 4, 5, 6, 7};
        auto begin = nums.begin();
        auto end = nums.end();
        for (int target : nums) {
            auto result = search_in_rotated_sorted_array_without_duplication(begin, end, target);
            examine(result != end && *result == target, "search_in_rotated_sorted_array_without_duplication_test is failed for the input: %d\n", target);
        }
        std::vector<int> others = {-1, 3, 8, 9, 11};
        for (int target : others) {
            auto result = search_in_rotated_sorted_array_without_duplication(begin, end, target);
            examine(result == end, "search_in_rotated_sorted_array_without_duplication_test is failed for the input: %d\n", target);
        }
    }
}

/*
Given an array of integers nums sorted in ascending order, find the starting and ending position of a given target value.

If target is not found in the array, return [-1, -1].
*/
namespace
{
    template <typename I, typename T>
    I my_lower_bound(I begin, I end, T const& target)
    {
        I original_begin = begin;
        I mid = end;
        while (begin < end) {
            mid = begin + (end - begin) / 2;
            if (*mid < target) {
                begin = mid + 1;
                mid = end;
            } else if (*mid > target) {
                end = mid;
                mid = begin;
            } else {
                if (mid > original_begin && *(mid - 1) == target) {
                    end = mid;
                    mid = begin;
                } else {
                    break;
                }
            }
        }
        return mid;
    }

    template <typename I, typename T>
    I last_position(I begin, I end, T const& target)
    {
        I last = begin + ((end - begin) - 1);
        I mid = end;
        while (begin < end) {
            mid = begin + (end - begin) / 2;
            if (*mid < target) {
                begin = mid + 1;
                mid = end;
            } else if (*mid > target) {
                end = mid;
                mid = begin;
            } else {
                if (mid < last && *(mid + 1) == target) {
                    begin = mid + 1;
                    mid = end;
                } else {
                    break;
                }
            }
        }
        return mid;
    }
}

template <typename I, typename T>
std::pair<I, I> search_in_sorted_array_with_duplication(I begin, I end, T const& target)
{
    I segment_begin = end;
    I segment_end = end;
    if (begin < end) {
        I original_begin = begin;
        I last = begin + ((end - begin) - 1);

        I mid = end;
        while (begin < end) {
            mid = begin + (end - begin) / 2;
            if (*mid < target) {
                begin = mid + 1;
                mid = end;
            } else if (*mid > target) {
                end = mid;
                mid = begin;
            } else {
                break;
            }
        }

        if (mid <= last && *mid == target) {
            segment_begin = mid;
            if (mid > original_begin && *(mid - 1) == target) {
                I b = begin;
                I e = mid;
                I m = e;
                while (b < e) {
                    m = b + (e - b) / 2;
                    if (*m < target) {
                        b = m + 1;
                        m = e;
                    } else {
                        if (m > original_begin && *(m - 1) == target) {
                            e = m;
                            m = begin;
                        } else {
                            break;
                        }
                    }
                }
                segment_begin = m;
            }
            if (mid < last && *(mid + 1) == target) {
                begin = mid + 1;
                mid = end;
                while (begin < end) {
                    mid = begin + (end - begin) / 2;
                    if (*mid > target) {
                        end = mid;
                        mid = begin;
                    } else {
                        if (mid < last && *(mid + 1) == target) {
                            begin = mid + 1;
                            mid = end;
                        } else {
                            break;
                        }
                    }
                }
            }
            segment_end = mid;
        }
    }
    return std::make_pair(segment_begin, segment_end);
}

void search_in_sorted_array_with_duplication_test()
{
    {
        std::vector<int> nums = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 6, 6, 6, 6, 6, 6};
        auto begin = nums.begin();
        auto end = nums.end();
        examine(my_lower_bound(begin, end, 0) == begin, "my_lower_bound is failed at the line: %d\n", __LINE__);
        examine(last_position(begin, end, 0) == begin, "last_position is failed at the line: %d\n", __LINE__);
        examine(my_lower_bound(begin, end, 1) == begin, "my_lower_bound is failed at the line: %d\n", __LINE__);
        examine(last_position(begin, end, 1) == begin, "last_position is failed at the line: %d\n", __LINE__);
        examine(my_lower_bound(begin, end, 2) == begin + 1, "my_lower_bound is failed at the line: %d\n", __LINE__);
        examine(last_position(begin, end, 2) == begin + 2, "last_position is failed at the line: %d\n", __LINE__);
        examine(my_lower_bound(begin, end, 3) == begin + 3, "my_lower_bound is failed at the line: %d\n", __LINE__);
        examine(last_position(begin, end, 3) == begin + 5, "last_position is failed at the line: %d\n", __LINE__);
        examine(my_lower_bound(begin, end, 4) == begin + 6, "my_lower_bound is failed at the line: %d\n", __LINE__);
        examine(last_position(begin, end, 4) == begin + 9, "last_position is failed at the line: %d\n", __LINE__);
        examine(my_lower_bound(begin, end, 5) == begin + 10, "my_lower_bound is failed at the line: %d\n", __LINE__);
        examine(last_position(begin, end, 5) == begin + 10, "last_position is failed at the line: %d\n", __LINE__);
        examine(my_lower_bound(begin, end, 6) == begin + 10, "my_lower_bound is failed at the line: %d\n", __LINE__);
        examine(last_position(begin, end, 6) == begin + 15, "last_position is failed at the line: %d\n", __LINE__);
        examine(my_lower_bound(begin, end, 8) == end, "my_lower_bound is failed at the line: %d\n", __LINE__);
        examine(last_position(begin, end, 8) == end, "last_position is failed at the line: %d\n", __LINE__);
        auto result = search_in_sorted_array_with_duplication(begin, end, 1);
        examine(result.first == begin && result.second == begin, "search_in_sorted_array_with_duplication is failed at the line: %d\n", __LINE__);
        result = search_in_sorted_array_with_duplication(begin, end, 2);
        examine(result.first == begin + 1 && result.second == begin + 2, "search_in_sorted_array_with_duplication is failed at the line: %d\n", __LINE__);
        result = search_in_sorted_array_with_duplication(begin, end, 3);
        examine(result.first == begin + 3 && result.second == begin + 5, "search_in_sorted_array_with_duplication is failed at the line: %d\n", __LINE__);
        result = search_in_sorted_array_with_duplication(begin, end, 4);
        examine(result.first == begin + 6 && result.second == begin + 9, "search_in_sorted_array_with_duplication is failed at the line: %d\n", __LINE__);
        result = search_in_sorted_array_with_duplication(begin, end, 5);
        examine(result.first == end && result.second == end, "search_in_sorted_array_with_duplication is failed at the line: %d\n", __LINE__);
        result = search_in_sorted_array_with_duplication(begin, end, 6);
        examine(result.first == (begin + 10) && result.second == (begin + 15), "search_in_sorted_array_with_duplication is failed at the line: %d\n", __LINE__);
        result = search_in_sorted_array_with_duplication(begin, end, 0);
        examine(result.first == end && result.second == end, "search_in_sorted_array_with_duplication is failed at the line: %d\n", __LINE__);
        result = search_in_sorted_array_with_duplication(begin, end, 8);
        examine(result.first == end && result.second == end, "search_in_sorted_array_with_duplication is failed at the line: %d\n", __LINE__);
    }
}

int main()
{
    search_in_rotated_sorted_array_without_duplication_test();
    search_in_sorted_array_with_duplication_test();
    printf("OK\n");
    return 0;
}
