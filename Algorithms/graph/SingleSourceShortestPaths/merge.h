//merge.h
#ifndef MERGE_GYM_H
#define MERGE_GYM_H

#include <assert.h>
#include <stdint.h>

#include <algorithm>
#include <iterator>
#include <type_traits>

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
                //if (std::is_constant_evaluated() && indexer != nullptr) {
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
                //if (std::is_constant_evaluated() && indexer != nullptr) {
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

    template <typename I>
    void sort(I begin, I end)
    {
        using Comparator = std::less_equal<typename std::iterator_traits<I>::value_type>;
        if (begin < end) {
            int64_t len = heap::make_heap<I, Comparator>(begin, end, Comparator());
            if (len > 1) {
                for (int64_t i = len - 1; i > 0; --i) {
                    I last = begin + i;
                    std::iter_swap(begin, last);
                    sink<I, Comparator>(begin, last, begin, Comparator());
                }
            }
        }
    }
}

#endif