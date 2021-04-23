#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include <algorithm>
#include <chrono>
#include <vector>
#include <string>

#include "check.h"


/*
Given two strings s and t, return the number of distinct subsequences of s which equals t.
A string's subsequence is a new string formed from the original string by deleting some (can be none) of the characters without disturbing the relative positions of the remaining characters. (i.e., "ACE" is a subsequence of "ABCDE" while "AEC" is not).
It's guaranteed the answer fits on a 32-bit signed integer.
 
Example 1:
Input: s = "rabbbit", t = "rabbit"
Output: 3
Explanation:
As shown below, there are 3 ways you can generate "rabbit" from S.
rabbbit
rabbbit
rabbbit

Example 2:
Input: s = "babgbag", t = "bag"
Output: 5
Explanation:
As shown below, there are 5 ways you can generate "bag" from S.
babgbag
babgbag
babgbag
babgbag
babgbag
*/

namespace
{
    class Graph
    {
        std::vector<std::vector<size_t>> m_adjacency_list;
    public:
        Graph(size_t V) : m_adjacency_list(V) {}
        void add_adge(size_t from, size_t to)
        {
            m_adjacency_list[from].push_back(to);
        }
        std::vector<size_t> const& adj(size_t v) const
        {
            return m_adjacency_list[v];
        }
        size_t size() const { return m_adjacency_list.size(); }
    };
}


namespace v1
{
    namespace details
    {
        std::vector<size_t> filter_neighbours(
            Graph const& graph,
            std::string const& input, size_t index_in_input,
            std::string const& word, size_t index_in_word,
            size_t & count
        ) {
            assert(input[index_in_input] == word[index_in_word]);
            size_t next_index_in_word = index_in_word + 1;
            std::vector<size_t> retval;

            if (next_index_in_word < word.length()) {
                char c = word[next_index_in_word];
                retval.reserve(8);
                for (auto v : graph.adj(index_in_input)) {
                    if (input[v] == c) {
                        retval.push_back(v);
                    }
                }
            } else {
                ++count;
            }
            return retval;
        }

        void dfs(
            Graph const& graph,
            std::string const& input, size_t index_in_input,
            std::string const& word, size_t index_in_word,
            std::vector<bool>& visited,
            size_t & count
        ) {
            visited[index_in_input] = true;
            for (auto v : filter_neighbours(graph, input, index_in_input, word, index_in_word, count)) {
                if (!visited[v]) {
                    dfs(graph, input, v, word, index_in_word+1, visited, count);
                }
            }
            visited[index_in_input] = false;
        }

        void search(
            Graph const& graph,
            std::string const& input,
            std::string const& word,
            size_t & count
        ) {
            char c = word[0];
            for (size_t i = 0, last = input.length() + 1 - word.length(); i <= last; ++i) {
                if (input[i] == c) {
                    std::vector<bool> visited(graph.size(), false);
                    dfs(graph, input, i, word, 0, visited, count);
                }
            }
        }
    }

    size_t get_number_of_distinct_subsequences(std::string const& s, std::string const& t)
    {
        size_t retval = 0;
        size_t sn = s.length();
        size_t tn = t.length();
        if (sn >= tn && tn > 0) {
            Graph graph(sn);
            for (size_t i = 0, sn_1 = sn - 1; i < sn_1; ++i) {
                for (size_t j = i + 1; j < sn; ++j) {
                    graph.add_adge(i, j);
                }
            }
            details::search(graph, s, t, retval);
        }
        return retval;
    }
}

namespace v2
{
    namespace details
    {
        size_t count_matches(
            std::string const& s, ptrdiff_t sn,
            std::string const& t, ptrdiff_t tn
        ) {
            assert(sn >= tn);
            std::vector<std::vector<size_t>> cache(2, std::vector<size_t>(sn + 1, 1));
            ptrdiff_t current = 0;
            for (ptrdiff_t i = tn - 1, ii = 1; ii <= tn; --i, ++ii) {
                ptrdiff_t previous = current++;
                current %= 2;
                auto tc = t[i];
                ptrdiff_t j = sn - ii + 1;
                cache[current][j] = 0;
                while (j > i) {
                    ptrdiff_t k = j - 1;
                    size_t v = 0;
                    if (s[k] == tc) {
                        v = cache[previous][j];
                    }
                    v += cache[current][j];
                    cache[current][k] = v;
                    j = k;
                }
            }
            return cache[current][0];
        }
    }

    size_t get_number_of_distinct_subsequences(std::string const& s, std::string const& t)
    {
        size_t retval = 0;
        ptrdiff_t sn = s.length();
        ptrdiff_t tn = t.length();
        if (sn >= tn && tn > 0) {
            retval = details::count_matches(s, sn, t, tn);
        }
        return retval;
    }
}


int main()
{
    {
        std::string input = "babgbag", pattern = "bag";
        auto result = v1::get_number_of_distinct_subsequences(input, pattern);
        examine(result == 5, "v1::get_number_of_distinct_subsequences is failed at the line: %d\n", __LINE__);
        result = v2::get_number_of_distinct_subsequences(input, pattern);
        examine(result == 5, "v2::get_number_of_distinct_subsequences is failed at the line: %d\n", __LINE__);
    }
    {
        std::string input = "rabbbiit", pattern = "rabbit";
        auto result = v1::get_number_of_distinct_subsequences(input, pattern);
        examine(result == 6, "v1::get_number_of_distinct_subsequences is failed at the line: %d\n", __LINE__);
        result = v2::get_number_of_distinct_subsequences(input, pattern);
        examine(result == 6, "v2::get_number_of_distinct_subsequences is failed at the line: %d\n", __LINE__);
    }
    {
        std::string input = "acbdeccdceedceaceed", pattern = "bcdeea";
        auto result = v1::get_number_of_distinct_subsequences(input, pattern);
        examine(result == 6, "v1::get_number_of_distinct_subsequences is failed at the line: %d\n", __LINE__);
        result = v2::get_number_of_distinct_subsequences(input, pattern);
        examine(result == 6, "v2::get_number_of_distinct_subsequences is failed at the line: %d\n", __LINE__);
    }
    {
        std::string input = "adbdadbeecadeadeceecbcdabddddabcaa";
        std::string pattern = "bcdeedaa";
        auto result = v1::get_number_of_distinct_subsequences(input, pattern);
        examine(result == 324, "v1::get_number_of_distinct_subsequences is failed at the line: %d\n", __LINE__);
        result = v2::get_number_of_distinct_subsequences(input, pattern);
        examine(result == 324, "v2::get_number_of_distinct_subsequences is failed at the line: %d\n", __LINE__);
    }
    {
        std::string input = "adbdadeecadeadeccaeaabdabdbcdabddddabcaaadbabaaedeeddeaeebcdeabcaaaeeaeeabcddcebddebeebedaecccbdcbcedbdaeaedcdebeecdaaedaacadbdccabddaddacdddc";
        std::string pattern = "bcddceeeebecbc";
        {
            auto begin = std::chrono::system_clock::now();
            auto result = v1::get_number_of_distinct_subsequences(input, pattern);
            auto end = std::chrono::system_clock::now();
            double duration = std::chrono::duration<double>(end - begin).count();
            printf("v1: %f seconds\n", duration);
            examine(result == 700531452, "v1::get_number_of_distinct_subsequences is failed at the line: %d\n", __LINE__);
        }
        {
            auto begin = std::chrono::system_clock::now();
            auto result = v2::get_number_of_distinct_subsequences(input, pattern);
            auto end = std::chrono::system_clock::now();
            double duration = std::chrono::duration<double>(end - begin).count();
            printf("v2: %f seconds\n", duration);
            examine(result == 700531452, "v2::get_number_of_distinct_subsequences is failed at the line: %d\n", __LINE__);
        }

    }
    return 0;
}
