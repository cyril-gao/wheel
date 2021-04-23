#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iterator>
#include <random>
#include <vector>
#include "check.h"

/*
Given an array of integers heights representing the histogram's bar height where the width of each bar is 1, return the area of the largest rectangle in the histogram.

Example 1:
Input: heights = [2,1,5,6,2,3]
Output: 10
Explanation: The above is a histogram where width of each bar is 1.
The largest rectangle is shown in the red area, which has an area = 10 units.

Example 2:
Input: heights = [2,4]
Output: 4
*/

namespace brute_force
{
    template <typename I>
    auto get_minimum(I begin, I end)
    {
        typename std::iterator_traits<I>::value_type retval = *begin;
        for (I i = begin + 1; i < end; ++i)
        {
            retval = std::min(retval, *i);
        }
        return retval;
    }

    template <typename I>
    auto get_largest_rectangle_area(I begin, I end)
    {
        typename std::iterator_traits<I>::value_type retval = 0;
        auto n = std::distance(begin, end);
        for (decltype(n) span = 1; span <= n; ++span)
        {
            decltype(retval) v = get_minimum(begin, begin + span) * span;
            retval = std::max(v, retval);
            if (span < n)
            {
                decltype(n) last = span + 1;
                for (I i = begin + 1, j = i + span; last <= n; ++i, j != end ? ++j : j, ++last)
                {
                    v = get_minimum(i, j) * span;
                    retval = std::max(v, retval);
                }
            }
        }
        return retval;
    }
}

namespace divide_conquer
{
    template <typename I>
    typename std::iterator_traits<I>::value_type get_largest_rectangle_area(I begin, I end)
    {
        typename std::iterator_traits<I>::value_type retval = 0;
        auto n = std::distance(begin, end);
        if (n > 1)
        {
            I mid = begin + n / 2;
            I last = begin + (n - 1);
            decltype(retval) left = get_largest_rectangle_area<I>(begin, mid);
            decltype(retval) right = get_largest_rectangle_area<I>(mid, end);
            retval = std::max(left, right);
            I i = mid - 1, j = mid;
            left = *i;
            right = *j;
            if (left > 0 && right > 0)
            {
                while (true)
                {
                    bool no_change = true;
                    auto v = std::min(left, right);
                    for (I k = i; k != begin && *--k >= v; i = k)
                    {
                    }
                    for (I k = j; k != last && *++k >= v; j = k)
                    {
                    }
                    retval = std::max(retval, static_cast<decltype(retval)>(v * (j - i + 1)));
                    if (i != begin && j < last)
                    {
                        if (*(i - 1) >= *(j + 1))
                        {
                            --i;
                            if (*i > 0)
                            {
                                left = *i;
                                no_change = false;
                            }
                        }
                        else
                        {
                            ++j;
                            if (*j > 0)
                            {
                                right = *j;
                                no_change = false;
                            }
                        }
                    }
                    else
                    {
                        if (i != begin)
                        {
                            --i;
                            if (*i > 0)
                            {
                                left = *i;
                                no_change = false;
                            }
                        }
                        if (j < last)
                        {
                            ++j;
                            if (*j > 0)
                            {
                                right = *j;
                                no_change = false;
                            }
                        }
                    }

                    if (no_change)
                    {
                        break;
                    }
                }
            }
        }
        else
        {
            if (n == 1)
            {
                retval = *begin;
            }
        }
        return retval;
    }
}

namespace fast
{
    template <typename I>
    auto get_largest_rectangle_area(I begin, I end)
    {
        // TODO
    }
}

int main()
{
    {
        std::vector<int> heights = {2, 1, 5, 6, 2, 3};
        auto r1 = brute_force::get_largest_rectangle_area(heights.begin(), heights.end());
        auto r2 = divide_conquer::get_largest_rectangle_area(heights.begin(), heights.end());
        examine(r1 == 10, "brute_force::get_largest_rectangle_area is failed at the line: %d\n", __LINE__);
        examine(r2 == 10, "divide_conquer::get_largest_rectangle_area is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> heights = {2, 4};
        auto r1 = brute_force::get_largest_rectangle_area(heights.begin(), heights.end());
        auto r2 = divide_conquer::get_largest_rectangle_area(heights.begin(), heights.end());
        examine(r1 == 4, "brute_force::get_largest_rectangle_area is failed at the line: %d\n", __LINE__);
        examine(r2 == 4, "divide_conquer::get_largest_rectangle_area is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> heights = {3, 6, 3};
        auto r1 = brute_force::get_largest_rectangle_area(heights.begin(), heights.end());
        auto r2 = divide_conquer::get_largest_rectangle_area(heights.begin(), heights.end());
        examine(r1 == 9, "brute_force::get_largest_rectangle_area is failed at the line: %d\n", __LINE__);
        examine(r2 == 9, "divide_conquer::get_largest_rectangle_area is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> heights = {2, 6, 0, 2, 2};
        auto r1 = brute_force::get_largest_rectangle_area(heights.begin(), heights.end());
        auto r2 = divide_conquer::get_largest_rectangle_area(heights.begin(), heights.end());
        examine(r1 == 6, "brute_force::get_largest_rectangle_area is failed at the line: %d\n", __LINE__);
        examine(r2 == 6, "divide_conquer::get_largest_rectangle_area is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> heights = {26, 18, 28, 28, 15, 32, 14, 29, 1, 32, 32, 30, 24, 21, 4, 0, 11};
        auto r1 = brute_force::get_largest_rectangle_area(heights.begin(), heights.end());
        auto r2 = divide_conquer::get_largest_rectangle_area(heights.begin(), heights.end());
        examine(r1 == 112, "brute_force::get_largest_rectangle_area is failed at the line: %d\n", __LINE__);
        examine(r2 == 112, "divide_conquer::get_largest_rectangle_area is failed at the line: %d\n", __LINE__);
    }
    {
        std::random_device rd;
        std::default_random_engine dre(rd());
        std::uniform_int_distribution<int> uid(0, 32);
        for (int i = 0; i < 100; ++i)
        {
            std::vector<int> heights(1027);
            for (int &h : heights)
            {
                h = uid(dre);
            }
            auto r1 = brute_force::get_largest_rectangle_area(heights.begin(), heights.end());
            auto r2 = divide_conquer::get_largest_rectangle_area(heights.begin(), heights.end());
            examine(r1 == r2, "the result of the brute force method is different from that of the divide conquer method\n");
        }
    }
    printf("OK\n");
    return 0;
}
