#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <iterator>
#include <random>
#include <algorithm>
#include <vector>
#include "check.h"

/*
Given two sorted arrays nums1 and nums2 of size m and n respectively, return the median of the two sorted arrays.

Example 1:
Input: nums1 = [1,3], nums2 = [2]
Output: 2.00000
Explanation: merged array = [1,2,3] and median is 2.

Example 2:
Input: nums1 = [1,2], nums2 = [3,4]
Output: 2.50000
Explanation: merged array = [1,2,3,4] and median is (2 + 3) / 2 = 2.5.

Example 3:
Input: nums1 = [0,0], nums2 = [0,0]
Output: 0.00000

Example 4:
Input: nums1 = [], nums2 = [1]
Output: 1.00000

Example 5:
Input: nums1 = [2], nums2 = []
Output: 2.00000
*/

namespace
{
    template <typename I>
    I my_binary_search(I begin, I end, typename std::iterator_traits<I>::value_type v)
    {
        I mid = end;
        while (begin < end)
        {
            mid = begin + (end - begin) / 2;
            if (*mid > v)
            {
                end = mid;
                mid = begin;
            }
            else if (*mid < v)
            {
                begin = mid + 1;
                mid = end;
            }
            else
            {
                break;
            }
        }
        return mid;
    }

    template <typename I1, typename I2>
    auto find_item_in_two_sorted_ranges(
        I1 b1, I1 e1, I2 b2, I2 e2, size_t k
    ) {
        while (b1 < e1 && b2 < e2)
        {
            I1 m1 = b1 + (e1 - b1) / 2;
            I2 m2 = b2 + (e2 - b2) / 2;
            if (*m1 <= *m2)
            {
                auto i = my_binary_search(b2, e2, *m1);
                size_t j = m1 - b1;
                j += (i - b2);
                if (j != k)
                {
                    if (j < k)
                    {
                        k -= j;
                        --k;
                        b1 = m1 + 1;
                        b2 = i;
                    }
                    else
                    {
                        e1 = m1;
                        e2 = i;
                    }
                }
                else
                {
                    return *m1;
                }
            }
            else
            {
                auto i = my_binary_search(b1, e1, *m2);
                size_t j = m2 - b2;
                j += (i - b1);
                if (j != k)
                {
                    if (j < k)
                    {
                        k -= j;
                        --k;
                        b1 = i;
                        b2 = m2 + 1;
                    }
                    else
                    {
                        e1 = i;
                        e2 = m2;
                    }
                }
                else
                {
                    return *m2;
                }
            }
        }
        if (b1 < e1)
        {
            return *(b1 + k);
        }
        if (b2 < e2)
        {
            return *(b2 + k);
        }
        assert(false);
    }
}

template <typename I1, typename I2>
double get_median_in_two_sorted_ranges(
    I1 b1, I1 e1, I2 b2, I2 e2)
{
    auto n1 = std::distance(b1, e1);
    auto n2 = std::distance(b2, e2);
    if (n1 > 0 && n2 > 0)
    {
        auto n = n1 + n2;
        if ((n & 1) == 0)
        {
            auto i = n / 2, j = i - 1;
            return static_cast<double>(
                find_item_in_two_sorted_ranges(b1, e1, b2, e2, i) +
                find_item_in_two_sorted_ranges(b1, e1, b2, e2, j)
            ) / 2.0;
        }
        else
        {
            return static_cast<double>(
                find_item_in_two_sorted_ranges(b1, e1, b2, e2, n / 2));
        }
    }
    else
    {
        auto get_median = [](auto begin, auto end, auto n) {
            if ((n & 1) == 0)
            {
                auto i = n / 2, j = i - 1;
                return static_cast<double>(*(begin + i) + *(begin + j)) / 2.0;
            }
            else
            {
                return static_cast<double>(*(begin + n / 2));
            }
        };
        double retval = 0;
        if (n1 > 0)
        {
            retval = get_median(b1, e1, n1);
        }
        else if (n2 > 0)
        {
            retval = get_median(b2, e2, n2);
        }
        return retval;
    }
}

int main()
{
    {
        std::vector<int> nums1 = {1, 3}, nums2 = {2};
        auto retval = get_median_in_two_sorted_ranges(nums1.begin(), nums1.end(), nums2.begin(), nums2.end());
        examine(retval == 2.0, "get_median_in_two_sorted_ranges is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums1 = {1, 2}, nums2 = {3, 4};
        auto retval = get_median_in_two_sorted_ranges(nums1.begin(), nums1.end(), nums2.begin(), nums2.end());
        examine(retval == 2.5, "get_median_in_two_sorted_ranges is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums1 = {0, 0}, nums2 = {0, 0};
        auto retval = get_median_in_two_sorted_ranges(nums1.begin(), nums1.end(), nums2.begin(), nums2.end());
        examine(retval == 0, "get_median_in_two_sorted_ranges is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums1 = {}, nums2 = {1};
        auto retval = get_median_in_two_sorted_ranges(nums1.begin(), nums1.end(), nums2.begin(), nums2.end());
        examine(retval == 1.0, "get_median_in_two_sorted_ranges is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums1 = {2}, nums2 = {};
        auto retval = get_median_in_two_sorted_ranges(nums1.begin(), nums1.end(), nums2.begin(), nums2.end());
        examine(retval == 2.0, "get_median_in_two_sorted_ranges is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums1 = {1, 3}, nums2 = {};
        auto retval = get_median_in_two_sorted_ranges(nums1.begin(), nums1.end(), nums2.begin(), nums2.end());
        examine(retval == 2.0, "get_median_in_two_sorted_ranges is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums1 = {}, nums2 = {1, 3};
        auto retval = get_median_in_two_sorted_ranges(nums1.begin(), nums1.end(), nums2.begin(), nums2.end());
        examine(retval == 2.0, "get_median_in_two_sorted_ranges is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums = {1, 2, 2, 3, 3, 3, 4, 4, 4, 4, 5, 5, 5, 5, 5, 6, 6, 6, 6, 6, 6, 7, 7, 7, 7, 7, 7, 7};
        std::random_device rd;
        std::mt19937 g(rd());
        double expectation = 5.0;
        auto begin = nums.begin();
        auto end = nums.end();
        for (int i = 0; i < 100; ++i)
        {
            auto mid = begin;
            for (int n = static_cast<int>(nums.size()); n >= 0; --n, mid != end ? ++mid : mid)
            {
                std::shuffle(nums.begin(), nums.end(), g);
                std::sort(begin, mid);
                std::sort(mid, end);
                auto retval = get_median_in_two_sorted_ranges(begin, mid, mid, end);
                examine(retval == expectation, "get_median_in_two_sorted_ranges is failed\n");
            }
        }
    }
    printf("OK\n");
    return 0;
}
