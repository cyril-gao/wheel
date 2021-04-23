#ifndef MERGE_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
#define MERGE_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00

#include <iterator>
#include <algorithm>
#include <functional>
#include <vector>
#include "insertion_sort.h"

template <typename RandomIt, typename Compare>
void merge(RandomIt b1, RandomIt e1, RandomIt b2, RandomIt e2, Compare comp)
{
    typedef typename std::iterator_traits<RandomIt>::value_type value_type;
    std::vector<value_type> a1(b1, e1), a2(b2, e2);
    RandomIt i = b1;

    b1 = a1.begin(), e1 = a1.end();
    b2 = a2.begin(), e2 = a2.end();
    for (; b1 != e1 && b2 != e2; ++i)
    {
        if (comp(*b1, *b2))
        {
            *i = *b1++;
        }
        else
        {
            *i = *b2++;
        }
    }

    if (b2 != e2)
    {
        b1 = b2;
        e1 = e2;
    }
    while (b1 != e1)
    {
        *i++ = *b1++;
    }
}

template <typename RandomIt, typename Compare>
void merge_sort(RandomIt begin, RandomIt end, Compare comp)
{
    auto sorting = [](RandomIt begin, RandomIt end, Compare comp) {
        auto distance = std::distance(begin, end);
        RandomIt mid = begin + (distance + 1) / 2;
        merge_sort(begin, mid, comp);
        merge_sort(mid, end, comp);
        merge(begin, mid, mid, end, comp);
    };
    insertion_sort<decltype(sorting), RandomIt, Compare>(sorting, begin, end, comp);
}

template <typename RandomIt>
void merge_sort(RandomIt begin, RandomIt end)
{
    using Compare = std::less_equal<typename std::iterator_traits<RandomIt>::value_type>;
    return merge_sort<RandomIt, Compare>(begin, end, Compare());
}

#endif //MERGE_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
