#ifndef QUICK_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
#define QUICK_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00

#include <assert.h>
#include <iterator>
#include <algorithm>
#include <functional>
#include <utility>
#include "merge_sort.h"

template <typename RandomIt, typename Less, typename Equal, typename LessOrEqual>
struct V1_1Partitioner
{
    RandomIt operator()(RandomIt begin, RandomIt end)
    {
        auto sentinel = *begin;
        auto ge = end;

        for (RandomIt i = end; i != begin;)
        {
            RandomIt j = i - 1;
            //if (sentinel <= *j)
            if (LessOrEqual()(sentinel, *j))
            {
                std::iter_swap(--ge, j);
            }
            i = j;
        }
        return ge;
    }
};

template <typename RandomIt, typename Less, typename Equal, typename LessOrEqual>
struct V1_2Partitioner
{
    RandomIt operator()(RandomIt begin, RandomIt end)
    {
        RandomIt le = begin;
        auto sentinel = *begin;
        for (RandomIt i = begin + 1; i != end; ++i)
        {
            //if (*i <= sentinel)
            if (LessOrEqual()(*i, sentinel))
            {
                std::iter_swap(++le, i);
            }
        }
        std::iter_swap(begin, le);
        return le;
    }
};

template <typename RandomIt, typename Less, typename Equal, typename LessOrEqual>
struct V1_3Partitioner
{
    RandomIt operator()(RandomIt begin, RandomIt end)
    {
        RandomIt last = end - 1;
        auto sentinel = *last;

        typename std::iterator_traits<RandomIt>::difference_type le = 0;
        for (RandomIt i = begin; i != last; ++i)
        {
            //if (*i <= sentinel)
            if (LessOrEqual()(*i, sentinel))
            {
                std::iter_swap(begin + le, i);
                ++le;
            }
        }
        RandomIt separator = begin + le;
        std::iter_swap(separator, last);
        return separator;
    }
};

template <typename RandomIt, typename Less, typename Equal, typename LessOrEqual>
struct V1_4Partitioner
{
    RandomIt operator()(RandomIt begin, RandomIt end)
    {
        RandomIt last = end - 1;
        auto sentinel = *last;

        RandomIt i = begin;
        //for (; *i < sentinel; ++i)
        for (; Less()(*i, sentinel); ++i)
        {
        }
        if (i != last)
        {
            RandomIt bigger = i;
            for (++i; i != end; ++i)
            {
                //if (*i < sentinel)
                if (Less()(*i, sentinel))
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

template <typename RandomIt, typename Less, typename Equal, typename LessOrEqual>
struct V2_1Partitioner
{
    RandomIt operator()(RandomIt begin, RandomIt end)
    {
        auto sentinel = *begin;

        RandomIt smaller = begin;
        RandomIt bigger = end;
        for (;;)
        {
            //for (++smaller; smaller < bigger && *smaller < sentinel; ++smaller)
            for (++smaller; smaller < bigger && Less()(*smaller, sentinel); ++smaller)
            {
            }
            //for (--bigger; sentinel < *bigger; --bigger)
            for (--bigger; Less()(sentinel, *bigger); --bigger)
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

template <typename RandomIt, typename Less, typename Equal, typename LessOrEqual>
struct V2_2Partitioner
{
    RandomIt operator()(RandomIt begin, RandomIt end)
    {
        auto sentinel = *begin;

        RandomIt smaller = begin;
        RandomIt bigger = end - 1;
        while (smaller < bigger)
        {
            //while (bigger > smaller && sentinel <= *bigger)
            while (bigger > smaller && LessOrEqual()(sentinel, *bigger))
            {
                --bigger;
            }
            std::iter_swap(smaller, bigger);
            //while (smaller < bigger && *smaller <= sentinel)
            while (smaller < bigger && LessOrEqual()(*smaller, sentinel))
            {
                ++smaller;
            }
            std::iter_swap(smaller, bigger);
        }
        return smaller;
    }
};

template <
    template <typename, typename, typename, typename> class Partitioner,
    typename RandomIt,
    typename Less = std::less<typename std::iterator_traits<RandomIt>::value_type>,
    typename Equal = std::equal_to<typename std::iterator_traits<RandomIt>::value_type>,
    typename LessOrEqual = std::less_equal<typename std::iterator_traits<RandomIt>::value_type>
>
void two_way_quick_sort(
    RandomIt begin, RandomIt end,
    size_t factor,
    Less less = Less{}, Equal equal = Equal{}, LessOrEqual le = LessOrEqual{}
)
{
    auto sorting = [=](RandomIt begin, RandomIt end, size_t factor)
    {
        if (factor != 0)
        {
            factor = (factor >> 1) + (factor >> 2);
            auto m = Partitioner<RandomIt, Less, Equal, LessOrEqual>()(begin, end);
            two_way_quick_sort<Partitioner, RandomIt, Less, Equal, LessOrEqual>(
                begin, m, factor, less, equal, le
            );
            two_way_quick_sort<Partitioner, RandomIt, Less, Equal, LessOrEqual>(
                m + 1, end, factor, less, equal, le
            );
        }
        else
        {
            merge_sort<RandomIt, LessOrEqual>(begin, end, le);
        }
    };
    insertion_sort<decltype(sorting), LessOrEqual, RandomIt, size_t>(
        sorting, le, begin, end, factor
    );
}

template <
    template <typename, typename, typename, typename> class Partitioner,
    typename RandomIt,
    typename Less = std::less<typename std::iterator_traits<RandomIt>::value_type>,
    typename Equal = std::equal_to<typename std::iterator_traits<RandomIt>::value_type>,
    typename LessOrEqual = std::less_equal<typename std::iterator_traits<RandomIt>::value_type>
>
void two_way_quick_sort(
    RandomIt begin, RandomIt end,
    Less less = Less{}, Equal equal = Equal{}, LessOrEqual le = LessOrEqual{}
)
{
    two_way_quick_sort<Partitioner, RandomIt, Less, Equal>(
        begin, end, static_cast<size_t>(end - begin), less, equal, le
    );
}

template <typename RandomIt, typename Less, typename Equal, typename LessOrEqual>
struct V3_1Partitioner
{
    std::pair<RandomIt, RandomIt> operator()(RandomIt begin, RandomIt end)
    {
        auto sentinel = *begin;

        RandomIt smaller = begin;
        RandomIt bigger = end - 1;
        for (RandomIt i = begin + 1; i <= bigger;)
        {
            //if (*i < sentinel)
            if (Less()(*i, sentinel))
            {
                std::iter_swap(smaller, i);
                ++smaller;
                ++i;
            }
            //else if (sentinel < *i)
            else if (Less()(sentinel, *i))
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

template <typename RandomIt, typename Less, typename Equal, typename LessOrEqual>
struct V3_2Partitioner
{
    std::pair<RandomIt, RandomIt> operator()(RandomIt begin, RandomIt end)
    {
        auto sentinel = *begin;

        RandomIt equal = begin;
        RandomIt bigger = end;
        for (RandomIt i = begin + 1; i != bigger;)
        {
            //if (*i < sentinel)
            if (Less()(*i, sentinel))
            {
                std::iter_swap(equal++, i++);
            }
            //else if (sentinel < *i)
            else if (Less()(sentinel, *i))
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

template <typename RandomIt, typename Less, typename Equal, typename LessOrEqual>
struct V3_3Partitioner
{
    std::pair<RandomIt, RandomIt> operator()(RandomIt begin, RandomIt end)
    {
        assert(std::distance(begin, end) > 1);
        auto sentinel = *begin;

        RandomIt p = begin + 1, i = p, j = end - 1, q = j + 1;
        while (i <= j)
        {
            //while (*i <= sentinel)
            while (LessOrEqual()(*i, sentinel))
            {
                //if (*i == sentinel)
                if (Equal()(*i, sentinel))
                {
                    std::iter_swap(p++, i);
                }
                ++i;
                if (i > j)
                {
                    break;
                }
            }

            //while (*j >= sentinel)
            while (LessOrEqual()(sentinel, *j))
            {
                //if (*j == sentinel)
                if (Equal()(*j, sentinel))
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

template <typename RandomIt, typename Less, typename Equal, typename LessOrEqual>
struct V3_4Partitioner
{
    std::pair<RandomIt, RandomIt> operator()(RandomIt begin, RandomIt end)
    {
        assert(std::distance(begin, end) > 1);
        auto sentinel = *begin;

        RandomIt equal = begin, i = begin + 1, bigger = end, j = bigger - 1;
        while (i <= j)
        {
            //while (*i <= sentinel)
            while (LessOrEqual()(*i, sentinel))
            {
                //if (*i < sentinel)
                if (Less()(*i, sentinel))
                {
                    std::iter_swap(equal++, i);
                }
                ++i;
                if (i > j)
                {
                    break;
                }
            }

            //while (*j >= sentinel)
            while (LessOrEqual()(sentinel, *j))
            {
                //if (*j > sentinel)
                if (Less()(sentinel, *j))
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
                //assert(*i > sentinel && *j < sentinel);
                assert(Less()(sentinel, *i) && Less()(*j, sentinel));
                std::iter_swap(i, j);
                std::iter_swap(equal++, i++);
                std::iter_swap(--bigger, j--);
            }
        }
        return std::make_pair(equal, bigger);
    }
};

template <
    template <typename, typename, typename, typename> class Partitioner,
    typename RandomIt,
    typename Less = std::less<typename std::iterator_traits<RandomIt>::value_type>,
    typename Equal = std::equal_to<typename std::iterator_traits<RandomIt>::value_type>,
    typename LessOrEqual = std::less_equal<typename std::iterator_traits<RandomIt>::value_type>
>
void three_way_quick_sort(
    RandomIt begin, RandomIt end,
    Less less = Less{}, Equal equal = Equal{}, LessOrEqual le = LessOrEqual{}
)
{
    auto sorting = [=](RandomIt begin, RandomIt end) {
        auto m = Partitioner<RandomIt, Less, Equal, LessOrEqual>()(begin, end);
        three_way_quick_sort<Partitioner, RandomIt, Less, Equal, LessOrEqual>(
            begin, m.first, less, equal, le
        );
        three_way_quick_sort<Partitioner, RandomIt, Less, Equal, LessOrEqual>(
            m.second, end, less, equal, le
        );
    };
    insertion_sort<decltype(sorting), LessOrEqual, RandomIt>(
        sorting, le, begin, end
    );
}

namespace v2
{
    namespace details
    {
        // the return value is the iterator of the max element
        template <typename RandomIt, typename Less>
        RandomIt max(RandomIt begin, RandomIt end)
        {
            RandomIt imax = begin;
            for (RandomIt i = begin + 1; i != end; ++i)
            {
                //if (*imax < *i)
                if (Less()(*imax, *i))
                {
                    imax = i;
                }
            }
            return imax;
        }

        template <typename RandomIt, typename Less>
        RandomIt partition(RandomIt begin, RandomIt end)
        {
            auto sentinel = *begin;

            RandomIt smaller = begin;
            RandomIt bigger = end;
            for (;;)
            {
                //for (++smaller; *smaller < sentinel; ++smaller)
                for (++smaller; Less()(*smaller, sentinel); ++smaller)
                {
                }
                //for (--bigger; sentinel < *bigger; --bigger)
                for (--bigger; Less()(sentinel, *bigger); --bigger)
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

        template <typename RandomIt, typename Less, typename Equal, typename LessOrEqual>
        void two_way_quick_sort(RandomIt begin, RandomIt end, Less less, Equal equal, LessOrEqual le)
        {
            auto sorting = [=](RandomIt begin, RandomIt end) {
                auto m = partition<RandomIt, Less>(begin, end);
                two_way_quick_sort<RandomIt, Less, Equal, LessOrEqual>(begin, m, less, equal, le);
                two_way_quick_sort<RandomIt, Less, Equal, LessOrEqual>(m + 1, end, less, equal, le);
            };
            insertion_sort<decltype(sorting), LessOrEqual, RandomIt>(
                sorting, le, begin, end
            );
        }
    } // namespace details

    template <
        typename RandomIt,
        typename Less = std::less<typename std::iterator_traits<RandomIt>::value_type>,
        typename Equal = std::equal_to<typename std::iterator_traits<RandomIt>::value_type>,
        typename LessOrEqual = std::less_equal<typename std::iterator_traits<RandomIt>::value_type>
    >
    void two_way_quick_sort(
        RandomIt begin, RandomIt end,
        Less less = Less{}, Equal equal = Equal{}, LessOrEqual le = LessOrEqual{}
    )
    {
        auto sorting = [=](RandomIt begin, RandomIt end) {
            RandomIt last = end - 1;
            std::iter_swap(details::max<RandomIt, Less>(begin, end), last);
            details::two_way_quick_sort<RandomIt, Less, Equal, LessOrEqual>(
                begin, last, less, equal, le
            );
        };
        insertion_sort<decltype(sorting), LessOrEqual, RandomIt>(
            sorting, le, begin, end
        );
    }
} // namespace v2

namespace v3
{
    namespace details
    {
        template <
            typename RandomIt,
            size_t THRESHOLD,
            typename Less,
            typename Equal,
            typename LessOrEqual
        >
        void three_way_quick_sort(
            RandomIt begin, RandomIt end, size_t trying, Less less, Equal equal, LessOrEqual le
        )
        {
            auto sorting = [=](RandomIt begin, RandomIt end, size_t trying) {
                if (trying != 0) {
                    auto m = V3_4Partitioner<RandomIt, Less, Equal, LessOrEqual>()(begin, end);
                    if (static_cast<size_t>(m.second - m.first) < THRESHOLD) {
                        --trying;
                    }
                    three_way_quick_sort<RandomIt, THRESHOLD, Less, Equal, LessOrEqual>(
                        begin, m.first, trying, less, equal, le
                    );
                    three_way_quick_sort<RandomIt, THRESHOLD, Less, Equal, LessOrEqual>(
                        m.second, end, trying, less, equal, le
                    );
                } else {
                    v2::two_way_quick_sort<RandomIt, Less, Equal, LessOrEqual>(begin, end, less, equal, le);
                }
            };
            insertion_sort<decltype(sorting), LessOrEqual, RandomIt, size_t>(
                sorting, le, begin, end, trying
            );
        }
    }

    template <size_t THRESHOLD, size_t TRYING>
    struct ThreeWayQuickSort
    {
        template <
            typename RandomIt,
            typename Less = std::less<typename std::iterator_traits<RandomIt>::value_type>,
            typename Equal = std::equal_to<typename std::iterator_traits<RandomIt>::value_type>,
            typename LessOrEqual = std::less_equal<typename std::iterator_traits<RandomIt>::value_type>
        >
        void operator()(
            RandomIt begin, RandomIt end,
            Less less = Less{}, Equal equal = Equal{}, LessOrEqual le = LessOrEqual{}
        )
        {
            details::three_way_quick_sort<RandomIt, THRESHOLD, Less, Equal, LessOrEqual>(
                begin, end, TRYING, less, equal, le
            );
        }
    };
}

namespace v4
{
    namespace details
    {
        template <typename RandomIt, typename Less, typename Equal, typename LessOrEqual>
        auto partition2(RandomIt begin, RandomIt end)
        {
            auto sentinel = *begin;
            RandomIt ge = end;
            size_t count = 0;

            for (RandomIt i = ge; i != begin;)
            {
                RandomIt j = i - 1;
                //if (sentinel <= *j)
                if (LessOrEqual()(sentinel, *j))
                {
                    //count += (sentinel == *j);
                    count += Equal()(sentinel, *j);
                    std::iter_swap(--ge, j);
                }
                i = j;
            }
            return std::make_pair(ge, count);
        }

        template <typename RandomIt, typename Less>
        auto partition3(RandomIt begin, RandomIt end)
        {
            auto sentinel = *begin;

            RandomIt bigger = end;
            for (RandomIt i = begin + 1; i != bigger;)
            {
                //if (*i > sentinel)
                if (Less()(sentinel, *i))
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

    template <
        size_t THRESHOLD,
        typename RandomIt,
        typename Less = std::less<typename std::iterator_traits<RandomIt>::value_type>,
        typename Equal = std::equal_to<typename std::iterator_traits<RandomIt>::value_type>,
        typename LessOrEqual = std::less_equal<typename std::iterator_traits<RandomIt>::value_type>
    >
    void hybird_quick_sort(
        RandomIt begin, RandomIt end,
        Less less = Less{}, Equal equal = Equal{}, LessOrEqual le = LessOrEqual{}
    )
    {
        auto sorting = [=](RandomIt begin, RandomIt end) {
            auto [separator, count] = details::partition2<RandomIt, Less, Equal, LessOrEqual>(
                begin, end
            );
            if (count < THRESHOLD) {
                hybird_quick_sort<THRESHOLD, RandomIt, Less, Equal, LessOrEqual>(
                    begin, separator, less, equal, le
                );
                hybird_quick_sort<THRESHOLD, RandomIt, Less, Equal, LessOrEqual>(
                    separator + 1, end, less, equal, le
                );
            } else {
                hybird_quick_sort<THRESHOLD, RandomIt, Less, Equal, LessOrEqual>(
                    begin, separator, less, equal, le
                );
                auto m = details::partition3<RandomIt, Less>(separator, end);
                hybird_quick_sort<THRESHOLD, RandomIt, Less, Equal, LessOrEqual>(
                    m.second, end, less, equal, le
                );
            }
        };
        insertion_sort<decltype(sorting), LessOrEqual, RandomIt>(sorting, le, begin, end);
    }
}

#endif //QUICK_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
