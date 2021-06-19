#include <stdio.h>
#include <stdint.h>

#include <vector>
#include <counting_sort.h>
#include "check.h"


/*
Given an unsorted array of integers nums, return the length of the longest consecutive elements sequence.

Follow up: Could you implement the O(n) solution? 


Example 1:
Input: nums = [100,4,200,1,3,2]
Output: 4
Explanation: The longest consecutive elements sequence is [1, 2, 3, 4]. Therefore its length is 4.

Example 2:
Input: nums = [0,3,7,2,5,8,4,6,0,1]
Output: 9
*/

int longest_consecutive(std::vector<int>& nums)
{
    integer_sort(nums.begin(), nums.end());
    int retval = 0;
#if 1
    for (auto i = nums.cbegin(), ie = nums.cend(); i != ie;) {
        int count = 1;
        for (auto j = i++; i != ie; j = i++) {
            auto diff = *i - *j;
            if (diff < 2) {
                count += (diff & 1);
            } else {
                break;
            }
        }
        if (count > retval) {
            retval = count;
        }
    }
#else
    for (int i = 0, n = static_cast<int>(nums.size()); i < n;) {
        int j = i + 1;
        int c = 1;
        while (j < n) {
            int v = nums[j] - nums[j-1];
            if (v < 2) {
                if (v == 1) {
                    ++c;
                }
                ++j;
            } else {
                break;
            }
        }
        if (c > retval) {
            retval = c;
        }
        i = j;
    }
#endif
    return retval;
}

int main()
{
    {
        std::vector<int> nums = {100, 3, 4, 2, 200, 201, 203, 204, 205, 207, 3, 2, 2, 4, 1, 1};
        examine(longest_consecutive(nums) == 4, "longest_consecutive is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums = {0, 3, 7, 3, 7, 2, 8, 5, 8, 4, 6, 0, 6, 0, 1, 18, 19, 20, 21};
        examine(longest_consecutive(nums) == 9, "longest_consecutive is failed at the line: %d\n", __LINE__);
    }
    return 0;
}
