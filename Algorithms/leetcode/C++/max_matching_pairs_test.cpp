#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <algorithm>
#include <iterator>
#include <memory>
#include <string>
#include <set>
#include <unordered_set>
#include <unordered_map>
#include <vector>

#include "check.h"

/*
Given two strings s and t of length N, find the maximum number of possible matching pairs in strings s
and t after swapping exactly two characters within s.

A swap is switching s[i] and s[j], where s[i] and s[j] denotes the character that is present at the ith
and jth index of s, respectively. The matching pairs of the two strings are defined as the number of
indices for which s[i] and t[i] are equal.

Note: This means you must swap two characters at different indices.

Signature
size_t max_matching_pairs(std::string const& s, std::string const& t)
Input
s and t are strings of length N
N is between 2 and 1,000,000
Output
Return an integer denoting the maximum number of matching pairs

Example 1
s = "abcd"
t = "adcb"
output = 4
Explanation:
Using 0-based indexing, and with i = 1 and j = 3, s[1] and s[3] can be swapped, making it  "adcb".
Therefore, the number of matching pairs of s and t will be 4.


Example 2
s = "mno"
t = "mno"
output = 1
Explanation:
Two indices have to be swapped, regardless of which two it is, only one letter will remain the same.
If i = 0 and j=1, s[0] and s[1] are swapped, making s = "nmo", which shares only "o" with t.
*/

size_t max_matching_pairs(std::string const& s, std::string const& t)
{
    size_t retval = 0;
    bool finally = false;
    size_t count_of_mismatching = 0;
    int64_t increment = 0;

    std::unordered_map<char, std::unordered_set<char>> map;
    std::unordered_set<char> common;
    std::set<char> sources, targets;
    for (size_t i = 0, n = std::min(s.length(), t.length()); i < n; ++i) {
        auto from = s[i];
        auto to = t[i];
        if (from == to) {
            common.insert(from);
            ++retval;
        } else if (!finally) {
            ++count_of_mismatching;
            sources.insert(from);
            targets.insert(to);
            auto j = map.find(from);
            if (j == map.end()) {
                map.insert({from, {to}});
            } else {
                j->second.insert(to);
            }
            j = map.find(to);
            if (j != map.end()) {
                if (j->second.find(from) != j->second.end()) {
                    increment = 2;
                    finally = true;
                }
            }
        }
    }
    if (!finally) {
        if (count_of_mismatching >= 2) {
            std::vector<char> intersection;
            std::set_intersection(
                sources.begin(), sources.end(),
                targets.begin(), targets.end(),
                std::back_inserter(intersection)
            );
            if (!intersection.empty()) {
                increment = 1;
            }
        } else if (count_of_mismatching == 1) {
            char c = *targets.begin();
            if (common.find(c) == common.end()) {
                increment = -1;
            }
        } else {
            assert(count_of_mismatching == 0);
            increment = -2;
        }
    }
    return static_cast<size_t>(static_cast<int64_t>(retval) + increment);
}

int main()
{
    try {
        {
            auto result = max_matching_pairs("abcd", "adcb");
            examine(result == 4, "max_matching_pairs is failed at the line: %d\n", __LINE__);
        }
        {
            auto result = max_matching_pairs("abce", "abdc");
            examine(result == 3, "max_matching_pairs is failed at the line: %d\n", __LINE__);
        }
        {
            auto result = max_matching_pairs("abcd", "abef");
            examine(result == 2, "max_matching_pairs is failed at the line: %d\n", __LINE__);
        }
        {
            auto result = max_matching_pairs("abcd", "abcc");
            examine(result == 3, "max_matching_pairs is failed at the line: %d\n", __LINE__);
        }
        {
            auto result = max_matching_pairs("abcf", "abdc");
            examine(result == 3, "max_matching_pairs is failed at the line: %d\n", __LINE__);
        }
        {
            auto result = max_matching_pairs("abcf", "abcg");
            examine(result == 2, "max_matching_pairs is failed at the line: %d\n", __LINE__);
        }
    } catch (std::exception const& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }
    return 0;
}
