#ifndef HEAP_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
#define HEAP_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00

#include <assert.h>
#include <stdint.h>
#include <iterator>
#include <algorithm>
#include <functional>

namespace heap
{
    template <typename I, typename C>
    void sink(
        I begin, I end, I outer,
        C comp = std::greater_equal<typename std::iterator_traits<I>::value_type>())
    {
        int64_t len = std::distance(begin, end);
        assert(outer >= begin && outer != end);
        while (true)
        {
            auto d = std::distance(begin, outer);
            I candidate = outer;
            auto c = (d + 1) << 1;
            for (int64_t repeat = 0; repeat < 2; ++repeat)
            {
                if (c < len)
                {
                    I child = begin + c;
                    if (comp(*candidate, *child))
                    {
                        candidate = child;
                    }
                }
                --c;
            }
            if (candidate != outer)
            {
                std::iter_swap(candidate, outer);
                outer = candidate;
            }
            else
            {
                break;
            }
        }
    }

    template <typename I, typename C>
    void rise(
        I begin, I end, I outer,
        C comp = std::greater_equal<typename std::iterator_traits<I>::value_type>())
    {
        assert(outer >= begin && outer != end);
        while (true)
        {
            int64_t d = std::distance(begin, outer);
            I parent;
            if (d > 0 && comp(*(parent = begin + ((d - 1) >> 1)), *outer))
            {
                std::iter_swap(outer, parent);
                outer = parent;
            }
            else
            {
                break;
            }
        }
    }

    template <typename I, typename C>
    int64_t make_heap(I begin, I end, C c)
    {
        assert(begin <= end);
        int64_t len = static_cast<int64_t>(std::distance(begin, end));
        if (len > 1)
        {
            for (auto i = len >> 1; i >= 0; --i)
            {
                sink<I, C>(begin, end, begin + i, c);
            }
        }
        return len;
    }
} // namespace heap

template <typename RandomIt, typename Compare>
void heap_sort(RandomIt begin, RandomIt end, Compare comp)
{
    int64_t len = heap::make_heap<RandomIt, Compare>(begin, end, comp);
    if (len > 1)
    {
        for (int64_t i = len - 1; i > 0; --i)
        {
            RandomIt last = begin + i;
            std::iter_swap(begin, last);
            heap::sink<RandomIt, Compare>(begin, last, begin, comp);
        }
    }
}

template <typename RandomIt>
void heap_sort(RandomIt begin, RandomIt end)
{
    using Compare = std::less_equal<typename std::iterator_traits<RandomIt>::value_type>;
    return heap_sort<RandomIt, Compare>(begin, end, Compare());
}

#endif //HEAP_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
