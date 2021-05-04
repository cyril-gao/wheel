#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <algorithm>
#include <iterator>
#include <set>
#include <string>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <utility>

#include "check.h"

/*
Given n pairs of parentheses, write a function to generate all combinations of well-formed parentheses.
*/

std::vector<std::string> generate_parenthesis(size_t n)
{
    std::vector<std::string> retval;
    if (n > 0) {
        std::vector<std::unordered_set<std::string>> cache(n + 1);
        cache[1].insert("()");
        for (size_t i = 2; i <= n; ++i) {
            for (size_t left = 1, right = i - left; right > 0; ++left, --right) {
                for (auto const& j : cache[left]) {
                    for (auto const& k : cache[right]) {
                        cache[i].insert(j + k);
                    }
                }
                for (auto const& k : cache[right]) {
                    std::string p(left, '(');
                    p.append(k);
                    p.append(left, ')');
                    cache[i].insert(std::move(p));
                }
            }
        }
        retval.assign(cache.back().begin(), cache.back().end());
    }
    return retval;
}

void generate_parenthesis_test()
{
    {
        auto result = generate_parenthesis(1);
        examine(result.size() == 1, "generate_parenthesis is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = generate_parenthesis(2);
        examine(result.size() == 2, "generate_parenthesis is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = generate_parenthesis(3);
        examine(result.size() == 5, "generate_parenthesis is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = generate_parenthesis(4);
        examine(result.size() == 14, "generate_parenthesis is failed at the line: %d\n", __LINE__);
    }
}


/*
Given a string s, return the longest palindromic substring in s.
*/

std::string get_longest_palindromic_substring(std::string const& input)
{
    using position_t = std::pair<size_t, size_t>;
    size_t n = input.length();
    std::string retval;
    if (n > 0) {
        retval.push_back(input[0]);
        size_t ml = 1;
        std::vector<position_t> cache;
        for (size_t i = 0; i < n; ++i) {
            cache.emplace_back(i, i);
        }
        for (size_t i = 0, j = 1; j < n; ++i, ++j) {
            if (input[i] == input[j]) {
                if (ml < 2) {
                    ml = 2;
                    retval.assign(&input[i], &input[i + 2]);
                }
                cache.emplace_back(i, j);
            }
        }
        for (size_t n_1 = n - 1; !cache.empty();) {
            std::vector<position_t> next;
            for (auto position : cache) {
                if (
                    position.first > 0 && position.second < n_1 &&
                    input[--position.first] == input[++position.second]
                ) {
                    size_t l = position.second - position.first + 1;
                    if (ml < l) {
                        ml = l;
                        retval.assign(&input[position.first], &input[position.second] + 1);
                    }
                    next.push_back(position);
                }
            }
            cache.swap(next);
        }
    }
    return retval;
}

void longest_palindromic_substring_test()
{
    {
        auto result = get_longest_palindromic_substring("babad");
        examine(result.length() == 3, "get_longest_palindromic_substring is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = get_longest_palindromic_substring("cbbd");
        examine(result.length() == 2, "get_longest_palindromic_substring is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = get_longest_palindromic_substring("abcdef");
        examine(result.length() == 1, "get_longest_palindromic_substring is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = get_longest_palindromic_substring("a");
        examine(result.length() == 1, "get_longest_palindromic_substring is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = get_longest_palindromic_substring("abcdcb");
        examine(result.length() == 5, "get_longest_palindromic_substring is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = get_longest_palindromic_substring("abcdcba");
        examine(result.length() == 7, "get_longest_palindromic_substring is failed at the line: %d\n", __LINE__);
    }
}


int main()
{
    generate_parenthesis_test();
    longest_palindromic_substring_test();
    printf("OK\n");
    return 0;
}
