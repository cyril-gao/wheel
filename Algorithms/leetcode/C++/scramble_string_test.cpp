#include <stdio.h>
#include <assert.h>

#include <chrono>
#include <algorithm>
#include <functional>
#include <string>

#include "check.h"

/*
We can scramble a string s to get a string t using the following algorithm:

If the length of the string is 1, stop.
If the length of the string is > 1, do the following:
Split the string into two non-empty substrings at a random index, i.e., if the string is s, divide it to x and y where s = x + y.
Randomly decide to swap the two substrings or to keep them in the same order. i.e., after this step, s may become s = x + y or s = y + x.
Apply step 1 recursively on each of the two substrings x and y.
Given two strings s1 and s2 of the same length, return true if s2 is a scrambled string of s1, otherwise, return false.


Example 1:
Input: s1 = "great", s2 = "rgeat"
Output: true
Explanation: One possible scenario applied on s1 is:
"great" --> "gr/eat" // divide at random index.
"gr/eat" --> "gr/eat" // random decision is not to swap the two substrings and keep them in order.
"gr/eat" --> "g/r / e/at" // apply the same algorithm recursively on both substrings. divide at ranom index each of them.
"g/r / e/at" --> "r/g / e/at" // random decision was to swap the first substring and to keep the second substring in the same order.
"r/g / e/at" --> "r/g / e/ a/t" // again apply the algorithm recursively, divide "at" to "a/t".
"r/g / e/ a/t" --> "r/g / e/ a/t" // random decision is to keep both substrings in the same order.
The algorithm stops now and the result string is "rgeat" which is s2.
As there is one possible scenario that led s1 to be scrambled to s2, we return true.


Example 2:
Input: s1 = "abcde", s2 = "caebd"
Output: false


Example 3:
Input: s1 = "a", s2 = "a"
Output: true
*/

namespace v1
{
    namespace details
    {
        using SI = std::string::const_iterator;

        bool is_scramble(SI begin1, SI end1, SI begin2, SI end2);

        bool split_and_check_is_scramble(SI begin1, SI mid1, SI end1, SI begin2, SI mid2, SI end2)
        {
            assert(*mid1 == *mid2);
            auto len = end1 - begin1;
            assert(len > 2);
            if (mid2 != begin2) {
                if (mid2 != (begin2 + (len - 1))) {
                    auto len2 = end2 - mid2;
                    auto len3 = mid2 - begin2;
                    if (len2 <= len3) {
                        if (is_scramble(begin1, begin1 + len2, mid2, end2) && is_scramble(begin1 + len2, end1, begin2, mid2)) {
                            return true;
                        }
                    }
                    else {
                        if (is_scramble(begin1 + len2, end1, begin2, mid2) && is_scramble(begin1, begin1 + len2, mid2, end2)) {
                            return true;
                        }
                    }
                    len2 = len3 + 1;
                    len3 = len - len2;
                    if (len2 <= len3) {
                        return is_scramble(begin1, begin1 + len2, begin2, begin2 + len2) && is_scramble(begin1 + len2, end1, begin2 + len2, end2);
                    }
                    return is_scramble(begin1 + len2, end1, begin2 + len2, end2) && is_scramble(begin1, begin1 + len2, begin2, begin2 + len2);
                }
                else {
                    if (mid1 == begin1) {
                        return is_scramble(begin1 + 1, end1, begin2, mid2);
                    }
                    else if (mid1 == (begin1 + (len - 1))) {
                        return is_scramble(begin1, mid1, begin2, mid2);
                    }
                    else {
                        return split_and_check_is_scramble(begin2, mid2, end2, begin1, mid1, end1);
                    }
                }
            }
            else {
                if (mid1 == begin1) {
                    return is_scramble(begin1 + 1, end1, begin2 + 1, end2);
                }
                else if (mid1 == (begin1 + (len - 1))) {
                    return is_scramble(begin1, mid1, begin2 + 1, end2);
                }
                else {
                    return split_and_check_is_scramble(begin2, mid2, end2, begin1, mid1, end1);
                }
            }
        }

        bool is_scramble(SI begin1, SI end1, SI begin2, SI end2)
        {
            assert((end1 - begin1) == (end2 - begin2));
            auto retval = std::equal(begin1, end1, begin2);
            if (!retval) {
                auto len = end1 - begin1;
                if (len > 2) {
                    for (auto i = begin1; i != end1; ++i) {
                        auto j = begin2;
                        while (j != end2) {
                            auto k = std::find(j, end2, *i);
                            if (k != end2) {
                                if (split_and_check_is_scramble(begin1, i, end1, begin2, k, end2)) {
                                    retval = true;
                                    goto out;
                                }
                                ++k;
                            }
                            j = k;
                        }
                    }
                }
                else if (len == 2) {
                    retval = *begin1 == *(begin2 + 1) && *(begin1 + 1) == *begin2;
                }
            }
        out:
            return retval;
        }
    }

    bool is_scramble(std::string const& s1, std::string const& s2)
    {
        return (s1.length() == s2.length()) && details::is_scramble(s1.begin(), s1.end(), s2.begin(), s2.end());
    }
}


namespace v2
{
    namespace details
    {
        bool is_scramble(size_t n, std::string const& s1, std::string const& s2)
        {
            using cache_t = std::vector<std::vector<std::vector<std::vector<bool>>>>;
            cache_t cache(
                n,
                std::vector<std::vector<std::vector<bool>>>(
                    n + 1,
                    std::vector<std::vector<bool>>(
                        n,
                        std::vector<bool>(n + 1, false)
                    )
                )
            );

            for (size_t i = 0, ii = 1; ii <= n; ++i, ++ii) {
                for (size_t j = 0, jj = 1; jj <= n; ++j, ++jj) {
                    cache[i][ii][j][jj] = (s1[i] == s2[j]);
                }
            }
            for (size_t i = 0, ii = 2; ii <= n; ++i, ++ii) {
                for (size_t j = 0, jj = 2; jj <= n; ++j, ++jj) {
                    cache[i][ii][j][jj] = (
                        (s1[i] == s2[j] && s1[i + 1] == s2[j + 1]) ||
                        (s1[i] == s2[j + 1] && s1[i + 1] == s2[j])
                    );
                }
            }
            for (size_t span = 3; span <= n; ++span) {
                for (size_t i = 0, ii = span; ii <= n; ++i, ++ii) {
                    for (size_t j = 0, jj = span; jj <= n; ++j, ++jj) {
                        if (std::equal(&s1[i], &s1[i] + ii, &s2[j])) {
                            cache[i][ii][j][jj] = true;
                        }
                        else {
                            for (size_t k = 1; k < span; ++k) {
                                if (cache[i][i + k][j][j + k] && cache[i + k][ii][j + k][jj]) {
                                    cache[i][ii][j][jj] = true;
                                    break;
                                }
                                if (cache[i][i + k][jj - k][jj] && cache[i + k][ii][j][jj - k]) {
                                    cache[i][ii][j][jj] = true;
                                    break;
                                }
                            }
                        }
                    }
                }
            }
            return cache[0][n][0][n];
        }
    }

    bool is_scramble(std::string const& s1, std::string const& s2)
    {
        size_t len = s1.length();
        return len == s2.length() && details::is_scramble(len, s1, s2);
    }
}

#define RUN_CASE(s1, s2, F, expectation, showing_duration)                                    \
    do {                                                                                      \
        auto begin = std::chrono::system_clock::now();                                        \
        auto result = F(s1, s2);                                                              \
        auto end = std::chrono::system_clock::now();                                          \
        double duration = std::chrono::duration<double>(end - begin).count();                 \
        if (showing_duration) {                                                               \
            printf("It took %s %f seconds for the input: %s <-> %s\n", #F, duration, s1, s2); \
        }                                                                                     \
        examine(result == expectation, "%s is failed for the input: %s <-> %s\n", #F, s1, s2);\
    } while (false)

int main()
{
    {
        RUN_CASE("abcdbdacbdac", "bdacabcdbdac", v2::is_scramble, true, false);
        RUN_CASE("great", "rgeat", v2::is_scramble, true, false);
        RUN_CASE("abcd", "cabd", v2::is_scramble, true, false);
        RUN_CASE("abcd", "dbac", v2::is_scramble, true, false);
        RUN_CASE("abcde", "edcba", v2::is_scramble, true, false);
        RUN_CASE("abcdbdacbdac", "bdacabcdbdac", v2::is_scramble, true, false);
        RUN_CASE("ccabcbabcbabbbbcbbabcdbdacbdacabcdbdacbdac", "bbbbabccccbbbabcbabdacabcdbdacbdacabcdbdac", v2::is_scramble, true, true);
        RUN_CASE("ccbabcbabbbbcbbabcdbdacac", "bbbbcccbbbabcbabdacabcdac", v2::is_scramble, true, true);
        RUN_CASE("abcde", "caebd", v2::is_scramble, false, false);
        RUN_CASE("dcoiorfhkqdwp", "rdpihwfkcooqd", v2::is_scramble, false, false);
    }
    {
        RUN_CASE("great", "rgeat", v1::is_scramble, true, false);
        RUN_CASE("abcd", "cabd", v1::is_scramble, true, false);
        RUN_CASE("abcd", "dbac", v1::is_scramble, true, false);
        RUN_CASE("abcde", "edcba", v1::is_scramble, true, false);
        RUN_CASE("abcdbdacbdac", "bdacabcdbdac", v1::is_scramble, true, false);
        RUN_CASE("ccbabcbabbbbcbbabcdbdacac", "bbbbcccbbbabcbabdacabcdac", v1::is_scramble, true, true);
        RUN_CASE("abcde", "caebd", v1::is_scramble, false, false);
        RUN_CASE("dcoiorfhkqdwp", "rdpihwfkcooqd", v1::is_scramble, false, false);
    }

    return 0;
}
