#include <stdio.h>
#include <stdint.h>
#include <assert.h>

#include <chrono>
#include <stack>
#include <vector>
#include <string>

#include "check.h"


/*
Given strings s1, s2, and s3, find whether s3 is formed by an interleaving of s1 and s2.

An interleaving of two strings s and t is a configuration where they are divided into non-empty substrings such that:

s = s1 + s2 + ... + sn
t = t1 + t2 + ... + tm
|n - m| <= 1

The interleaving is s1 + t1 + s2 + t2 + s3 + t3 + ... or t1 + s1 + t2 + s2 + t3 + s3 + ...
Note: a + b is the concatenation of strings a and b.
 

Example 1:
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac"
Output: true


Example 2:
Input: s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc"
Output: false


Example 3:
Input: s1 = "", s2 = "", s3 = ""
Output: true

*/


namespace v1
{
    namespace details
    {
        template <typename I1, typename I2 = I1>
        bool equals(
            I1 begin1, I1 end1,
            I2 begin2, I2 end2
        ) {
            bool retval = true;
            while (begin1 != end1 && begin2 != end2) {
                if (*begin1++ != *begin2++) {
                    retval = false;
                    break;
                }
            }
            if (retval) {
                retval = (begin1 == end1) && (begin2 == end2);
            }
            return retval;
        }

        bool interleaving_check(
            std::string const& s1, size_t ns1,
            std::string const& s2, size_t ns2,
            std::string const& s3
        ) {
            std::vector<std::vector<std::vector<std::vector<bool>>>> cache(
                ns1,
                std::vector<std::vector<std::vector<bool>>>(
                    ns1,
                    std::vector<std::vector<bool>>(
                        ns2,
                        std::vector<bool>(ns2, false)
                    )
                )
            );
            for (size_t i = 0; i < ns1; ++i) {
                for (size_t j = 0; j < ns2; ++j) {
                    cache[i][i][j][j] = true;
                }
            }
            auto s1_begin = s1.begin();
            auto s2_begin = s2.begin();
            auto s3_begin = s3.begin();
            for (size_t i = 0; i < ns1; ++i) {
                auto s3_next = s3_begin + i;
                for (size_t j = 0, je = ns2 - 1; j < je; ++j) {
                    for (size_t k = j + 1; k < ns2; ++k) {
                        cache[i][i][j][k] = equals(s2_begin + j, s2_begin + k, s3_next + j, s3_next + k);
                    }
                }
            }
            for (size_t j = 0; j < ns2; ++j) {
                auto s3_next = s3_begin + j;
                for (size_t i = 0, ie = ns1 - 1; i < ie; ++i) {
                    for (size_t k = i + 1; k < ns1; ++k) {
                        cache[i][k][j][j] = equals(s1_begin + i, s1_begin + k, s3_next + i, s3_next + k);
                    }
                }
            }
            for (size_t d1 = 1; d1 < ns1; ++d1) {
                for (size_t d2 = 1; d2 < ns2; ++d2) {
                    for (size_t i = 0, ie = i + d1; ie < ns1; ++i, ++ie) {
                        for (size_t j = 0, je = j + d2; je < ns2; ++j, ++je) {
                            bool matched = false;
                            for (size_t ik = i; ik <= ie && !matched; ++ik) {
                                for (size_t jk = j; jk <= je; ++jk) {
                                    if (cache[i][ik][j][jk] && cache[ik][ie][jk][je]) {
                                        matched = true;
                                        break;
                                    }
                                    if (cache[i][i][j][jk] && cache[i][ik][jk][je] && cache[ik][ie][je][je]) {
                                        matched = true;
                                        break;
                                    }
                                }
                            }
                            cache[i][ie][j][je] = matched;
                        }
                    }
                }
            }
            return cache[0][ns1-1][0][ns2-1];
        }
    }

    bool is_interleaving(std::string const& s1, std::string const& s2, std::string const& s3)
    {
        size_t ns1 = s1.length();
        size_t ns2 = s2.length();
        size_t ns3 = s3.length();
        bool retval = false;
        if ((ns1 + ns2) == ns3) {
            if (ns1 != 0 && ns2 != 0) {
                retval = details::interleaving_check(s1, ns1 + 1, s2, ns2 + 1, s3);
            } else {
                if (ns1 == 0) {
                    retval = (s2 == s3);
                } else {
                    retval = (s1 == s3);
                }
            }
        }
        return retval;
    }
}

namespace v2
{
    namespace details
    {
        struct Indices
        {
            int64_t index_in_input;
            int64_t index_in_word;
            int64_t index_in_another;
        };

        struct State
        {
            int64_t index_in_word;
            int64_t index_in_another;
            std::stack<Indices> retry_points;
            bool matched;
        };

        int64_t get_neighbour(
            size_t current_vertex,
            std::string const& input, size_t input_size,
            std::string const& word,
            std::string const& another,
            State & state
        ) {
            int64_t retval = -1;

            size_t next_vertex = current_vertex + 1;
            if (next_vertex < input_size) {
                auto c = input[next_vertex];
                auto next_index_in_word = state.index_in_word + 1;
                auto next_index_in_another = state.index_in_another + 1;
                auto w = word[next_index_in_word];
                auto a = another[next_index_in_another];
                if (w == c) {
                    if (w == a) {
                        Indices indices = {
                            static_cast<int64_t>(current_vertex),
                            state.index_in_word,
                            state.index_in_another
                        };
                        state.retry_points.push(indices);
                    }
                    state.index_in_word = next_index_in_word;
                    retval = static_cast<int64_t>(next_vertex);
                } else if (a == c) {
                    state.index_in_another = next_index_in_another;
                    retval = static_cast<int64_t>(next_vertex);
                }
            } else {
                state.matched = true;
            }
            return retval;
        }

        void dfs(
            std::string const& input, size_t input_size,
            std::string const& word,
            std::string const& another,
            State & state
        ) {
            for (size_t current_vertex = 0; current_vertex < input_size;) {
                auto neighbour = get_neighbour(current_vertex, input, input_size, word, another, state);
                if (neighbour > 0) {
                    current_vertex = static_cast<size_t>(neighbour);
                } else {
                    if (!state.retry_points.empty()) {
                        decltype(auto) indices = state.retry_points.top();
                        current_vertex = indices.index_in_input + 1;
                        state.index_in_word = indices.index_in_word;
                        state.index_in_another = indices.index_in_another + 1;
                        state.retry_points.pop();
                    } else {
                        break;
                    }
                }
            }
        }

        bool interleaving_check(
            std::string const& s1,
            std::string const& s2,
            std::string const& s3, size_t ns3
        ) {
            State state = { 0 };
            state.index_in_word = 0;
            state.index_in_another = -1;
            state.matched = false;
            char c = s3[0];
            if (c == s1[0]) {
                if (c == s2[0]) {
                    Indices indices = {-1, -1, -1};
                    state.retry_points.push(indices);
                }
                dfs(s3, ns3, s1, s2, state);
            } else if (c == s2[0]) {
                dfs(s3, ns3, s2, s1, state);
            }
            return state.matched;
        }
    }

    bool is_interleaving(std::string const& s1, std::string const& s2, std::string const& s3)
    {
        size_t ns1 = s1.length();
        size_t ns2 = s2.length();
        size_t ns3 = s3.length();
        bool retval = false;
        if ((ns1 + ns2) == ns3) {
            if (ns1 != 0 && ns2 != 0) {
                return details::interleaving_check(s1, s2, s3, ns3);
            } else {
                if (ns1 == 0) {
                    retval = (s2 == s3);
                } else {
                    retval = (s1 == s3);
                }
            }
        }
        return retval;
    }
}

namespace v3
{
    namespace details
    {
        bool dfs_recursively(
            std::string const& input, size_t input_size, size_t current_vertex,
            std::string const& word, int64_t index_in_word,
            std::string const& another, int64_t index_in_another_word
        ) {
            size_t next_vertex = current_vertex + 1;
            if (next_vertex < input_size) {
                auto c = input[next_vertex];
                auto next_index_in_word = index_in_word + 1;
                auto next_index_in_another_word = index_in_another_word + 1;
                if (another[next_index_in_another_word] == c) {
                    if (
                        dfs_recursively(
                            input, input_size,
                            current_vertex + 1,
                            word, index_in_word,
                            another, next_index_in_another_word
                        )
                        ) {
                        return true;
                    }
                }
                if (word[next_index_in_word] == c) {
                    return dfs_recursively(
                        input, input_size,
                        current_vertex + 1,
                        word, next_index_in_word,
                        another, index_in_another_word
                    );
                }
                return false;
            }
            else {
                return true;
            }
        }

        bool interleaving_check(
            std::string const& s1,
            std::string const& s2,
            std::string const& s3, size_t ns3
        ) {
            char c = s3[0];
            if (c == s1[0]) {
                if (dfs_recursively(s3, ns3, 0, s1, 0, s2, -1)) {
                    return true;
                }
            }
            if (c == s2[0]) {
                return dfs_recursively(s3, ns3, 0, s2, 0, s1, -1);
            }

            return false;
        }
    }
    bool is_interleaving(std::string const& s1, std::string const& s2, std::string const& s3)
    {
        size_t ns1 = s1.length();
        size_t ns2 = s2.length();
        size_t ns3 = s3.length();
        bool retval = false;
        if ((ns1 + ns2) == ns3) {
            if (ns1 != 0 && ns2 != 0) {
                return details::interleaving_check(s1, s2, s3, ns3);
            }
            else {
                if (ns1 == 0) {
                    retval = (s2 == s3);
                }
                else {
                    retval = (s1 == s3);
                }
            }
        }
        return retval;
    }
}

int main()
{
    {
        std::string s1 = "aabaac", s2 = "aadaaeaaf", s3 = "aadaaeaabaafaac";
        examine(v1::is_interleaving(s1, s2, s3), "v1::is_interleaving is failed at the line: %d\n", __LINE__);
        examine(v2::is_interleaving(s1, s2, s3), "v2::is_interleaving is failed at the line: %d\n", __LINE__);
        examine(v3::is_interleaving(s1, s2, s3), "v3::is_interleaving is failed at the line: %d\n", __LINE__);
    }
    {
        std::string s1 = "aa", s2 = "ab", s3 = "abaa";
        examine(v1::is_interleaving(s1, s2, s3), "v1::is_interleaving is failed at the line: %d\n", __LINE__);
        examine(v2::is_interleaving(s1, s2, s3), "v2::is_interleaving is failed at the line: %d\n", __LINE__);
        examine(v3::is_interleaving(s1, s2, s3), "v3::is_interleaving is failed at the line: %d\n", __LINE__);
    }
    {
        std::string s1 = "aabcc", s2 = "dbbca", s3 = "aadbbcbcac";
        examine(v1::is_interleaving(s1, s2, s3), "v1::is_interleaving is failed at the line: %d\n", __LINE__);
        examine(v2::is_interleaving(s1, s2, s3), "v2::is_interleaving is failed at the line: %d\n", __LINE__);
        examine(v3::is_interleaving(s1, s2, s3), "v3::is_interleaving is failed at the line: %d\n", __LINE__);
    }
    {
        std::string s1 = "aabcc", s2 = "dbbca", s3 = "aadbbbaccc";
        examine(!v1::is_interleaving(s1, s2, s3), "v1::is_interleaving is failed at the line: %d\n", __LINE__);
        examine(!v2::is_interleaving(s1, s2, s3), "v2::is_interleaving is failed at the line: %d\n", __LINE__);
        examine(!v3::is_interleaving(s1, s2, s3), "v3::is_interleaving is failed at the line: %d\n", __LINE__);
    }
    {
        std::string s1 = "", s2 = "", s3 = "";
        examine(v1::is_interleaving(s1, s2, s3), "v1::is_interleaving is failed at the line: %d\n", __LINE__);
        examine(v2::is_interleaving(s1, s2, s3), "v2::is_interleaving is failed at the line: %d\n", __LINE__);
        examine(v3::is_interleaving(s1, s2, s3), "v3::is_interleaving is failed at the line: %d\n", __LINE__);
    }
    {
        std::string s1 = "bcbbacbaabaabbbacbbbcbbbc", s2 = "babcbbacaabbaaaabaccc", s3 = "bbcbbbcbabacbcbaacabaabaabaabbbaaacccbbabbbbcc";
        auto begin = std::chrono::system_clock::now();
        auto result = v1::is_interleaving(s1, s2, s3);
        auto end = std::chrono::system_clock::now();
        double duration = std::chrono::duration<double>(end - begin).count();
        printf("v1::is_interleaving %f seconds\n", duration);
        examine(!result, "v1::is_interleaving is failed at the line: %d\n", __LINE__);

        begin = std::chrono::system_clock::now();
        result = v2::is_interleaving(s1, s2, s3);
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration<double>(end - begin).count();
        printf("v2::is_interleaving %f seconds\n", duration);
        examine(!result, "v2::is_interleaving is failed at the line: %d\n", __LINE__);

        begin = std::chrono::system_clock::now();
        result = v3::is_interleaving(s1, s2, s3);
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration<double>(end - begin).count();
        printf("v3::is_interleaving %f seconds\n", duration);
        examine(!result, "v3::is_interleaving is failed at the line: %d\n", __LINE__);
    }
    {
        std::string s1 = "cbcccbabbccbbcccbbbcabbbabcababbbbbbaccaccbabbaacbaabbbc";
        std::string s2 = "abcbbcaababccacbaaaccbabaabbaaabcbababbcccbbabbbcbbb";
        std::string s3 = "abcbcccbacbbbbccbcbcacacbbbbacabbbabbcacbcaabcbaaacbcbbbabbbaacacbbaaaabccbcbaabbbaaabbcccbcbabababbbcbbbcbb";
        auto begin = std::chrono::system_clock::now();
        auto result = v1::is_interleaving(s1, s2, s3);
        auto end = std::chrono::system_clock::now();
        double duration = std::chrono::duration<double>(end - begin).count();
        printf("v1::is_interleaving %f seconds\n", duration);
        examine(result, "v1::is_interleaving is failed at the line: %d\n", __LINE__);

        begin = std::chrono::system_clock::now();
        result = v2::is_interleaving(s1, s2, s3);
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration<double>(end - begin).count();
        printf("v2::is_interleaving %f seconds\n", duration);
        examine(result, "v2::is_interleaving is failed at the line: %d\n", __LINE__);

        begin = std::chrono::system_clock::now();
        result = v3::is_interleaving(s1, s2, s3);
        end = std::chrono::system_clock::now();
        duration = std::chrono::duration<double>(end - begin).count();
        printf("v3::is_interleaving %f seconds\n", duration);
        examine(result, "v3::is_interleaving is failed at the line: %d\n", __LINE__);
    }
    printf("OK\n");
    return 0;
}



