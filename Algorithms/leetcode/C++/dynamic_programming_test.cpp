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


/*
Given two strings word1 and word2, return the minimum number of operations required to convert word1 to word2.

You have the following three operations permitted on a word:
    Insert a character
    Delete a character
    Replace a character
*/

int calculate_minimum_distance(std::string const& word1, std::string const& word2)
{
    int retval = 0;
    int m = static_cast<int>(word1.length());
    int n = static_cast<int>(word2.length());
    if (m > 0 && n > 0) {
        std::vector<std::vector<int>> cache(m + 1, std::vector<int>(n + 1));
        auto calculate_distance = [&](int i, int j) {
            int i1 = i + 1, j1 = j + 1;
            int v = cache[i1][j1];
            if (word1[i] != word2[j]) {
                ++v;
            }
            return std::min({cache[i][j1] + 1, cache[i1][j] + 1, v});
        };
        for (int i = m - 1, j = 1; i >= 0; --i, ++j) {
            cache[i][n] = j;
        }
        for (int i = n - 1, j = 1; i >= 0; --i, ++j) {
            cache[m][i] = j;
        }
        for (int row = m - 1, col = n - 1; row >= 0 && col >= 0; --row, --col) {
            cache[row][col] = calculate_distance(row, col);
            if (row > 0) {
                for (int i = row - 1; i >= 0; --i) {
                    cache[i][col] = calculate_distance(i, col);
                }
            }
            if (col > 0) {
                for (int j = col - 1; j >= 0; --j) {
                    cache[row][j] = calculate_distance(row, j);
                }
            }
        }
        retval = cache[0][0];
    } else {
        retval = std::max(m, n);
    }
    return retval;
}

namespace less_memory
{
    int calculate_minimum_distance(std::string const& word1, std::string const& word2)
    {
        int retval = 0;
        int m = static_cast<int>(word1.length());
        int n = static_cast<int>(word2.length());
        if (m > 0 && n > 0) {
            std::vector<std::vector<int>> horizontal_cache(2, std::vector<int>(n + 1, 0));
            std::vector<std::vector<int>> vertical_cache(2, std::vector<int>(m + 1, 0));
            int common = 0;
            int previous = 0;
            auto calculate_distance_for_cross = [&](int i, int j, int common, int previous) {
                if (word1[i] != word2[j]) {
                    ++common;
                }
                return std::min({common, vertical_cache[previous][i] + 1, horizontal_cache[previous][j] + 1});
            };
            auto calculate_distance_vertically = [&](int i, int j, int current, int previous) {
                int v = vertical_cache[previous][i+1];
                if (word1[i] != word2[j]) {
                    ++v;
                }
                return std::min({v, vertical_cache[current][i+1] + 1, vertical_cache[previous][i] + 1});
            };
            auto calculate_distance_horizontally = [&](int i, int j, int current, int previous) {
                int v = horizontal_cache[previous][j+1];
                if (word1[i] != word2[j]) {
                    ++v;
                }
                return std::min({v, horizontal_cache[current][j+1] + 1, horizontal_cache[previous][j] + 1});
            };
            for (int i = m - 1, j = 1; i >= 0; --i, ++j) {
                vertical_cache[0][i] = j;
            }
            for (int i = n - 1, j = 1; i >= 0; --i, ++j) {
                horizontal_cache[0][i] = j;
            }
            for (int row = m - 1, col = n - 1; row >= 0 && col >= 0; --row, --col) {
                int current = (previous + 1) & 1;
                common = calculate_distance_for_cross(row, col, common, previous);
                vertical_cache[current][row] = common;
                horizontal_cache[current][col] = common;
                if (row > 0) {
                    for (int i = row - 1; i >= 0; --i) {
                        vertical_cache[current][i] = calculate_distance_vertically(i, col, current, previous);
                    }
                }
                if (col > 0) {
                    for (int i = col - 1; i >= 0; --i) {
                        horizontal_cache[current][i] = calculate_distance_horizontally(row, i, current, previous);
                    }
                }
                previous = current;
            }
            retval = m > n ? vertical_cache[previous][0] : m < n ? horizontal_cache[previous][0] : common;
        } else {
            retval = std::max(m, n);
        }
        return retval;
    }
}

void minimum_distance_test()
{
    {
        auto result = calculate_minimum_distance("horse", "ros");
        examine(result == 3, "calculate_minimum_distance is failed at the line: %d\n", __LINE__);
        result = less_memory::calculate_minimum_distance("horse", "ros");
        examine(result == 3, "less_memory::calculate_minimum_distance is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = calculate_minimum_distance("ros", "horse");
        examine(result == 3, "calculate_minimum_distance is failed at the line: %d\n", __LINE__);
        result = less_memory::calculate_minimum_distance("ros", "horse");
        examine(result == 3, "less_memory::calculate_minimum_distance is failed at the line: %d\n", __LINE__);
    }
    {
        auto result = calculate_minimum_distance("intention", "execution");
        examine(result == 5, "calculate_minimum_distance is failed at the line: %d\n", __LINE__);
        result = less_memory::calculate_minimum_distance("intention", "execution");
        examine(result == 5, "less_memory::calculate_minimum_distance is failed at the line: %d\n", __LINE__);
    }
}


int main()
{
    generate_parenthesis_test();
    longest_palindromic_substring_test();
    minimum_distance_test();
    printf("OK\n");
    return 0;
}
