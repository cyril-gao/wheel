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


int main()
{
    str_to_int_test();
    printf("OK\n");
    return 0;
}
