#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <algorithm>
#include <iterator>
#include <set>
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


int main()
{
    generate_parenthesis_test();
    printf("OK\n");
    return 0;
}
