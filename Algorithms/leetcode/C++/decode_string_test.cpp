#include <stdio.h>
#include <assert.h>
#include <string.h>

#include <string>
#include <vector>
#include <stdexcept>

#include "check.h"


/*
Given an encoded string, return its decoded string.

The encoding rule is: k[encoded_string], where the encoded_string inside the square brackets is being repeated exactly k times. Note that k is guaranteed to be a positive integer.

You may assume that the input string is always valid; No extra white spaces, square brackets are well-formed, etc.

Furthermore, you may assume that the original data does not contain any digits and that digits are only for those repeat numbers, k. For example, there won't be input like 3a or 2[4].

 

Example 1:
Input: s = "3[a]2[bc]"
Output: "aaabcbc"

Example 2:
Input: s = "3[a2[c]]"
Output: "accaccacc"

Example 3:
Input: s = "2[abc]3[cd]ef"
Output: "abcabccdcdcdef"

Example 4:
Input: s = "abc3[cd]xyz"
Output: "abccdcdcdxyz"
*/


namespace
{
    std::string repeat(const char * input, size_t begin, size_t end, size_t times)
    {
        std::string retval;
        retval.reserve((end - begin) * times);
        for (size_t i = 0; i < times; ++i) {
            retval.insert(retval.end(), input + begin, input + end);
        }
        return retval;
    }

    std::string decode_string(const char * input, size_t begin, size_t end)
    {
        std::string retval;
        retval.reserve(end - begin);
        for (size_t i = begin, j = i; i != end;) {
            for (j = i; j != end;) {
                if (!isdigit(input[j])) {
                    retval.push_back(input[j]);
                    ++j;
                } else {
                    break;
                }
            }
            if (j != end) {
                assert(isdigit(input[j]));
                i = j++;
                while (j != end && isdigit(input[j])) {
                    ++j;
                }
                if (j != end && input[j] == '[') {
                    int count = 1;
                    bool recursive = false;
                    size_t k;
                    for (k = j + 1; k != end; ++k) {
                        if (input[k] == '[') {
                            ++count;
                            recursive = true;
                        } else if (input[k] == ']') {
                            --count;
                            if (count == 0) {
                                break;
                            }
                        }
                    }
                    if (count == 0) {
                        auto times = strtoul(input + i, nullptr, 10);
                        if (!recursive) {
                            auto r = repeat(input, j + 1, k, times);
                            retval.insert(retval.end(), r.begin(), r.end());
                        } else {
                            auto r1 = decode_string(input, j + 1, k);
                            auto r2 = repeat(r1.c_str(), 0, r1.size(), times);
                            retval.insert(retval.end(), r2.begin(), r2.end());
                        }
                        j = k + 1;
                    } else {
                        throw std::invalid_argument("no matched [ is found");
                    }
                } else {
                    retval.insert(retval.end(), input + i, input + j);
                }
            }
            i = j;
        }
        return retval;
    }
}

std::string decode_string(const char * input)
{
    if (input != nullptr && input[0] != 0) {
        size_t n = strlen(input);
        return decode_string(input, 0, n);
    }
    return std::string();
}

int main()
{
    {
        auto r = decode_string("3[a]2[bc]");
        examine(r == "aaabcbc", "decode_string is failed at the line: %d\n", __LINE__);
    }
    {
        auto r = decode_string("123abc456def789ghi[]");
        examine(r == "123abc456def789ghi[]", "decode_string is failed at the line: %d\n", __LINE__);
    }
    {
        auto r = decode_string("3[a2[c]]");
        examine(r == "accaccacc", "decode_string is failed at the line: %d\n", __LINE__);
    }
    {
        auto r = decode_string("2[abc]3[cd]ef");
        examine(r == "abcabccdcdcdef", "decode_string is failed at the line: %d\n", __LINE__);
    }
    {
        auto r = decode_string("abc3[cd]xyz");
        examine(r == "abccdcdcdxyz", "decode_string is failed at the line: %d\n", __LINE__);
    }
    {
        auto r = decode_string("354abc3[cd]56xyz");
        examine(r == "354abccdcdcd56xyz", "decode_string is failed at the line: %d\n", __LINE__);
    }
    printf("OK\n");
    return 0;
}
