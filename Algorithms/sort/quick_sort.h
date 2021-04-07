#ifndef QUICK_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
#define QUICK_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00

#include <assert.h>
#include <iterator>
#include <algorithm>
#include <utility>
#include "merge_sort.h"

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

        int64_t le = -1;
        for (RandomIt i = begin; i != last; ++i)
        {
            if (*i <= sentinel)
            {
                ++le;
                std::iter_swap(begin + le, i);
            }
        }
        RandomIt separator = begin + (le + 1);
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
    RandomIt operator()(RandomIt begin, RandomIt end)
    {
        auto distance = std::distance(begin, end);
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
void two_way_quick_sort(RandomIt begin, RandomIt end, size_t factor)
{
    auto sorting = [](RandomIt begin, RandomIt end, size_t factor) {
        if (factor != 0) {
            factor = (factor >> 1) + (factor >> 2);
            auto m = Partitioner<RandomIt>()(begin, end);
            two_way_quick_sort<Partitioner, RandomIt>(begin, m, factor);
            two_way_quick_sort<Partitioner, RandomIt>(m + 1, end, factor);
        }
        else {
            merge_sort<RandomIt>(begin, end);
        }
    };
    insertion_sort<decltype(sorting), RandomIt, size_t>(sorting, begin, end, factor);
}

template <template <typename> class Partitioner, typename RandomIt>
void two_way_quick_sort(RandomIt begin, RandomIt end)
{
    two_way_quick_sort<Partitioner, RandomIt>(begin, end, static_cast<size_t>(end - begin));
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
            bigger != (begin + distance) ? bigger : end
        );
    }
};

template <template <typename> class Partitioner, typename RandomIt>
void three_way_quick_sort(RandomIt begin, RandomIt end)
{
    auto sorting = [](RandomIt begin, RandomIt end) {
        auto m = Partitioner<RandomIt>()(begin, end);
        three_way_quick_sort<Partitioner, RandomIt>(begin, m.first);
        three_way_quick_sort<Partitioner, RandomIt>(m.second, end);
    };
    insertion_sort<decltype(sorting), RandomIt>(sorting, begin, end);
}

namespace v2
{
    namespace details
    {
        template <typename RandomIt>
        RandomIt max(RandomIt begin, RandomIt end)
        {
            //auto sentinel = *begin;
            RandomIt maxIndex = begin;
            for (RandomIt i = begin + 1; i != end; ++i)
            {
                //if (sentinel < *i)
                if (*maxIndex < *i)
                {
                    //sentinel = *i;
                    maxIndex = i;
                }
            }
            return maxIndex;
        }

        template <typename RandomIt>
        RandomIt partition(RandomIt begin, RandomIt end)
        {
            auto distance = std::distance(begin, end);
            auto sentinel = *begin;

            RandomIt smaller = begin;
            RandomIt bigger = begin + distance;
            for (;;)
            {
                for (++smaller; *smaller < sentinel; ++smaller)
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

        template <typename RandomIt>
        void two_way_quick_sort(RandomIt begin, RandomIt end)
        {
            auto sorting = [](RandomIt begin, RandomIt end) {
                auto m = partition<RandomIt>(begin, end);
                two_way_quick_sort<RandomIt>(begin, m);
                two_way_quick_sort<RandomIt>(m + 1, end);
            };
            insertion_sort<decltype(sorting), RandomIt>(sorting, begin, end);
        }
    } // namespace details

    template <typename RandomIt>
    void two_way_quick_sort(RandomIt begin, RandomIt end)
    {
        auto sorting = [](RandomIt begin, RandomIt end) {
            RandomIt last = begin + (std::distance(begin, end) - 1);
            RandomIt imax = details::max(begin, end);
            std::iter_swap(imax, last);
            details::two_way_quick_sort<RandomIt>(begin, last);
        };
        insertion_sort<decltype(sorting), RandomIt>(sorting, begin, end);
    }
} // namespace v2

namespace v3
{
    namespace details
    {
        template <typename RandomIt, size_t THRESHOLD>
        void three_way_quick_sort(RandomIt begin, RandomIt end, size_t trying)
        {
            auto sorting = [](RandomIt begin, RandomIt end, size_t trying) {
                if (trying != 0) {
                    auto m = V3_4Partitioner<RandomIt>()(begin, end);
                    if (static_cast<size_t>(m.second - m.first) < THRESHOLD) {
                        --trying;
                    }
                    three_way_quick_sort<RandomIt, THRESHOLD>(begin, m.first, trying);
                    three_way_quick_sort<RandomIt, THRESHOLD>(m.second, end, trying);
                } else {
                    v2::two_way_quick_sort(begin, end);
                }
            };
            insertion_sort<decltype(sorting), RandomIt, size_t>(sorting, begin, end, trying);
        }
    }

    template <size_t THRESHOLD, size_t TRYING>
    struct ThreeWayQuickSort
    {
        template <typename RandomIt>
        void operator()(RandomIt begin, RandomIt end)
        {
            details::three_way_quick_sort<RandomIt, THRESHOLD>(begin, end, TRYING);
        }
    };
}

namespace v4
{
    namespace details
    {
        template <typename RandomIt>
        auto partition2(RandomIt begin, RandomIt end)
        {
            auto distance = std::distance(begin, end);
            auto sentinel = *begin;
            RandomIt ge = begin + distance;
            size_t count = 0;

            for (RandomIt i = ge; i != begin;)
            {
                RandomIt j = i - 1;
                if (sentinel <= *j)
                {
                    count += (sentinel == *j);
                    std::iter_swap(--ge, j);
                }
                i = j;
            }
            return std::make_pair(ge, count);
        }

        template <typename RandomIt>
        auto partition3(RandomIt begin, RandomIt end)
        {
            auto distance = std::distance(begin, end);
            auto sentinel = *begin;

            RandomIt bigger = begin + distance;
            for (RandomIt i = begin + 1; i != bigger;)
            {
                if (*i > sentinel)
                {
                    std::iter_swap(--bigger, i);
                }
                else
                {
                    ++i;
                }
            }
            return std::make_pair(begin, bigger);
        }
    }

    template <size_t THRESHOLD, typename RandomIt>
    void hybird_quick_sort(RandomIt begin, RandomIt end)
    {
        auto sorting = [](RandomIt begin, RandomIt end) {
            auto [separator, count] = details::partition2<RandomIt>(begin, end);
            if (count < THRESHOLD) {
                hybird_quick_sort<THRESHOLD, RandomIt>(begin, separator);
                hybird_quick_sort<THRESHOLD, RandomIt>(separator + 1, end);
            } else {
                hybird_quick_sort<THRESHOLD, RandomIt>(begin, separator);
                auto m = details::partition3<RandomIt>(separator, end);
                hybird_quick_sort<THRESHOLD, RandomIt>(m.second, end);
            }
        };
        insertion_sort<decltype(sorting), RandomIt>(sorting, begin, end);
    }
}

#endif //QUICK_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
