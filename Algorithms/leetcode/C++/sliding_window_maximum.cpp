#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <time.h>

#include <iterator>
#include <algorithm>
#include <functional>
#include <vector>
#include <unordered_map>

#include "check.h"


namespace heap
{
    template <typename T, typename I>
    class NullObject
    {
    public:
        void set(const T & /*key*/, I /*index*/) {}
    };

    template <typename I, typename C, typename Indexer = NullObject<typename std::iterator_traits<I>::value_type, I>>
    void sink(
        I begin, I end, I outer,
        C comp = std::greater_equal<typename std::iterator_traits<I>::value_type>(),
        Indexer * indexer = nullptr
    ) {
        auto len = std::distance(begin, end);
        assert(outer >= begin && outer != end);
        while (true) {
            auto d = std::distance(begin, outer);
            I candidate = outer;
            auto c = (d + 1) << 1;
            for (int repeat = 0; repeat < 2; ++repeat) {
                if (c < len) {
                    I child = begin + c;
                    if (comp(*candidate, *child)) {
                        candidate = child;
                    }
                }
                --c;
            }
            if (candidate != outer) {
                if (indexer != nullptr) {
                    indexer->set(*candidate, outer);
                    indexer->set(*outer, candidate);
                }
                std::iter_swap(candidate, outer);
                outer = candidate;
            } else {
                break;
            }
        }
    }

    template <typename I, typename C, typename Indexer = NullObject<typename std::iterator_traits<I>::value_type, I>>
    void rise(
        I begin, I end, I outer,
        C comp = std::greater_equal<typename std::iterator_traits<I>::value_type>(),
        Indexer * indexer = nullptr
    ) {
        assert(outer >= begin && outer != end);
        while (true) {
            auto d = std::distance(begin, outer);
            I parent;
            if (d > 0 && comp(*(parent = begin + ((d - 1) >> 1)), *outer)) {
                if (indexer != nullptr) {
                    indexer->set(*parent, outer);
                    indexer->set(*outer, parent);
                }
                std::iter_swap(outer, parent);
                outer = parent;
            } else {
                break;
            }
        }
    }

    template <typename I, typename C, typename Indexer = NullObject<typename std::iterator_traits<I>::value_type, I>>
    int64_t make_heap(I begin, I end, C c, Indexer * indexer = nullptr)
    {
        assert(begin <= end);
        int64_t len = static_cast<int64_t>(std::distance(begin, end));
        if (len > 1) {
            for (auto i = len >> 1; i >= 0; --i) {
                sink<I, C, Indexer>(begin, end, begin + i, c, indexer);
            }
        }
        return len;
    }
} // namespace heap

namespace
{
    template <typename T>
    struct Item
    {
        size_t index;
        T      value;
        Item(size_t i, T v): index(i), value(v) {}
        Item() : index(SIZE_MAX) {}
        Item(const Item<T>&) = default;
        Item<T>& operator=(const Item<T>&) = default;

        bool operator==(Item rhs) const noexcept
        {
            return index == rhs.index;
        }

        operator size_t() const noexcept { return index; }
    };

    template <typename T>
    struct ItemValueComparator
    {
        bool operator()(Item<T> lhs, Item<T> rhs) const noexcept
        {
            return lhs.value < rhs.value;
        }
    };

    template <typename T>
    class Indexer
    {
        using index_t = typename std::vector<Item<T>>::iterator;
        std::unordered_map<size_t, index_t> m_map;
    public:
        void set(size_t index_in_array, index_t index_in_heap)
        {
            m_map[index_in_array] = index_in_heap;
        }
        void remove(size_t index_in_array)
        {
            m_map.erase(index_in_array);
        }
        index_t get(size_t index_in_array)
        {
            return m_map[index_in_array];
        }
    };

    template <typename T, typename Indexer>
    auto make_buffer(std::vector<T> const& input, size_t k, Indexer & indexer)
    {
        std::vector<Item<T>> buf;
        buf.reserve(k);
        for (size_t i = 0; i < k; ++i) {
            buf.emplace_back(Item<T>(i, input[i]));
        }
        for (size_t i = 0; i < k; ++i) {
            indexer.set(i, buf.begin() + i);
        }
        return buf;
    }
}


/*
You are given an array of integers nums, there is a sliding window of size k which is moving from the very left of the array to the very right. You can only see the k numbers in the window. Each time the sliding window moves right by one position.

Return the max sliding window.

 

Example 1:

Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
Output: [3,3,5,5,6,7]
Explanation: 
Window position                Max
---------------               -----
[1  3  -1] -3  5  3  6  7       3
 1 [3  -1  -3] 5  3  6  7       3
 1  3 [-1  -3  5] 3  6  7       5
 1  3  -1 [-3  5  3] 6  7       5
 1  3  -1  -3 [5  3  6] 7       6
 1  3  -1  -3  5 [3  6  7]      7
Example 2:

Input: nums = [1], k = 1
Output: [1]
Example 3:

Input: nums = [1,-1], k = 1
Output: [1,-1]
Example 4:

Input: nums = [9,11], k = 2
Output: [11]
Example 5:

Input: nums = [4,-2], k = 2
Output: [4]
*/

template <typename T>
std::vector<T> max_sliding_window(std::vector<T> const& input, size_t k)
{
    assert(!input.empty() && k > 0);
    std::vector<T> retval;
    size_t n = input.size();
    if (n > k) {
        Indexer<T> indexer;
        std::vector<Item<T>> buf = make_buffer<T, Indexer<T>>(input, k, indexer);
        heap::make_heap<typename std::vector<Item<T>>::iterator, ItemValueComparator<T>, Indexer<T>>(
            buf.begin(), buf.end(), ItemValueComparator<T>(), &indexer
        );
        retval.reserve(n-k+1);
        for (size_t i = 0, j = k; j < n; ++i, ++j) {
            retval.push_back(buf[0].value);
            auto pos = indexer.get(i);
            auto old = *pos;
            *pos = Item<T>(j, input[j]);
            indexer.set(j, pos);
            indexer.remove(i);
            if (pos->value > old.value) {
                heap::rise<typename std::vector<Item<T>>::iterator, ItemValueComparator<T>, Indexer<T>>(
                    buf.begin(), buf.end(), pos, ItemValueComparator<T>(), &indexer
                );
            } else if (pos->value < old.value) {
                heap::sink<typename std::vector<Item<T>>::iterator, ItemValueComparator<T>, Indexer<T>>(
                    buf.begin(), buf.end(), pos, ItemValueComparator<T>(), &indexer
                );
            }
        }
        retval.push_back(buf[0].value);
    } else {
        if (n > 0) {
            T t{ input[0] };
            for (size_t i = 1; i < n; ++i) {
                if (t < input[i]) {
                    t = input[i];
                }
            }
            retval.push_back(t);
        }
    }
    return retval;
}


int main()
{
    {
        std::vector<int> input = {1,3,-1,-3,5,3,6,7};
        std::vector<int> expectation = {3,3,5,5,6,7};
        auto result = max_sliding_window<int>(input, 3);
        examine(result == expectation, "max_sliding_window is failed at the line: %d\n", __LINE__);

        result = max_sliding_window<int>(input, input.size());
        examine(result.size() == 1 && result[0] == 7, "max_sliding_window is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> input = { 1 };
        std::vector<int> expectation = { 1 };
        auto result = max_sliding_window<int>(input, 1);
        examine(result == expectation, "max_sliding_window is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> input = { 1, -1 };
        std::vector<int> expectation = { 1, -1 };
        auto result = max_sliding_window<int>(input, 1);
        examine(result == expectation, "max_sliding_window is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> input = { 9, 11 };
        std::vector<int> expectation = { 11 };
        auto result = max_sliding_window<int>(input, 2);
        examine(result == expectation, "max_sliding_window is failed at the line: %d\n", __LINE__);
    }
    {
        std::vector<int> input = { 4, -2 };
        std::vector<int> expectation = { 4 };
        auto result = max_sliding_window<int>(input, 2);
        examine(result == expectation, "max_sliding_window is failed at the line: %d\n", __LINE__);
    }
    {
        srand(static_cast<unsigned int>(time(nullptr)));
        auto brute_forch_method = [](std::vector<int> const& input, size_t k) {
            std::vector<int> retval;
            size_t n = input.size();
            if (n > k) {
                retval.reserve(input.size() - k + 1);
                auto begin = input.begin(), end = begin + k;
                for (size_t i = 0, ie = (n-k+1); i < ie; ++i, ++begin, ++end) {
                    auto r = std::max_element(begin, end);
                    retval.push_back(*r);
                }
            }
            else {
                if (n > 0) {
                    retval.push_back(*std::max_element(input.begin(), input.end()));
                }
            }
            return retval;
        };
        for (int i = 0; i < 100; ++i) {
            unsigned int n = rand() % 10000;
            if (n < 5) {
                n = 1734941;
            }
            std::vector<int> input(n);
            std::for_each(input.begin(), input.end(), [](auto& v) { v = rand(); });
            for (size_t j = 0; j < 100; ++j) {
                size_t k = 0;
                while (k == 0) {
                    k = static_cast<size_t>(rand()) % n;
                }
                auto r1 = max_sliding_window<int>(input, k);
                auto r2 = brute_forch_method(input, k);
                examine(r1 == r2, "max_sliding_window is failed at the line: %d\n", __LINE__);
            }
        }
    }
    printf("OK\n");
    return 0;
}
