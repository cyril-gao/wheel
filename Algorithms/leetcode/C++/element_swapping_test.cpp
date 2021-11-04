#include <stdio.h>

#include <algorithm>
#include <vector>

#include "check.h"


/*
Element Swapping
Given a sequence of n integers arr, determine the lexicographically smallest sequence
which may be obtained from it after performing at most k element swaps, each involving
a pair of consecutive elements in the sequence.

Note: A list x is lexicographically smaller than a different equal-length list y if and
only if, for the earliest index at which the two lists differ, x's element at that index
is smaller than y's element at that index.

Example 1
n = 3
k = 2
arr = [5, 3, 1]
output = [1, 5, 3]
We can swap the 2nd and 3rd elements, followed by the 1st and 2nd elements, to end up with the
sequence [1, 5, 3]. This is the lexicographically smallest sequence achievable after at most 2 swaps.

Example 2
n = 5
k = 3
arr = [8, 9, 11, 2, 1]
output = [2, 8, 9, 11, 1]
We can swap [11, 2], followed by [9, 2], then [8, 2].
*/

template <typename I>
void insertion_sort(I begin, I index)
{
    auto v = *index;
    while (index != begin) {
        I j = index - 1;
        if (*j > v) {
            *index = *j;
            index = j;
        } else {
            break;
        }
    }
    *index = v;
}

std::vector<int> find_minimum_array(std::vector<int> const& array, int k)
{
    std::vector<int> retval(array);
    size_t n = array.size();
    if (n > 0 && k > 0) {
        for (
            size_t uk = static_cast<size_t>(k), i = 0;
            uk != 0 && i < n;
            ++i
        ) {
            auto begin = retval.begin();
            size_t end_index = i + uk + 1;
            if (end_index > n) {
                end_index = n;
            }
            auto end = begin + end_index;
            auto j = std::min_element(begin + i, end);
            uk -= (static_cast<size_t>(j - begin) - i);
            insertion_sort(begin + i, j);
        }
    }
    return retval;
}

int main()
{
    try {
        {
            int k = 20;
            std::vector<int> expectation = {1, 2, 3, 4};
            std::vector<int> input = {1, 2, 3, 4};
            auto output = find_minimum_array(input, k);
            examine(output == expectation, "find_minimum_array is failed at the line: %d\n", __LINE__);
        }
        {
            int k = 3;
            std::vector<int> expectation = {1, 2, 3, 4};
            std::vector<int> input = {1, 2, 3, 4};
            auto output = find_minimum_array(input, k);
            examine(output == expectation, "find_minimum_array is failed at the line: %d\n", __LINE__);
        }
        {
            int k = 2;
            std::vector<int> expectation = {1, 5, 3};
            std::vector<int> input = {5, 3, 1};
            auto output = find_minimum_array(input, k);
            examine(output == expectation, "find_minimum_array is failed at the line: %d\n", __LINE__);
        }
        {
            int k = 3;
            std::vector<int> expectation = {2, 8, 9, 11, 1};
            std::vector<int> input = {8, 9, 11, 2, 1};
            auto output = find_minimum_array(input, k);
            examine(output == expectation, "find_minimum_array is failed at the line: %d\n", __LINE__);
        }
        {
            int k = 7;
            std::vector<int> expectation = {1, 2, 8, 9, 11};
            std::vector<int> input = {8, 9, 11, 2, 1};
            auto output = find_minimum_array(input, k);
            examine(output == expectation, "find_minimum_array is failed at the line: %d\n", __LINE__);
        }
        {
            int k = 17;
            std::vector<int> expectation = {1, 2, 8, 9, 11};
            std::vector<int> input = {8, 9, 11, 2, 1};
            auto output = find_minimum_array(input, k);
            examine(output == expectation, "find_minimum_array is failed at the line: %d\n", __LINE__);
        }
        {
            int k = 15;
            std::vector<int> expectation = {1, 2, 3, 4, 6, 8, 7, 9, 5};
            std::vector<int> input = {8, 3, 7, 6, 1, 2, 9, 4, 5};
            auto output = find_minimum_array(input, k);
            examine(output == expectation, "find_minimum_array is failed at the line: %d\n", __LINE__);
        }
    } catch (std::exception const& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }
    return 0;
}