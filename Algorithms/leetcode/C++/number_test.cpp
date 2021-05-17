#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <math.h>

#include <vector>
#include "check.h"

/*
Implement the int str_to_int(const char * input) function,
which converts a string to a 32-bit signed integer (similar to C/C++'s atoi function).
*/

int str_to_int(const char * input)
{
    const int LAST = 214748364;
    auto is_digit = [](char c) {
        return c >= '0' && c <= '9';
    };

    int flag = 1;
    int retval = 0;
    if (input != nullptr && input[0] != '\0') {
        const char * p = input;
        while (*p == ' ') {
            ++p;
        }
        if (*p == '-') {
            flag = -1;
            ++p;
        } else if (*p == '+') {
            ++p;
        }
        while (is_digit(*p)) {
            int d = (*p - '0');
            if (retval < LAST || (retval == LAST && d <= 7)) {
                retval = (retval * 10) + d;
            } else {
                if (flag > 0) {
                    retval = INT_MAX;
                } else {
                    retval = INT_MIN;
                    flag = 1;
                }
                break;
            }
            ++p;
        }
        retval *= flag;
    }
    return retval;
}

void str_to_int_test()
{
    {
        int result = str_to_int("  -42");
        examine(result == -42, "str_to_int is failed at the line: %d\n", __LINE__);
    }
    {
        int result = str_to_int("4193 with words");
        examine(result == 4193, "str_to_int is failed at the line: %d\n", __LINE__);
    }
    {
        int result = str_to_int("words and 987");
        examine(result == 0, "str_to_int is failed at the line: %d\n", __LINE__);
    }
    {
        int result = str_to_int("-91283472332");
        examine(result == INT_MIN, "str_to_int is failed at the line: %d\n", __LINE__);
    }
    {
        int result = str_to_int("91283472332");
        examine(result == INT_MAX, "str_to_int is failed at the line: %d\n", __LINE__);
    }
    {
        int result = str_to_int("42");
        examine(result == 42, "str_to_int is failed at the line: %d\n", __LINE__);
    }
}


/*
Given two integers dividend and divisor, divide two integers without using multiplication,
division, and mod operator.

Return the quotient after dividing dividend by divisor.

The integer division should truncate toward zero, which means losing its fractional part.
For example, truncate(8.345) = 8 and truncate(-2.7335) = -2.

Note: Assume we are dealing with an environment that could only store integers within the 32-bit
signed integer range: [-231, 231 - 1]. For this problem, assume that your function returns
231 - 1 when the division result overflows.
*/

int positive_divide(unsigned int dividend, unsigned int divisor)
{
    int retval = 0;
    assert(divisor > 0);
    if (dividend >= divisor) {
        if (((divisor - 1) & divisor) != 0) {
            unsigned int p, r;
            for (p = 1, r = divisor; r <= dividend; p <<= 1, r <<= 1) {}
            for (p >>= 1, r >>= 1; dividend >= divisor; p >>= 1, r >>= 1) {
                if (dividend >= r) {
                    dividend -= r;
                    retval += static_cast<int>(p);
                }
            }
        } else {
            int i = 0;
            for (unsigned int d = divisor; d != 1u; ++i, d >>= 1) {}
            if (!(divisor == 1 && dividend >= INT_MAX)) {
                retval = static_cast<int>(dividend >> i);
            } else {
                retval = INT_MAX;
            }
        }
    }
    return retval;
}

int divide(int dividend, int divisor)
{
    assert(divisor != 0);
    if (dividend >= 0 && divisor > 0) {
        return positive_divide(dividend, divisor);
    } else if (dividend <= 0 && divisor < 0) {
        if (dividend != divisor) {
            if (dividend != INT_MIN && divisor != INT_MIN) {
                return positive_divide(-dividend, -divisor);
            }
            if (dividend == INT_MIN) {
                return positive_divide(static_cast<unsigned int>(INT_MAX) + 1u, -divisor);
            }
            return 0;
        } else {
            return 1;
        }
    } else {
        if (divisor < 0) {
            if (divisor != INT_MIN) {
                return -positive_divide(dividend, -divisor);
            }
            return 0;
        }
        if (divisor != 1) {
            if (dividend != INT_MIN) {
                return -positive_divide(-dividend, divisor);
            }
            return -positive_divide(static_cast<unsigned int>(INT_MAX) + 1u, divisor);
        } else {
            return dividend;
        }
    }
}

void divide_test()
{
    int nums[] = {
        INT_MIN, INT_MIN + 1, INT_MIN + 2, -2834752, -345734, -131072, -9253, -745, -87, -64, -5, -4, -3, -2, -1,
        1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 64, 128, 534, 9857, 131072, 1048576, 9467786, INT_MAX
    };
    for (int a : nums) {
        for (int b : nums) {
            if (a != INT_MIN || b != -1) {
                assert(divide(a, b) == (a / b));
                examine(divide(a, b) == a / b, "divide is failed for the input: %d / %d\n", a, b);
            } else {
                assert(divide(a, b) == INT_MAX);
                examine(divide(a, b) == INT_MAX, "divide is failed for the input: %d / %d\n", a, b);
            }
        }
    }
}

/*
Implement pow(x, n), which calculates x raised to the power n (i.e., x^n).
*/
namespace study
{
    double positive_pow(double x, unsigned int n)
    {
        assert(n > 0);
        double retval = 1.0;
        double power = x;
        for (
            unsigned bit = 1, mask = -1;
            (n & bit) != 0 || (n & mask) != 0;
            bit <<= 1, mask <<= 1 , power = power * power
        ) {
            if ((n & bit) != 0) {
                retval *= power;
            }
        }
        return retval;
    }

    double pow(double x, int n)
    {
        if (n > 0) {
            return positive_pow(x, static_cast<unsigned int>(n));
        } else if (n < 0) {
            if (n != INT_MIN) {
                return 1 / positive_pow(x, static_cast<unsigned int>(-n));
            }
            return 1 / positive_pow(x, static_cast<unsigned int>(INT_MAX) + 1u);
        } else {
            return 1.0;
        }
    }

    bool equal(double x, double y)
    {
        return fabs(x - y) < 0.001;
    }
}

void pow_test()
{
    double xs[] = {1.02345, 1.656, 1.0035, -1.0334, -1.004657};
    int ns[] = {-101, -53, -29, -17, -11, -7, -3, -1, 0, 1, 3, 5, 7, 9, 11, 13, 17, 19, 23, 29, 53};
    for (auto x : xs) {
        for (auto n : ns) {
            // there are significant difference between the two results
            examine(study::equal(study::pow(x, n), pow(x, n)), "pow is failed for the input: %f ^ %d\n", x, n);
        }
    }
}


/*
A valid number can be split up into these components (in order):
1. A decimal number or an integer.
2. (Optional) An 'e' or 'E', followed by an integer.


A decimal number can be split up into these components (in order):
1. (Optional) A sign character (either '+' or '-').
2. One of the following formats:
    1). At least one digit, followed by a dot '.'.
    2). At least one digit, followed by a dot '.', followed by at least one digit.
    3). A dot '.', followed by at least one digit.


An integer can be split up into these components (in order):
1. (Optional) A sign character (either '+' or '-').
2. At least one digit.


For example, all the following are valid numbers:
["2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789"],
while the following are not valid numbers:
["abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53"].

Given a string s, return true if s is a valid number.


Example 1:
Input: s = "0"
Output: true

Example 2:
Input: s = "e"
Output: false

Example 3:
Input: s = "."
Output: false

Example 4:
Input: s = ".1"
Output: true
*/

bool is_valid_exponential_part(const char * input)
{
    bool retval = false;
    if (*input == '-' || *input == '+') {
        ++input;
    }
    if (isdigit(*input)) {
        for (++input; isdigit(*input); ++input) {}
        if (*input == '\0') {
            retval = true;
        }
    }
    return retval;
}

bool is_vaild_tail(const char * input, int minimum_amount_of_number)
{
    bool retval = false;
    if (*input == '\0') {
        retval = minimum_amount_of_number == 0;
    } else if (isdigit(*input)) {
        int count = 0;
        while (isdigit(*input)) {
            ++input;
            ++count;
        }
        if (count >= minimum_amount_of_number) {
            if (*input == 'e' || *input == 'E') {
                retval = is_valid_exponential_part(input + 1);
            } else if (*input == '\0') {
                retval = true;
            }
        }
    } else if (*input == 'e' || *input == 'E') {
        if (minimum_amount_of_number == 0) {
            retval = is_valid_exponential_part(input + 1);
        }
    }
    return retval;
}

bool is_number(const char * input)
{
    bool retval = false;
    if (input != nullptr && *input != '\0') {
        while (isspace(*input)) {
            ++input;
        }
        if (*input != '\0') {
            if (*input == '+' || *input == '-') {
                ++input;
            }
            if (isdigit(*input)) {
                for (++input; isdigit(*input); ++input) {}
                if (*input == '\0') {
                    retval = true;
                } else if (*input == '.') {
                    retval = is_vaild_tail(input + 1, 0);
                } else if (*input == 'e' || *input == 'E') {
                    retval = is_valid_exponential_part(input + 1);
                }
            } else if (*input == '.') {
                retval = is_vaild_tail(input + 1, 1);
            }
        }
    } 
    return retval;
}

void is_number_test()
{
    const char * good_input[] = { "2", "0089", "-0.1", "+3.14", "4.", "-.9", "2e10", "-90E3", "3e+7", "+6e-1", "53.5e93", "-123.456e789" };
    for (auto n : good_input) {
        examine(is_number(n), "is_number is failed for the argument: %s\n", n);
    }
    const char * bad_input[] = { "abc", "1a", "1e", "e3", "99e2.5", "--6", "-+3", "95a54e53", "." };
    for (auto n : bad_input ) {
        examine(!is_number(n), "is_number is failed for the argument: %s\n", n);
    }
}


int main()
{
    str_to_int_test();
    divide_test();
    pow_test();
    is_number_test();
    printf("OK\n");
    return 0;
}
