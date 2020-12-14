#ifndef BINARY_HEAP_GYM_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
#define BINARY_HEAP_GYM_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00

#include <stdint.h>
#include <assert.h>

#include <algorithm>
#include <functional>
#include <iterator>
#include <type_traits>
#include <vector>
#include <unordered_map>


namespace heap
{
    namespace details
    {
        template <typename T>
        struct KeyTrait
        {
            using key_type = T;
            key_type key(const T& t) const { return t; }
            void swap(KeyTrait<T>&) {}
        };

        template <
            typename T,
            typename C,
            template <typename>
            class KeyTrait = KeyTrait
        >
        class Indexer
        {
            std::unordered_map<typename KeyTrait<T>::key_type, size_t> m_map;
            KeyTrait<T> m_key_trait;
        public:
            void set(const T& t, size_t index)
            {
                m_map[m_key_trait.key(t)] = index;
            }
            size_t get(const T& t) const // throw(std::out_of_range)
            {
                return m_map.at(m_key_trait.key(t));
            }
            void erase(const T& t)
            {
                m_map.erase(m_key_trait.key(t));
            }
            bool contains(const T& t) const
            {
                return m_map.find(m_key_trait.key(t)) != m_map.end();
            }
            size_t size() const { return m_map.size(); }

            void swap(Indexer<T, C, KeyTrait>& other)
            {
                m_map.swap(other.m_map);
                m_key_trait.swap(other.m_key_trait);
            }
        };

        template <
            typename I,
            typename C,
            template <typename, typename, template <typename> class>
            class Indexer
        >
        void sink(
            I begin, I end, I outer,
            C comp,
            Indexer<typename std::iterator_traits<I>::value_type, C, KeyTrait> & indexer
        ) {
            auto len = end - begin;
            while (true) {
                decltype(len) d = outer - begin;
                auto candidate = outer;
                decltype(len) c = (d + 1) << 1;
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
            template <typename, typename, template <typename> class>
            class Indexer
        >
        void rise(
            I begin, I /*end*/, I outer,
            C comp,
            Indexer<typename std::iterator_traits<I>::value_type, C, KeyTrait> & indexer
        ) {
            while (true) {
                auto d = outer - begin;
                I parent;
                if (d > 0 && comp(*(parent = begin + ((d - 1) >> 1)), *outer)) {
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
            template <typename, typename, template <typename> class>
            class Indexer
        >
        int64_t make_heap(
            I begin, I end,
            C comp,
            Indexer<typename std::iterator_traits<I>::value_type, C, KeyTrait> & indexer
        ) {
            assert(begin <= end);
            int64_t len = static_cast<int64_t>(end - begin);
            if (len > 1) {
                for (auto i = len >> 1; i >= 0; --i) {
                    sink<I, C, Indexer>(begin, end, begin + i, comp, indexer);
                }
            }
            return len;
        }
    }

    template <
        typename T,
        typename C = std::greater_equal<T>,
        template <typename>
        class KeyTrait = details::KeyTrait
    >
    class BinaryHeap
    {
        std::vector<T> m_heap;
        details::Indexer<T, C, KeyTrait> m_indexer;

        template <typename I>
        BinaryHeap(I begin, I end)/* : m_heap(begin, end)*/
        {
        #if 0
            size_t i = 0;
            for (auto j = begin; j != end; ++j) {
                m_indexer.set(*j, i++);
            }
            details::make_heap<typename std::vector<T>::iterator, C, details::Indexer>(
                m_heap.begin(), m_heap.end(), C(), m_indexer
            );
            if (m_indexer.size() != m_heap.size()) {
                throw std::invalid_argument("Every element must be unique");
            }
        #else
            for (auto i = begin; i != end; ++i) {
                insert(*i);
            }
        #endif
        }
    public:
        BinaryHeap(size_t n=0)
        {
            if (n > 0) {
                m_heap.reserve(n);
            }
        }
        BinaryHeap(BinaryHeap<T, C, KeyTrait> const&) = default;
        BinaryHeap(BinaryHeap<T, C, KeyTrait>&&) = default;
        BinaryHeap<T, C, KeyTrait>& operator=(BinaryHeap<T, C, KeyTrait> const&) = default;
        BinaryHeap<T, C, KeyTrait>& operator=(BinaryHeap<T, C, KeyTrait>&&) = default;

        template <typename I>
        static BinaryHeap<T, C, KeyTrait> make_heap(I begin, I end)
        {
            return BinaryHeap<T, C, KeyTrait>(begin, end);
        }

        void insert(const T& t)
        {
            if (!m_indexer.contains(t)) {
                size_t n = m_heap.size();
                m_heap.push_back(t);
                m_indexer.set(t, n);
                details::rise<typename std::vector<T>::iterator, C, details::Indexer>(
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
                    details::sink<typename std::vector<T>::iterator, C, details::Indexer>(
                        begin, end, begin, C(), m_indexer
                    );
                }
                m_heap.pop_back();
            }
        }

        BinaryHeap<T, C, KeyTrait> & operator+=(BinaryHeap<T, C, KeyTrait> const& other)
        {
        #if 0
            size_t n = m_heap.size();
            m_heap.insert(m_heap.end(), other.m_heap.begin(), other.m_heap.end());
            for (auto i = other.m_heap.begin(), ie = other.m_heap.end(); i != ie; ++i) {
                m_indexer.set(*i, n++);
            }
            details::make_heap<typename std::vector<T>::iterator, C, details::Indexer>(
                m_heap.begin(), m_heap.end(), C(), m_indexer
            );
            if (m_indexer.size() != n) {
                throw std::invalid_argument("Every element must be unique");
            }
        #else
            for (auto i = other.m_heap.begin(), ie = other.m_heap.end(); i != ie; ++i) {
                insert(*i);
            }
        #endif
            return *this;
        }

        void replace(const T& _old, const T& _new) // throw(std::out_of_range)
        {
            if (_old != _new) {
                size_t index = m_indexer.get(_old);
                m_heap[index] = _new;
                m_indexer.erase(_old);
                m_indexer.set(_new, index);
                if (C()(_old, _new)) {
                    details::rise<typename std::vector<T>::iterator, C, details::Indexer>(
                        m_heap.begin(), m_heap.end(), m_heap.begin() + index, C(), m_indexer
                    );
                } else {
                    details::sink<typename std::vector<T>::iterator, C, details::Indexer>(
                        m_heap.begin(), m_heap.end(), m_heap.begin() + index, C(), m_indexer
                    );
                }
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
                details::sink<typename std::vector<T>::iterator, C, details::Indexer>(
                    begin, end, begin + index, C(), m_indexer
                );
            }
            m_heap.pop_back();
        }

        bool contains(const T& t) const { return m_indexer.contains(t); }
        size_t size() const { return m_heap.size(); }
        bool empty() const { return m_heap.empty(); }
        void swap(BinaryHeap<T, C, KeyTrait>& other)
        {
            m_heap.swap(other.m_heap);
            m_indexer.swap(other.m_indexer);
        }
    };
}

#endif //BINARY_HEAP_GYM_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
