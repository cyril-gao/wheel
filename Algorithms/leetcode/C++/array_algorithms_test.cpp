#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <algorithm>
#include <iterator>
#include <vector>

#include "check.h"

/*
Given an unsorted integer array nums, find the smallest missing positive integer.
*/

int first_missing_positive(std::vector<int>& nums)
{
    int n = static_cast<int>(nums.size());
    for (int i = 0; i < n; ++i) {
        int v = nums[i];
        if (v > 0) {
            for (int j = v - 1; j >= 0 && j < n && nums[j] != (j + 1);) {
                int k = nums[j] - 1;
                nums[j] = j + 1;
                j = k;
            }
        }
    }
    int retval = n + 1;
    for (int i = 0; i < n; ++i) {
        if ((nums[i] - 1) != i) {
            retval = i + 1;
            break;
        }
    }
    return retval;
}

void first_missing_positive_test()
{
    {
        std::vector<int> nums = {1, 2, 0};
        auto result = first_missing_positive(nums);
        examine(result == 3, "first_missing_positive is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums = {1, 2, 3};
        auto result = first_missing_positive(nums);
        examine(result == 4, "first_missing_positive is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums = {7, 8, 9, 11, 12};
        auto result = first_missing_positive(nums);
        examine(result == 1, "first_missing_positive is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums = {3, 4, -1, 1};
        auto result = first_missing_positive(nums);
        examine(result == 2, "first_missing_positive is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums = {3, 4, -1, 5, 2, 7, 6, 9, 10, 1};
        auto result = first_missing_positive(nums);
        examine(result == 8, "first_missing_positive is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums = {2147483647, 2147483646, 2147483645, 3, 2, 1, -1, 0, -2147483648};
        auto result = first_missing_positive(nums);
        examine(result == 4, "first_missing_positive is failed at the line: %d\n", __LINE__);
    }
}

/*
Given an array nums with n objects colored red, white, or blue, sort them in-place so that objects of the same color are adjacent, with the colors in the order red, white, and blue.

We will use the integers 0, 1, and 2 to represent the color red, white, and blue, respectively.
*/
void sort_colors(std::vector<int>& colors)
{
    int n = static_cast<int>(colors.size());
    int zero = -1;
    auto begin = colors.begin();
    auto two = begin + n;
    for (auto i = begin; i < two;) {
        int c = *i;
        if (c <= 1) {
            if (c < 1) {
                ++zero;
                std::iter_swap(begin + zero, i);
            }
            ++i;
        } else {
            --two;
            std::iter_swap(two, i);
        }
    }
}

void sort_colors_test()
{
    {
        std::vector<int> colors = {2, 1, 0};
        sort_colors(colors);
        examine(colors[0] == 0 && colors[1] == 1 && colors[2] == 2, "sort_colors is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> colors = {1, 0};
        sort_colors(colors);
        examine(colors[0] == 0 && colors[1] == 1, "sort_colors is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> colors = {0};
        sort_colors(colors);
        examine(colors[0] == 0, "sort_colors is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> colors = {1};
        sort_colors(colors);
        examine(colors[0] == 1, "sort_colors is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> colors = {2};
        sort_colors(colors);
        examine(colors[0] == 2, "sort_colors is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> colors = {};
        sort_colors(colors);
        examine(colors.empty(), "sort_colors is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> colors = {2, 0};
        sort_colors(colors);
        examine(colors[0] == 0 && colors[1] == 2, "sort_colors is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> colors = {2, 0, 2, 1, 1, 1, 0, 2, 1, 0, 2, 1, 0, 0, 0, 1, 1, 2, 2, 2, 1, 0, 0, 1, 2};
        sort_colors(colors);
        examine(std::is_sorted(colors.begin(), colors.end()), "sort_colors is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> colors = {0, 2, 0, 2, 1, 1, 1, 0, 2, 1, 0, 2, 1, 0, 0, 0, 1, 1, 2, 2, 2, 1, 0, 0, 1, 2};
        sort_colors(colors);
        examine(std::is_sorted(colors.begin(), colors.end()), "sort_colors is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> colors = {1, 2, 0, 2, 1, 1, 1, 0, 2, 1, 0, 2, 1, 0, 0, 0, 1, 1, 2, 2, 2, 1, 0, 0, 1, 2};
        sort_colors(colors);
        examine(std::is_sorted(colors.begin(), colors.end()), "sort_colors is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> colors = {2, 0, 2, 1, 1, 1, 0, 2, 1, 0, 2, 1, 0, 0, 0, 1, 1, 2, 2, 2, 1, 0, 0, 1, 2, 0};
        sort_colors(colors);
        examine(std::is_sorted(colors.begin(), colors.end()), "sort_colors is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> colors = {2, 0, 2, 1, 1, 1, 0, 2, 1, 0, 2, 1, 0, 0, 0, 1, 1, 2, 2, 2, 1, 0, 0, 1, 2, 1};
        sort_colors(colors);
        examine(std::is_sorted(colors.begin(), colors.end()), "sort_colors is failed at the line: %d\n", __LINE__);
    }
}

int main()
{
    first_missing_positive_test();
    sort_colors_test();
    printf("OK\n");
    return 0;
}
