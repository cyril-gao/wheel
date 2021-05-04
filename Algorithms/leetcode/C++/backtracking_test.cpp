#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <algorithm>
#include <iterator>
#include <set>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>

#include "check.h"

/*
Given an array of distinct integers candidates and a target integer target, return a list of all unique combinations of candidates where the chosen numbers sum to target. You may return the combinations in any order.

The same number may be chosen from candidates an unlimited number of times. Two combinations are unique if the frequency of at least one of the chosen numbers is different.

It is guaranteed that the number of unique combinations that sum up to target is less than 150 combinations for the given input.

Constraints:
    1 <= candidates.length <= 30
    1 <= candidates[i] <= 200
    All elements of candidates are distinct.
    1 <= target <= 500
*/
namespace
{
    template <typename T>
    void next_element(
        std::vector<T> const& input, size_t index, T target,
        std::vector<T>& selected,
        std::vector<std::vector<T>>& result
    ) {
        if (target != 0) {
            for (size_t i = index, n = input.size(); i < n && input[i] <= target; ++i) {
                selected.push_back(input[i]);
                next_element(input, i, target - input[i], selected, result);
                selected.pop_back();
            }
        } else {
            result.push_back(selected);
        }
    }
}

template <typename T>
std::vector<std::vector<T>> combination_sum(std::vector<T> const& candidates, T target)
{
    std::set<T> no_dup{candidates.cbegin(), candidates.cend()};
    std::vector<T> input{no_dup.cbegin(), no_dup.cend()};
    std::vector<T> selected;
    std::vector<std::vector<T>> retval;
    next_element(input, 0, target, selected, retval);
    return retval;
}

void combination_sum_test()
{
    {
        std::vector<int> candidates = {2, 3, 5};
        int target = 8;
        auto result = combination_sum(candidates, target);
        examine(result.size() == 3, "combination_sum is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> candidates = {2, 3, 5};
        int target = 1;
        auto result = combination_sum(candidates, target);
        examine(result.empty(), "combination_sum is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> candidates = {2};
        int target = 2;
        auto result = combination_sum(candidates, target);
        examine(result.size() == 1, "combination_sum is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> candidates = {1, 1};
        int target = 2;
        auto result = combination_sum(candidates, target);
        examine(result.size() == 1, "combination_sum is failed at the line: %d\n", __LINE__);
    }
}

/*
Given a string containing digits from 2-9 inclusive, return all possible letter combinations that the number could represent. Return the answer in any order.

A mapping of digit to letters (just like on the telephone buttons) is given below. Note that 1 does not map to any letters.
*/
namespace
{
    std::unordered_map<char, std::vector<char>> mapping_table = {
        {'2', {'a', 'b', 'c'}},
        {'3', {'d', 'e', 'f'}},
        {'4', {'g', 'h', 'i'}},
        {'5', {'j', 'k', 'l'}},
        {'6', {'m', 'n', 'o'}},
        {'7', {'p', 'q', 'r', 's'}},
        {'8', {'t', 'u', 'v'}},
        {'9', {'w', 'x', 'y', 'z'}}
    };

    std::vector<char> empty;

    std::vector<char> const& get_mapping(char c)
    {
        auto i = mapping_table.find(c);
        if (i != mapping_table.end()) {
            return i->second;
        }
        return empty;
    }

    void next_element(
        std::string const& digits,
        size_t index,
        std::vector<char>& selected,
        std::vector<std::string>& result
    ) {
        if (index < digits.length()) {
            decltype(auto) mapping = get_mapping(digits[index]);
            if (!mapping.empty()) {
                for (char c : mapping) {
                    selected.push_back(c);
                    next_element(digits, index + 1, selected, result);
                    selected.pop_back();
                }
            } else {
                next_element(digits, index + 1, selected, result);
            }
        } else {
            selected.push_back('\0');
            result.emplace_back(&selected[0]);
            selected.pop_back();
        }
    }
}

std::vector<std::string> letter_combinations(std::string const& digits)
{
    std::vector<std::string> retval;
    if (!digits.empty()) {
        std::vector<char> selected;
        next_element(digits, 0, selected, retval);
    }
    return retval;
}

void letter_combinations_test()
{
    {
        auto result = letter_combinations("23");
        std::unordered_set<std::string> no_dup{result.begin(), result.end()};
        examine(no_dup.size() == 9, "letter_combinations is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = letter_combinations("279");
        std::unordered_set<std::string> no_dup{result.begin(), result.end()};
        examine(no_dup.size() == 48, "letter_combinations is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = letter_combinations("");
        examine(result.empty(), "letter_combinations is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = letter_combinations("2");
        std::unordered_set<std::string> no_dup{result.begin(), result.end()};
        examine(no_dup.size() == 3, "letter_combinations is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = letter_combinations("7");
        std::unordered_set<std::string> no_dup{result.begin(), result.end()};
        examine(no_dup.size() == 4, "letter_combinations is failed at the line: %d\n", __LINE__);
    }
}


/*
Given a collection of candidate numbers (candidates) and a target number (target), find all unique combinations in candidates where the candidate numbers sum to target.

Each number in candidates may only be used once in the combination.

Note: The solution set must not contain duplicate combinations.
*/
namespace only_once
{
    template <typename T>
    struct Hash
    {
        std::size_t operator()(std::vector<T> const& vt) const noexcept
        {
            std::hash<T> hasher;
            const size_t mask = 37;
            size_t retval = 0;
            for (auto t : vt) {
                retval = retval * mask + hasher(t);
            }
            return retval;
        }
    };

    template <typename T>
    void next_element(
        std::vector<T> const& input, size_t index,
        T target,
        std::vector<T>& selected,
        std::unordered_set<std::vector<T>, Hash<T>>& result
    ) {
        if (target != 0) {
            for (size_t i = index, n = input.size(); i < n && input[i] <= target; ++i) {
                selected.push_back(input[i]);
                next_element(input, i + 1, target - input[i], selected, result);
                selected.pop_back();
            }
        } else {
            result.insert(selected);
        }
    }

    template <typename T>
    std::vector<std::vector<T>> combination_sum(std::vector<T> const& candidates, T target)
    {
        std::vector<std::vector<T>> retval;
        if (!candidates.empty()) {
            auto input{candidates};
            std::sort(input.begin(), input.end());
            std::unordered_set<std::vector<T>, Hash<T>> result;
            std::vector<T> selected;
            next_element(input, 0, target, selected, result);
            retval.assign(result.begin(), result.end());
        }
        return retval;
    }

    void combination_sum_test()
    {
        {
            std::vector<int> candidates = {2, 5, 2, 1, 2};
            int target = 5;
            auto result = combination_sum(candidates, target);
            examine(result.size() == 2, "combination_sum(each candidate is used only once) is failed at the line: %d\n", __LINE__);
        }
        {
            std::vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
            int target = 8;
            auto result = combination_sum(candidates, target);
            examine(result.size() == 4, "combination_sum(each candidate is used only once) is failed at the line: %d\n", __LINE__);
        }
    }
}


int main()
{
    combination_sum_test();
    letter_combinations_test();
    only_once::combination_sum_test();
    printf("OK\n");
    return 0;
}
