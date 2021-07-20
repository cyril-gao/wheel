#ifndef STRING_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
#define STRING_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00

#include <string.h>
#include <iterator>
#include "counting_sort.h"
#include "insertion_sort.h"

namespace
{
    namespace details
    {
        template <typename RandomIt>
        struct V4_1Partitioner
        {
            std::pair<RandomIt, RandomIt> operator()(RandomIt begin, RandomIt end, size_t d)
            {
                auto sentinel = (*begin)[d];

                RandomIt smaller = begin;
                RandomIt bigger = end - 1;
                for (RandomIt i = begin + 1; i <= bigger;) {
                    if ((*i)[d] < sentinel) {
                        std::iter_swap(smaller, i);
                        ++smaller;
                        ++i;
                    } else if (sentinel < (*i)[d]) {
                        std::iter_swap(i, bigger);
                        --bigger;
                    } else {
                        ++i;
                    }
                }
                return std::make_pair(smaller, bigger + 1);
            }
        };

        template <typename RandomIt>
        struct V4_2Partitioner
        {
            std::pair<RandomIt, RandomIt> operator()(RandomIt begin, RandomIt end, size_t d)
            {
                assert(std::distance(begin, end) > 1);
                auto sentinel = (*begin)[d];

                RandomIt equal = begin, i = begin + 1, bigger = end, j = bigger - 1;
                while (i <= j) {
                    while ((*i)[d] <= sentinel) {
                        if ((*i)[d] < sentinel) {
                            std::iter_swap(equal++, i);
                        }
                        ++i;
                        if (i > j) {
                            break;
                        }
                    }

                    while ((*j)[d] >= sentinel) {
                        if ((*j)[d] > sentinel) {
                            std::iter_swap(--bigger, j);
                        }
                        --j;
                        if (j < i) {
                            break;
                        }
                    }
                    if (i < j) {
                        assert((*i)[d] > sentinel && (*j)[d] < sentinel);
                        std::iter_swap(i, j);
                        std::iter_swap(equal++, i++);
                        std::iter_swap(--bigger, j--);
                    }
                }
                return std::make_pair(equal, bigger);
            }
        };

        template <template <typename> class Partitioner, typename RandomIt>
        void str_sort(RandomIt begin, RandomIt end, size_t d)
        {
            auto sorting = [](RandomIt begin, RandomIt end, size_t d) {
                auto m = Partitioner<RandomIt>()(begin, end, d);
                str_sort<Partitioner, RandomIt>(begin, m.first, d);
                if ((*m.first)[d] != 0 && (m.second - m.first) > 1) {
                    str_sort<Partitioner, RandomIt>(m.first, m.second, d + 1);
                }
                str_sort<Partitioner, RandomIt>(m.second, end, d);
            };
            insertion_sort<decltype(sorting), RandomIt, size_t>(sorting, begin, end, d);
        }

        template <typename RandomIt>
        class CStrIterator
        {
            RandomIt m_i;
            size_t m_offset;
        public:
            typedef typename std::iterator_traits<RandomIt>::iterator_category iterator_category;
            typedef typename std::iterator_traits<RandomIt>::difference_type difference_type;
            typedef typename std::iterator_traits<RandomIt>::pointer pointer;
            typedef std::remove_cv_t<std::remove_reference_t<decltype((*m_i)[0])>> value_type;
            // typedef unsigned char value_type;
            typedef const value_type& reference;

            explicit CStrIterator(RandomIt i, size_t offset) : m_i(i), m_offset(offset)
            {
            }

            RandomIt inner() const { return m_i; }

            reference operator*() const
            {
                auto cptr = *m_i;
                return cptr[m_offset];
            }

            CStrIterator& operator++()
            {
                ++m_i;
                return (*this);
            }

            CStrIterator operator++(int)
            {
                CStrIterator tmp = m_i;
                ++m_i;
                return tmp;
            }

            CStrIterator& operator--()
            {
                --m_i;
                return (*this);
            }

            CStrIterator operator--(int)
            {
                CStrIterator tmp = m_i;
                --m_i;
                return tmp;
            }

            CStrIterator& operator+=(difference_type diff)
            {
                m_i += diff;
                return (*this);
            }

            CStrIterator operator+(difference_type diff) const
            {
                return CStrIterator(m_i + diff, m_offset);
            }

            CStrIterator& operator-=(difference_type diff)
            {
                m_i -= diff;
                return (*this);
            }

            CStrIterator operator-(difference_type diff) const
            {
                return CStrIterator(m_i - diff, m_offset);
            }

            difference_type operator-(const CStrIterator& r) const
            {
                return m_i - r.m_i;
            }

            reference operator[](difference_type diff) const
            {
                auto cptr = &m_i[diff];
                return cptr[m_offset];
            }

            friend bool operator>(CStrIterator l, CStrIterator r)
            {
                return l.m_i > r.m_i;
            }

            friend bool operator<(CStrIterator l, CStrIterator r)
            {
                return l.m_i < r.m_i;
            }

            friend bool operator==(CStrIterator l, CStrIterator r)
            {
                return l.m_i == r.m_i;
            }

            friend bool operator!=(CStrIterator l, CStrIterator r)
            {
                return l.m_i != r.m_i;
            }
        };

        template <typename RandomIt>
        void iter_swap(CStrIterator<RandomIt> a, CStrIterator<RandomIt> b)
        {
            if (a != b) {
                std::iter_swap(a.inner(), b.inner());
            }
        }

        template <typename RandomIt>
        inline void unsigned_char_sort(RandomIt begin, RandomIt end, size_t d, std::vector<uint32_t>& counting_buffer)
        {
            static_assert(
                std::is_same<typename std::iterator_traits<RandomIt>::value_type, unsigned char>::value &&
                sizeof(typename std::iterator_traits<RandomIt>::value_type) == 1,
                "must be an one-byte positive integer"
            );
            std::vector<typename std::iterator_traits<RandomIt>::value_type> temporary_array(end - begin);
            typename std::vector<typename std::iterator_traits<RandomIt>::value_type>::iterator oi = temporary_array.begin();
            counting_sort(
                CStrIterator(begin, d), CStrIterator(end, d),
                UCHAR_MAX,
                begin, end,
                oi,
                counting_buffer
            );
            std::copy(temporary_array.begin(), temporary_array.end(), begin);
        }

        template <typename RandomIt>
        void c_str_msd_sort(RandomIt begin, RandomIt end, size_t d, unsigned_char_type)
        {
            auto sorting = [d](RandomIt begin, RandomIt end) {
                std::vector<uint32_t> counting_buffer(static_cast<size_t>(UCHAR_MAX) + 1, 0);
                unsigned_char_sort<RandomIt>(begin, end, d, counting_buffer);
                size_t last = counting_buffer.size() - 1;
                for (size_t i = 1; i < last;) { // skip 0
                    size_t j = i + 1;
                    size_t b = counting_buffer[i];
                    size_t e = counting_buffer[j];
                    if (b < e) {
                        c_str_msd_sort(begin + b, begin + e, d + 1, unsigned_char_type());
                    }
                    i = j;
                }
                begin += counting_buffer[last];
                if (begin < end) {
                    c_str_msd_sort(begin, end, d + 1, unsigned_char_type());
                }
            };
            insertion_sort<decltype(sorting), RandomIt>(sorting, begin, end);
        }

        template <typename RandomIt>
        inline RandomIt char_sort(RandomIt begin, RandomIt end, size_t d, std::vector<uint32_t>& counting_buffer)
        {
            static_assert(
                (
                    std::is_same_v<std::remove_cv_t<std::remove_reference_t<decltype((*begin)[0])>>, char> ||
                    std::is_same_v<std::remove_cv_t<std::remove_reference_t<decltype((*begin)[0])>>, int8_t>
                ) &&
                sizeof(std::remove_cv_t<std::remove_reference_t<decltype((*begin)[0])>>) == 1,
                "must be an one-byte integer"
            );
            std::vector<typename std::iterator_traits<RandomIt>::value_type> temporary_array(static_cast<size_t>(end - begin));
            auto separator = partition(CStrIterator<RandomIt>(begin, d), CStrIterator<RandomIt>(end, d));
            counting_sort(
                CStrIterator<RandomIt>(begin, d), separator,
                UCHAR_MAX,
                begin, separator.inner(),
                temporary_array.begin(),
                counting_buffer
            );
            std::copy(temporary_array.begin(), temporary_array.begin() + (separator.inner() - begin), begin);
            counting_sort(
                separator, CStrIterator<RandomIt>(end, d),
                CHAR_MAX,
                separator.inner(), end,
                temporary_array.begin(),
                counting_buffer
            );
            std::copy(temporary_array.begin(), temporary_array.begin() + (end - separator.inner()), separator.inner());
            return separator.inner();
        }

        template <typename RandomIt>
        void c_str_msd_sort(RandomIt begin, RandomIt end, size_t d, char_type)
        {
            auto comp = [](auto a, auto b) {
                return strcmp(a, b) <= 0;
            };
            auto sorting = [d](RandomIt begin, RandomIt end) {
                std::vector<uint32_t> counting_buffer(static_cast<size_t>(UCHAR_MAX) + 1, 0);
                auto separator = char_sort<RandomIt>(begin, end, d, counting_buffer);
                for (size_t i = 1; i < SCHAR_MAX;) {
                    size_t j = i + 1;
                    auto b = counting_buffer[i];
                    auto e = counting_buffer[j];
                    if (b < e) {
                        c_str_msd_sort(separator + b, separator + e, d + 1, char_type());
                    }
                    i = j;
                }
                {
                    auto b = separator + counting_buffer[SCHAR_MAX];
                    if (b < end) {
                        c_str_msd_sort(b, end, d + 1, char_type());
                    }
                }
                for (size_t i = SCHAR_MAX; i < UCHAR_MAX;) {
                    size_t j = i + 1;
                    auto b = counting_buffer[i];
                    auto e = counting_buffer[j];
                    if (b < e) {
                        c_str_msd_sort(begin + b, begin + e, d + 1, char_type());
                    }
                    i = j;
                }
                {
                    auto b = begin + counting_buffer[UCHAR_MAX];
                    if (b < separator) {
                        c_str_msd_sort(b, separator, d + 1, char_type());
                    }
                }
            };
            insertion_sort<decltype(sorting), decltype(comp), RandomIt>(sorting, comp, begin, end);
        }

        template <typename RandomIt>
        void c_str_msd_sort(RandomIt begin, RandomIt end)
        {
            c_str_msd_sort<RandomIt>(
                begin, end, 0,
                typename details::integer<std::remove_cv_t<std::remove_reference_t<decltype((*begin)[0])>>>::value_type()
            );
        }
    }
}

template <typename RandomIt>
void msd_sort(RandomIt begin, RandomIt end)
{
    if constexpr (std::is_pointer_v<typename std::iterator_traits<RandomIt>::value_type>) {
        details::c_str_msd_sort(begin, end);
    } else {
        size_t distance = static_cast<size_t>(std::distance(begin, end));
        std::vector<typename std::iterator_traits<RandomIt>::value_type> moved;
        moved.reserve(distance);
        std::for_each(begin, end, [&moved](auto& s) { moved.emplace_back(std::move(s)); });
        std::vector<decltype(moved[0].c_str())> buffer;
        buffer.reserve(distance);
        std::for_each(moved.begin(), moved.end(), [&buffer](const auto& s) { buffer.push_back(s.c_str()); });
        details::c_str_msd_sort(buffer.begin(), buffer.end());
        auto i = buffer.begin();
        std::for_each(begin, end, [&i](auto& s) { s = *i++; });
    }
}

template <template <typename> class Partitioner, typename RandomIt>
void str_sort(RandomIt begin, RandomIt end)
{
    details::str_sort<Partitioner, RandomIt>(begin, end, 0);
}

#endif //STRING_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
