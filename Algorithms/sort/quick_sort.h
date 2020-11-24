#ifndef QUICK_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
#define QUICK_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00

#include <assert.h>
#include <iterator>
#include <algorithm>
#include <utility>
#include "insertion_sort.h"

template <typename RandomIt>
struct V1_1Partitioner
{
    RandomIt operator()(RandomIt begin, RandomIt end)
    {
        auto distance = std::distance(begin, end);
        auto sentinel = *begin;
        RandomIt ge = begin + distance;

        for (RandomIt i = ge; i != begin;)
        {
            RandomIt j = i - 1;
            if (sentinel <= *j)
            {
                std::iter_swap(--ge, j);
            }
            i = j;
        }
        return ge;
    }
};

template <typename RandomIt>
struct V1_2Partitioner
{
    RandomIt operator()(RandomIt begin, RandomIt end)
    {
        RandomIt le = begin;
        auto sentinel = *begin;
        for (RandomIt i = begin + 1; i != end; ++i)
        {
            if (*i <= sentinel)
            {
                std::iter_swap(++le, i);
            }
        }
        std::iter_swap(begin, le);
        return le;
    }
};

template <typename RandomIt>
struct V1_3Partitioner
{
    RandomIt operator()(RandomIt begin, RandomIt end)
    {
        auto distance = std::distance(begin, end);
        RandomIt last = begin + distance - 1;
        auto sentinel = *last;

        int64_t smaller = -1;
        for (RandomIt i = begin; i != last; ++i)
        {
            if (*i <= sentinel)
            {
                ++smaller;
                std::iter_swap(begin + smaller, i);
            }
        }
        RandomIt separator = begin + (smaller + 1);
        std::iter_swap(separator, last);
        return separator;
    }
};

template <typename RandomIt>
struct V1_4Partitioner
{
    RandomIt operator()(RandomIt begin, RandomIt end)
    {
        auto distance = std::distance(begin, end);
        RandomIt last = begin + distance - 1;
        auto sentinel = *last;

        RandomIt i = begin;
        for (; *i < sentinel; ++i)
        {
        }
        if (i != last)
        {
            RandomIt bigger = i;
            for (++i; i != end; ++i)
            {
                if (*i < sentinel)
                {
                    std::iter_swap(bigger++, i);
                }
            }
            std::iter_swap(bigger, last);
            i = bigger;
        }
        return i;
    }
};

template <typename RandomIt>
struct V2_1Partitioner
{
    RandomIt max(RandomIt begin, RandomIt end)
    {
        auto sentinel = *begin;
        RandomIt maxIndex = begin;
        for (RandomIt i = begin + 1; i != end; ++i)
        {
            if (sentinel < *i)
            {
                sentinel = *i;
                maxIndex = i;
            }
        }
        return maxIndex;
    }

    RandomIt operator()(RandomIt begin, RandomIt end)
    {
        auto distance = std::distance(begin, end);
        //RandomIt maxIndex = max(begin, end);
        //std::iter_swap(maxIndex, begin + distance - 1);
        auto sentinel = *begin;

        RandomIt smaller = begin;
        RandomIt bigger = begin + distance;
        for (;;)
        {
            for (++smaller; smaller < bigger && *smaller < sentinel; ++smaller)
            {
            }
            for (--bigger; sentinel < *bigger; --bigger)
            {
            }
            if (smaller < bigger)
            {
                std::iter_swap(smaller, bigger);
            }
            else
            {
                break;
            }
        }
        std::iter_swap(begin, bigger);
        return bigger;
    }
};

template <typename RandomIt>
struct V2_2Partitioner
{
    RandomIt operator()(RandomIt begin, RandomIt end)
    {
        auto distance = std::distance(begin, end);
        auto sentinel = *begin;

        RandomIt smaller = begin;
        RandomIt bigger = begin + distance - 1;
        while (smaller < bigger)
        {
            while (bigger > smaller && sentinel <= *bigger)
            {
                --bigger;
            }
            std::iter_swap(smaller, bigger);
            while (smaller < bigger && *smaller <= sentinel)
            {
                ++smaller;
            }
            std::iter_swap(smaller, bigger);
        }
        return smaller;
    }
};

template <template <typename> class Partitioner, typename RandomIt>
void two_way_quick_sort(RandomIt begin, RandomIt end)
{
    enum
    {
        THRESHOLD = 512 / sizeof(typename std::iterator_traits<RandomIt>::value_type)
    };
    auto diff = std::distance(begin, end);
    if (diff > THRESHOLD)
    {
        auto m = Partitioner<RandomIt>()(begin, end);
        two_way_quick_sort<Partitioner, RandomIt>(begin, m);
        two_way_quick_sort<Partitioner, RandomIt>(m + 1, end);
    }
    else
    {
        insertion_sort(begin, end);
    }
}

template <typename RandomIt>
struct V3_1Partitioner
{
    std::pair<RandomIt, RandomIt> operator()(RandomIt begin, RandomIt end)
    {
        auto distance = std::distance(begin, end);
        auto sentinel = *begin;

        RandomIt smaller = begin;
        RandomIt bigger = begin + distance - 1;
        for (RandomIt i = begin + 1; i <= bigger;)
        {
            if (*i < sentinel)
            {
                std::iter_swap(smaller, i);
                ++smaller;
                ++i;
            }
            else if (sentinel < *i)
            {
                std::iter_swap(i, bigger);
                --bigger;
            }
            else
            {
                ++i;
            }
        }
        return std::make_pair(smaller, bigger + 1);
    }
};

template <typename RandomIt>
struct V3_2Partitioner
{
    std::pair<RandomIt, RandomIt> operator()(RandomIt begin, RandomIt end)
    {
        auto distance = std::distance(begin, end);
        auto sentinel = *begin;

        RandomIt equal = begin;
        RandomIt bigger = begin + distance;
        for (RandomIt i = begin + 1; i != bigger;)
        {
            if (*i < sentinel)
            {
                std::iter_swap(equal++, i++);
            }
            else if (sentinel < *i)
            {
                std::iter_swap(--bigger, i);
            }
            else
            {
                ++i;
            }
        }
        return std::make_pair(equal, bigger);
    }
};

template <typename RandomIt>
struct V3_3Partitioner
{
    std::pair<RandomIt, RandomIt> operator()(RandomIt begin, RandomIt end)
    {
        auto distance = std::distance(begin, end);
        assert(distance > 1);
        auto sentinel = *begin;

        RandomIt p = begin + 1, i = p, j = begin + distance - 1, q = j + 1;
        while (i <= j)
        {
            while (*i <= sentinel)
            {
                if (*i == sentinel)
                {
                    std::iter_swap(p++, i);
                }
                ++i;
                if (i > j)
                {
                    break;
                }
            }

            while (*j >= sentinel)
            {
                if (*j == sentinel)
                {
                    std::iter_swap(--q, j);
                }
                --j;
                if (j < i)
                {
                    break;
                }
            }
            if (i < j)
            {
                std::iter_swap(i, j);
            }
        }

        while (p > begin)
        {
            std::iter_swap(--i, --p);
        }
        while (q != end)
        {
            std::iter_swap(++j, q++);
        }
        return std::make_pair(i, j + 1);
    }
};

template <typename RandomIt>
struct V3_4Partitioner
{
    std::pair<RandomIt, RandomIt> operator()(RandomIt begin, RandomIt end)
    {
        auto distance = std::distance(begin, end);
        assert(distance > 1);
        auto sentinel = *begin;

        RandomIt equal = begin, i = begin + 1, bigger = begin + distance, j = bigger - 1;
        while (i <= j)
        {
            while (*i <= sentinel)
            {
                if (*i < sentinel)
                {
                    std::iter_swap(equal++, i);
                }
                ++i;
                if (i > j)
                {
                    break;
                }
            }

            while (*j >= sentinel)
            {
                if (*j > sentinel)
                {
                    std::iter_swap(--bigger, j);
                }
                --j;
                if (j < i)
                {
                    break;
                }
            }
            if (i < j)
            {
                assert(*i > sentinel && *j < sentinel);
                std::iter_swap(i, j);
                std::iter_swap(equal++, i++);
                std::iter_swap(--bigger, j--);
            }
        }
        return std::make_pair(
            equal,
            bigger != (begin + distance) ? bigger : end);
    }
};

template <template <typename> class Partitioner, typename RandomIt>
void three_way_quick_sort(RandomIt begin, RandomIt end)
{
    enum
    {
        THRESHOLD = 512 / sizeof(typename std::iterator_traits<RandomIt>::value_type)
    };
    auto diff = std::distance(begin, end);
    if (diff > THRESHOLD)
    {
        auto m = Partitioner<RandomIt>()(begin, end);
        three_way_quick_sort<Partitioner, RandomIt>(begin, m.first);
        three_way_quick_sort<Partitioner, RandomIt>(m.second, end);
    }
    else
    {
        insertion_sort(begin, end);
    }
}

#endif //QUICK_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
