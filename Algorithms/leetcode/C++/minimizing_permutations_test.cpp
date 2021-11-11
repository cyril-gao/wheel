#include <assert.h>
#include <stdio.h>

#include <algorithm>
#include <functional>
#include <iterator>
#include <queue>
#include <vector>
#include <unordered_set>

#include "check.h"


/*
Minimizing Permutations
In this problem, you are given an integer N, and a permutation, P of the integers from 1 to N,
denoted as (a_1, a_2, ..., a_N). You want to rearrange the elements of the permutation into
increasing order, repeatedly making the following operation:
Select a sub-portion of the permutation, (a_i, ..., a_j), and reverse its order.
Your goal is to compute the minimum number of such operations required to return the permutation to increasing order.

Example
If N = 3, and P = (3, 1, 2), we can do the following operations:
Select (1, 2) and reverse it: P = (3, 2, 1).
Select (3, 2, 1) and reverse it: P = (1, 2, 3).
output = 2
*/

struct VectorHash
{
    size_t operator()(std::vector<int> const& input) const noexcept
    {
        size_t retval = 0;
        for (int n : input) {
            retval = retval * 11 + static_cast<size_t>(n);
        }
        return retval;
    }
};

template <typename I>
void reverse_array(I begin, I last)
{
    for (; begin < last; ++begin, --last) {
        std::iter_swap(begin, last);
    }
}

bool in_order(std::vector<int> const& array)
{
    bool retval = true;
    for (int i = 1, n = static_cast<int>(array.size()); i <= n; ++i) {
        if (array[i-1] != i) {
            retval = false;
            break;
        }
    }
    return retval;
}

bool valid(std::vector<int> const& array)
{
    std::vector<int> copy(array);
    std::sort(copy.begin(), copy.end());
    return in_order(copy);
}

struct Item
{
    std::vector<int> data;
    int begin;
    int first;
    int last;
    int step;

    Item() : begin(-1), first(-1), last(-1), step(-1) {}
    Item(std::vector<int>&& d, int b, int f, int l, int s) : data(std::move(d)), begin(b), first(f), last(l), step(s) {}
};

std::vector<Item> neighbours(
    std::vector<int> const& input,
    int begin_index,
    int first_value,
    int last_value,
    int step,
    std::unordered_set<std::vector<int>, VectorHash>& visited
) {
    assert(!in_order(input));
    std::vector<Item> retval;

    ++step;
    {
        std::vector<int> data(input);
        auto begin = data.begin();
        auto end = data.end();
        int my_begin_index = begin_index;
        int my_first_value = first_value;
        auto i = begin + begin_index;
        while (i != end) {
            if (*i == my_first_value) {
                ++i;
                ++my_begin_index;
                ++my_first_value;
            } else {
                break;
            }
        }
        if (i != end) {
            auto j = std::find(i + 1, end, my_first_value);
            assert(j != end);
            reverse_array(i, j);
            ++my_begin_index;
            ++my_first_value;
        } else {
            auto j = begin + begin_index;
            while (j != begin && *(j - 1) + 1 == *j) {
                --j;
            }
            assert(j != begin);
            reverse_array(j, end - 1);
            my_begin_index = static_cast<int>(input.size());
        }
        if (visited.find(data) == visited.end()) {
            retval.emplace_back(
                Item{ std::move(data), my_begin_index, my_first_value, last_value, step }
            );
        }
    }

    {
        std::vector<int> data(input);
        auto begin = data.begin();
        auto end = data.end();
        auto i = begin + begin_index;
        int my_begin_index = begin_index;
        int my_last_value = last_value;
        while (i != end) {
            if (*i == my_last_value) {
                ++i;
                --my_last_value;
            }
            else {
                break;
            }
        }
        if (i != end) {
            auto j = std::find(i + 1, end, my_last_value);
            assert(j != end);
            reverse_array(i, j);
            --my_last_value;
        }
        else {
            auto j = begin + begin_index;
            while (j != begin && *(j - 1) == *j + 1) {
                --j;
            }
            reverse_array(j, end - 1);
            my_begin_index = static_cast<int>(input.size());
        }
        if (visited.find(data) == visited.end()) {
            retval.emplace_back(
                Item{ std::move(data), my_begin_index, first_value, my_last_value, step }
            );
        }
    }
    return retval;
}


// Note: the elements in the array must be in [1..N] and unique
int minimum_operations(std::vector<int> const& array)
{
    assert(valid(array));
    int retval = 0;
    int n = static_cast<int>(array.size());
    if (n > 1) {
        std::unordered_set<std::vector<int>, VectorHash> visited;
        std::queue<Item> queue;
        queue.emplace(Item{std::vector<int>(array), 0, 1, n, 0});
        while (!queue.empty()) {
            Item item = std::move(queue.front());
            queue.pop();
            if (!in_order(item.data)) {
                visited.insert(item.data);
                auto items = neighbours(item.data, item.begin, item.first, item.last, item.step, visited);
                for (auto& item : items) {
                    queue.emplace(std::move(item));
                }
            } else {
                retval = item.step;
                break;
            }
        }
    }
    return retval;
}

int main()
{
    try {
        {
            std::vector<int> array = { 1, 2, 3 };
            examine(minimum_operations(array) == 0, "minimum_operations is failed at the line: %d\n", __LINE__);
        }
        {
            std::vector<int> array = { 3, 1, 2 };
            examine(minimum_operations(array) == 2, "minimum_operations is failed at the line: %d\n", __LINE__);
        }
        {
            std::vector<int> array = { 1, 2, 5, 4, 3 };
            examine(minimum_operations(array) == 1, "minimum_operations is failed at the line: %d\n", __LINE__);
        }
        {
            std::vector<int> array = { 1, 2, 4, 5, 3 };
            examine(minimum_operations(array) == 2, "minimum_operations is failed at the line: %d\n", __LINE__);
        }
        {
            std::vector<int> array = { 3, 5, 1, 4, 2 };
            examine(minimum_operations(array) == 3, "minimum_operations is failed at the line: %d\n", __LINE__);
        }
        {
            std::vector<int> array = { 3, 1, 4, 2, 5 };
            examine(minimum_operations(array) == 3, "minimum_operations is failed at the line: %d\n", __LINE__);
        }
        {
            std::vector<int> array = { 3, 5, 4, 2, 1 };
            examine(minimum_operations(array) == 3, "minimum_operations is failed at the line: %d\n", __LINE__);
        }
        {
            std::vector<int> array = { 1, 2, 5, 3, 4 };
            examine(minimum_operations(array) == 2, "minimum_operations is failed at the line: %d\n", __LINE__);
        }
        {
            std::vector<int> array = { 4, 6, 1, 2, 5, 3, 7 };
            examine(minimum_operations(array) == 5, "minimum_operations is failed at the line: %d\n", __LINE__);
        }
        {
            std::vector<int> array = { 1, 2, 7, 6, 5, 3, 4 };
            examine(minimum_operations(array) == 3, "minimum_operations is failed at the line: %d\n", __LINE__);
        }
    } catch (std::exception const& e) {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }
    return 0;
}
