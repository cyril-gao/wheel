#include <assert.h>
#include <limits.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdio.h>

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


int main()
{
    str_to_int_test();
    divide_test();
    printf("OK\n");
    return 0;
}
