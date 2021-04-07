#ifndef INSERTION_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
#define INSERTION_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00

#include <stdint.h>
#include <iterator>

template <typename RandomIt, typename Compare>
inline void insertion_sort(RandomIt begin, RandomIt end, Compare comp)
{
    for (RandomIt i = begin + 1; i < end; ++i)
    {
        auto sentinel = *i;
        int64_t j = static_cast<int64_t>(std::distance(begin, i)) - 1;
        for (; j >= 0; --j)
        {
            if (comp(sentinel, *(begin + j)))
            {
                *(begin + j + 1) = *(begin + j);
            }
            else
            {
                break;
            }
        }
        *(begin + (j + 1)) = sentinel;
    }
}

template <typename RandomIt>
inline void insertion_sort(RandomIt begin, RandomIt end)
{
    using Compare = std::less_equal<typename std::iterator_traits<RandomIt>::value_type>;
    insertion_sort<RandomIt, Compare>(begin, end, Compare());
}

template <typename RandomIt>
struct SortingThreshold
{
    enum
    {
        THRESHOLD = 256 / sizeof(typename std::iterator_traits<RandomIt>::value_type)
    };
};

template <typename Sorting, typename RandomIt, typename... Args>
void insertion_sort(Sorting sorting, RandomIt begin, RandomIt end, Args... args)
{
    auto diff = std::distance(begin, end);
    if (diff > SortingThreshold<RandomIt>::THRESHOLD) {
        sorting(begin, end, args...);
    }
    else if (diff > 0) {
        insertion_sort<RandomIt>(begin, end);
    }
}

template <typename Sorting, typename Compare, typename RandomIt, typename... Args>
void insertion_sort(Sorting sorting, Compare comp, RandomIt begin, RandomIt end, Args... args)
{
    auto diff = std::distance(begin, end);
    if (diff > SortingThreshold<RandomIt>::THRESHOLD) {
        sorting(begin, end, args...);
    }
    else if (diff > 0) {
        insertion_sort<RandomIt>(begin, end, comp);
    }
}

#endif //INSERTION_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
