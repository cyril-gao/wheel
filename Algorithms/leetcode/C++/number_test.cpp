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
            unsigned bit = 1, mask = 1;
            (n & bit) != 0 || (n & ~mask) != 0;
            bit <<= 1, mask = ((mask << 1) | 1u), power = power * power
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

int main()
{
    str_to_int_test();
    divide_test();
    pow_test();
    printf("OK\n");
    return 0;
}
