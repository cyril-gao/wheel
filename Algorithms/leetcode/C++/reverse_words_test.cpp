#include <stdio.h>
#include <string.h>
#include <stdint.h>

#include <string>
#include <vector>

#include "check.h"

std::string reverse_words(std::string const& input)
{
    int64_t n = static_cast<int64_t>(input.length());
    std::vector<char> buf;
    buf.reserve(n+1);
    for (int64_t end = n; end >= 0;) {
        int64_t i = end - 1;
        while (i >= 0 && isspace(input[i])) {
            --i;
        }
        end = i + 1;
        while (i >= 0 && !isspace(input[i])) {
            --i;
        }
        int64_t head = i + 1;
        if (head < end) {
            if (!buf.empty()) {
                buf.push_back(' ');
            }
            buf.insert(buf.end(), &input[head], &input[end]);
        }
        end = i;
    }
    buf.push_back('\0');
    return &buf[0];
}

int main()
{
    {
        std::string expection("blue is sky the");
        auto result = reverse_words("the sky is blue");
        examine(expection == result, "reverse_words is wrong at the line: %d\n", __LINE__);
    }
    {
        std::string expection("world hello");
        auto result = reverse_words("  hello world  ");
        examine(expection == result, "reverse_words is wrong at the line: %d\n", __LINE__);
    }
    {
        std::string expection("example good a");
        auto result = reverse_words("a good   example");
        examine(expection == result, "reverse_words is wrong at the line: %d\n", __LINE__);
    }
    {
        std::string expection("Alice Loves Bob");
        auto result = reverse_words("  Bob    Loves  Alice   ");
        examine(expection == result, "reverse_words is wrong at the line: %d\n", __LINE__);
    }
    {
        std::string expection("bob like even not does Alice");
        auto result = reverse_words("Alice does not even like bob");
        examine(expection == result, "reverse_words is wrong at the line: %d\n", __LINE__);
    }
    return 0;
}
