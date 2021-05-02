#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

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

int main()
{
    first_missing_positive_test();
    printf("OK\n");
    return 0;
}
