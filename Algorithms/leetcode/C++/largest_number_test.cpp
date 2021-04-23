#include <stdio.h>
#include <assert.h>

#include <algorithm>
#include <string>
#include <vector>

#include "check.h"

std::string generate_largest_number(std::vector<int> const& nums)
{
    std::vector<std::string> buf;
    buf.reserve(nums.size());
    for (const auto n : nums) {
        assert(n >= 0);
        buf.emplace_back(std::to_string(n));
    }
    std::sort(
        buf.begin(), buf.end(),
        [](const std::string& s1, const std::string& s2) {
            auto s1_begin = s1.begin(), s1_end = s1.end();
            auto s2_begin = s2.begin(), s2_end = s2.end();
            while (true) {
                auto original_s1_begin = s1_begin;
                auto original_s2_begin = s2_begin;
                while (s1_begin != s1_end && s2_begin != s2_end) {
                    if (*s1_begin != *s2_begin) {
                        return *s1_begin > *s2_begin;
                    } else {
                        ++s1_begin;
                        ++s2_begin;
                    }
                }
                if (s1_begin == s1_end && s2_begin == s2_end) {
                    return false;
                }
                if (s1_begin != s1_end) {
                    s2_begin = original_s2_begin;
                } else {
                    s1_begin = original_s1_begin;
                }
            }
        }
    );
    std::string retval;
    retval.reserve(buf.size() * 2);
    bool first_time = true;
    for (const auto & s : buf) {
        if (first_time) {
            first_time = false;
            if (s.length() == 1 && s[0] == '0') {
                retval.push_back('0');
                break;
            }
        }
        retval.insert(retval.end(), s.begin(), s.end());
    }
    return retval;
}

int main()
{
    {
    {
        std::vector<int> nums = {0, 0, 0, 0};
        auto r = generate_largest_number(nums);
        examine(r == "0", "generate_largest_number is failed at the line: %d\n", __LINE__);
    }
    }
    {
        std::vector<int> nums = {};
        auto r = generate_largest_number(nums);
        examine(r == "", "generate_largest_number is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums = {10, 2};
        auto r = generate_largest_number(nums);
        examine(r == "210", "generate_largest_number is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums = {1};
        auto r = generate_largest_number(nums);
        examine(r == "1", "generate_largest_number is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums = {10};
        auto r = generate_largest_number(nums);
        examine(r == "10", "generate_largest_number is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums = {3, 30, 34, 5, 9};
        auto r = generate_largest_number(nums);
        examine(r == "9534330", "generate_largest_number is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums = {3, 30, 34, 5, 9};
        auto r = generate_largest_number(nums);
        examine(r == "9534330", "generate_largest_number is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums = {4321043, 43210432, 4321, 5, 9};
        auto r = generate_largest_number(nums);
        examine(r == "954321432104343210432", "generate_largest_number is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> nums = {6543210, 65432, 654};
        auto r = generate_largest_number(nums);
        examine(r == "654654326543210", "generate_largest_number is failed at the line: %d\n", __LINE__);
    }
    return 0;
}
