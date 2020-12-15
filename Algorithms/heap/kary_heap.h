#ifndef KARY_HEAP_GYM_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
#define KARY_HEAP_GYM_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00


#include "binary_heap.h"


namespace heap
{
    namespace details
    {
        template <
            typename I,
            typename C,
            template <typename>
            class KeyTrait,
            template <typename, typename, template <typename> class>
            class Indexer,
            size_t K
        >
        void kary_sink(
            I begin, I end, I outer,
            C comp,
            Indexer<typename std::iterator_traits<I>::value_type, C, KeyTrait> & indexer
        ) {
            auto len = end - begin;
            while (true) {
                decltype(len) d = outer - begin;
                auto candidate = outer;
                decltype(len) c = (d + 1) * K; // the rightmost child
                for (size_t repeat = 0; repeat < K; ++repeat) {
                    if (c < len) {
                        I child = begin + c;
                        if (comp(*candidate, *child)) {
                            candidate = child;
                        }
                    }
                    --c;
                }
                if (candidate != outer) {
                    indexer.set(*candidate, outer - begin);
                    indexer.set(*outer, candidate - begin);
                    std::iter_swap(candidate, outer);
                    outer = candidate;
                } else {
                    break;
                }
            }
        }

        template <
            typename I,
            typename C,
            template <typename>
            class KeyTrait,
            template <typename, typename, template <typename> class>
            class Indexer,
            size_t K
        >
        void kary_rise(
            I begin, I /*end*/, I outer,
            C comp,
            Indexer<typename std::iterator_traits<I>::value_type, C, KeyTrait> & indexer
        ) {
            while (true) {
                auto d = outer - begin;
                I parent;
                if (d > 0 && comp(*(parent = begin + ((d - 1) / K)), *outer)) {
                    indexer.set(*parent, outer - begin);
                    indexer.set(*outer, parent - begin);
                    std::iter_swap(outer, parent);
                    outer = parent;
                } else {
                    break;
                }
            }
        }

        template <
            typename I,
            typename C,
            template <typename>
            class KeyTrait,
            template <typename, typename, template <typename> class>
            class Indexer,
            size_t K
        >
        int64_t make_kary_heap(
            I begin, I end,
            C comp,
            Indexer<typename std::iterator_traits<I>::value_type, C, KeyTrait> & indexer
        ) {
            assert(begin <= end);
            int64_t len = static_cast<int64_t>(end - begin);
            if (len > 1) {
                for (auto i = (len + K - 1) / K; i >= 0; --i) {
                    kary_sink<I, C, KeyTrait, Indexer, K>(begin, end, begin + i, comp, indexer);
                }
            }
            return len;
        }
    }

    template <
        size_t K,
        typename T,
        typename C = std::greater_equal<T>,
        template <typename>
        class KeyTrait = details::KeyTrait
    >
    class KaryHeap
    {
        std::vector<T> m_heap;
        details::Indexer<T, C, KeyTrait> m_indexer;

        template <typename I>
        KaryHeap(I begin, I end)
        {
            m_heap.reserve(end-begin);
            for (auto i = begin; i != end; ++i) {
                insert(*i);
            }
        }
    public:
        KaryHeap(size_t n=0)
        {
            if (n > 0) {
                m_heap.reserve(n);
            }
        }
        KaryHeap(KaryHeap<K, T, C, KeyTrait> const&) = default;
        KaryHeap(KaryHeap<K, T, C, KeyTrait>&&) = default;
        KaryHeap<K, T, C, KeyTrait>& operator=(KaryHeap<K, T, C, KeyTrait> const&) = default;
        KaryHeap<K, T, C, KeyTrait>& operator=(KaryHeap<K, T, C, KeyTrait>&&) = default;

        template <typename I>
        static KaryHeap<K, T, C, KeyTrait> make_heap(I begin, I end)
        {
            return KaryHeap<K, T, C, KeyTrait>(begin, end);
        }

        void insert(const T& t)
        {
            if (!m_indexer.contains(t)) {
                size_t n = m_heap.size();
                m_heap.push_back(t);
                m_indexer.set(t, n);
                details::kary_rise<typename std::vector<T>::iterator, C, KeyTrait, details::Indexer, K>(
                    m_heap.begin(), m_heap.end(), m_heap.begin() + n, C(), m_indexer
                );
            } else {
                size_t i = m_indexer.get(t);
                auto old = m_heap[i];
                replace(old, t);
            }
        }

        const T& minimum() const { return m_heap[0]; }
        void pop_min()
        {
            size_t n = m_heap.size();
            if (n > 0) {
                --n;
                auto begin = m_heap.begin();
                auto end = begin + n;
                m_indexer.erase(*begin);
                if (n != 0) {
                    std::iter_swap(begin, end);
                    m_indexer.set(*begin, 0);
                    details::kary_sink<typename std::vector<T>::iterator, C, KeyTrait, details::Indexer, K>(
                        begin, end, begin, C(), m_indexer
                    );
                }
                m_heap.pop_back();
            }
        }

        KaryHeap<K, T, C, KeyTrait> & operator+=(KaryHeap<K, T, C, KeyTrait> const& other)
        {
            for (auto i = other.m_heap.begin(), ie = other.m_heap.end(); i != ie; ++i) {
                insert(*i);
            }
            return *this;
        }

        void replace(const T& _old, const T& _new) // throw(std::out_of_range)
        {
            bool should_rise = C()(_old, _new);
            size_t index = m_indexer.get(_old);
            m_heap[index] = _new;
            m_indexer.erase(_old);
            m_indexer.set(_new, index);
            if (should_rise) {
                details::kary_rise<typename std::vector<T>::iterator, C, KeyTrait, details::Indexer, K>(
                    m_heap.begin(), m_heap.end(), m_heap.begin() + index, C(), m_indexer
                );
            } else {
                details::kary_sink<typename std::vector<T>::iterator, C, KeyTrait, details::Indexer, K>(
                    m_heap.begin(), m_heap.end(), m_heap.begin() + index, C(), m_indexer
                );
            }
        }

        void erase(const T& t) // throw(std::out_of_range)
        {
            size_t n = size();
            size_t index = m_indexer.get(t);
            m_indexer.erase(t);
            --n;
            if (n != 0) {
                auto begin = m_heap.begin();
                auto end = begin + n;
                m_heap[index] = *end;
                m_indexer.set(m_heap[index], index);
                details::kary_sink<typename std::vector<T>::iterator, C, KeyTrait, details::Indexer, K>(
                    begin, end, begin + index, C(), m_indexer
                );
            }
            m_heap.pop_back();
        }

        const T& operator[](const T& t) const
        {
            size_t index = m_indexer.get(t);
            return m_heap[index];
        }

        bool contains(const T& t) const { return m_indexer.contains(t); }
        size_t size() const { return m_heap.size(); }
        bool empty() const { return m_heap.empty(); }
        void swap(KaryHeap<K, T, C, KeyTrait>& other)
        {
            m_heap.swap(other.m_heap);
            m_indexer.swap(other.m_indexer);
        }
    };
}

#endif //KARY_HEAP_GYM_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
