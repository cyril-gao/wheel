#ifndef COUNTING_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
#define COUNTING_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00

#include <assert.h>
#include <stdint.h>

#include <limits.h>
#include <type_traits>
#include <algorithm>


namespace
{
    template <typename DecoratedInputIterator, typename OriginalInputIterator, typename OutputIterator>
    void counting_sort(
        DecoratedInputIterator db, DecoratedInputIterator de,
        size_t biggest_item,
        OriginalInputIterator ob, OriginalInputIterator oe,
        OutputIterator output,
        std::vector<uint32_t> & counting_buffer
    ) {
        assert(biggest_item < SIZE_MAX && (de - db == oe - ob));
        assert(counting_buffer.size() >= (biggest_item + 1));
        if (de > db) {
            for (DecoratedInputIterator i = db; i != de; ++i) {
                ++counting_buffer[static_cast<size_t>(*i)];
            }
            for (size_t i = 1, last = biggest_item; i <= last; ++i) {
                counting_buffer[i] += counting_buffer[i - 1];
            }

            for (auto i = de - db; i != 0;) {
                --i;
                size_t v = static_cast<size_t>(*(db + i));
                *(output + counting_buffer[v] - 1) = *(ob + i);
                --counting_buffer[v];
            }
        }
    }

    template <typename RandomIt>
    class OffsetIterator
    {
        RandomIt m_i;
        size_t m_offset;
    public:
        typedef typename std::iterator_traits<RandomIt>::iterator_category iterator_category;
        typedef typename std::iterator_traits<RandomIt>::difference_type difference_type;
        typedef typename std::iterator_traits<RandomIt>::pointer pointer;
        typedef unsigned char value_type;
        typedef value_type& reference;

        explicit OffsetIterator(RandomIt i, size_t offset) : m_i(i), m_offset(offset)
        {
        #if 0
            assert(offset < sizeof(typename std::iterator_traits<RandomIt>::value_type));
            unsigned int s = 0x01000000;
            unsigned char* pb = reinterpret_cast<unsigned char*>(&s);
            if (pb[0] == 0x01) {
                m_offset = sizeof(typename std::iterator_traits<RandomIt>::value_type) - offset - 1;
            }
        #endif
        }

        reference operator*() const
        {
            void* pv = &(*m_i);
            value_type* pb = reinterpret_cast<value_type*>(pv);
            return pb[m_offset];
        }

        OffsetIterator& operator++()
        {
            ++m_i;
            return (*this);
        }

        OffsetIterator operator++(int)
        {
            OffsetIterator tmp = m_i;
            ++m_i;
            return tmp;
        }

        OffsetIterator& operator--()
        {
            --m_i;
            return (*this);
        }

        OffsetIterator operator--(int)
        {
            OffsetIterator tmp = m_i;
            --m_i;
            return tmp;
        }

        OffsetIterator& operator+=(difference_type diff)
        {
            m_i += diff;
            return (*this);
        }

        OffsetIterator operator+(difference_type diff) const
        {
            return OffsetIterator(m_i + diff, m_offset);
        }

        OffsetIterator& operator-=(difference_type diff)
        {
            m_i -= diff;
            return (*this);
        }

        OffsetIterator operator-(difference_type diff) const
        {
            return OffsetIterator(m_i - diff, m_offset);
        }

        difference_type operator-(const OffsetIterator& r) const
        {
            return m_i - r.m_i;
        }

        reference operator[](difference_type diff) const
        {
            void* pv = &m_i[diff];
            value_type* pb = reinterpret_cast<value_type*>(pv);
            return pb[m_offset];
        }

        friend bool operator>(OffsetIterator l, OffsetIterator r)
        {
            return l.m_i > r.m_i;
        }

        friend bool operator<(OffsetIterator l, OffsetIterator r)
        {
            return l.m_i < r.m_i;
        }

        friend bool operator==(OffsetIterator l, OffsetIterator r)
        {
            return l.m_i == r.m_i;
        }

        friend bool operator!=(OffsetIterator l, OffsetIterator r)
        {
            return l.m_i != r.m_i;
        }
    };

    namespace details
    {
        template <typename RandomIt>
        inline void positive_integer_sort(RandomIt begin, RandomIt end)
        {
            if (end > begin) {
                std::vector<typename std::iterator_traits<RandomIt>::value_type> temporary_array(static_cast<size_t>(end - begin));
                typename std::vector<typename std::iterator_traits<RandomIt>::value_type>::iterator oi = temporary_array.begin(), oe = temporary_array.end();
                constexpr size_t bytes = sizeof(typename std::iterator_traits<RandomIt>::value_type);
                assert(bytes % 2 == 0);
                std::vector<uint32_t> counting_buffer(static_cast<size_t>(UCHAR_MAX) + 1, 0);
            #if defined(LITTLE_ENDIAN_MACHINE)
                for (size_t i = 0; i < bytes; i += 2) {
                    counting_sort(OffsetIterator<RandomIt>(begin, i), OffsetIterator<RandomIt>(end, i), UCHAR_MAX, begin, end, oi, counting_buffer);
                    std::fill(std::begin(counting_buffer), std::end(counting_buffer), 0);
                    counting_sort(
                        OffsetIterator<typename std::vector<typename std::iterator_traits<RandomIt>::value_type>::iterator>(oi, i + 1),
                        OffsetIterator<typename std::vector<typename std::iterator_traits<RandomIt>::value_type>::iterator>(oe, i + 1),
                        UCHAR_MAX,
                        oi, oe,
                        begin,
                        counting_buffer
                    );
                    std::fill(std::begin(counting_buffer), std::end(counting_buffer), 0);
                }
            #else
                for (size_t i = bytes; i != 0;) {
                    --i;
                    counting_sort(
                        OffsetIterator<typename std::vector<typename std::iterator_traits<RandomIt>::value_type>::iterator>(oi, i),
                        OffsetIterator<typename std::vector<typename std::iterator_traits<RandomIt>::value_type>::iterator>(oe, i),
                        UCHAR_MAX,
                        oi, oe,
                        begin,
                        counting_buffer
                    );
                    std::fill(std::begin(counting_buffer), std::end(counting_buffer), 0);
                    --i;
                    counting_sort(
                        OffsetIterator<typename std::vector<typename std::iterator_traits<RandomIt>::value_type>::iterator>(oi, i),
                        OffsetIterator<typename std::vector<typename std::iterator_traits<RandomIt>::value_type>::iterator>(oe, i),
                        UCHAR_MAX,
                        oi, oe,
                        begin,
                        counting_buffer
                    );
                    std::fill(std::begin(counting_buffer), std::end(counting_buffer), 0);
                }
            #endif
            }
        }

        typedef std::integral_constant<int, 0> unsigned_char_type;
        typedef std::integral_constant<int, 1> char_type;
        typedef std::integral_constant<int, 2> unsigned_int_type;
        typedef std::integral_constant<int, 3> int_type;

        template <typename I>
        struct integer;

        template <>
        struct integer<uint8_t>
        {
            typedef unsigned_char_type value_type;
        };

        template <>
        struct integer<int8_t>
        {
            typedef char_type value_type;
        };

        template <>
        struct integer<char>
        {
            typedef char_type value_type;
        };

        template <>
        struct integer<unsigned short>
        {
            typedef unsigned_int_type value_type;
        };

        template <>
        struct integer<short>
        {
            typedef int_type value_type;
        };

        template <>
        struct integer<unsigned int>
        {
            typedef unsigned_int_type value_type;
        };

        template <>
        struct integer<char16_t>
        {
            typedef unsigned_int_type value_type;
        };

        template <>
        struct integer<char32_t>
        {
            typedef unsigned_int_type value_type;
        };

        template <>
        struct integer<wchar_t>
        {
            typedef unsigned_int_type value_type;
        };

        template <>
        struct integer<int>
        {
            typedef int_type value_type;
        };

        template <>
        struct integer<uint64_t>
        {
            typedef unsigned_int_type value_type;
        };

        template <>
        struct integer<int64_t>
        {
            typedef int_type value_type;
        };

        template <typename RandomIt>
        inline RandomIt partition(RandomIt begin, RandomIt end)
        {
            using std::iter_swap;
            RandomIt separator = end;
            if (end > begin) {
                auto distance = end - begin;
                auto ge = begin + distance;
                for (auto i = ge; i != begin;) {
                    auto j = i - 1;
                    if (*j >= 0) {
                        iter_swap(--ge, j);
                    }
                    i = j;
                }
                separator = ge;
            }
            return separator;
        }

        template <typename RandomIt>
        inline void integer_sort(RandomIt begin, RandomIt end, unsigned_char_type)
        {
            static_assert(
                std::is_same<typename std::iterator_traits<RandomIt>::value_type, unsigned char>::value &&
                sizeof(typename std::iterator_traits<RandomIt>::value_type) == 1,
                "must be an one-byte positive integer"
            );
            std::vector<typename std::iterator_traits<RandomIt>::value_type> temporary_array(static_cast<size_t>(end - begin));
            typename std::vector<typename std::iterator_traits<RandomIt>::value_type>::iterator oi = temporary_array.begin();
            std::vector<uint32_t> counting_buffer(static_cast<size_t>(UCHAR_MAX) + 1, 0);
            counting_sort(begin, end, UCHAR_MAX, begin, end, oi, counting_buffer);
            std::copy(temporary_array.begin(), temporary_array.end(), begin);
        }

        template <typename RandomIt>
        inline void integer_sort(RandomIt begin, RandomIt end, char_type)
        {
            static_assert(
                (
                    std::is_same<typename std::iterator_traits<RandomIt>::value_type, char>::value ||
                    std::is_same<typename std::iterator_traits<RandomIt>::value_type, int8_t>::value
                ) &&
                sizeof(typename std::iterator_traits<RandomIt>::value_type) == 1,
                "must be an one-byte integer"
            );
            std::vector<typename std::iterator_traits<RandomIt>::value_type> temporary_array(static_cast<size_t>(end - begin));
            auto separator = partition(begin, end);
            std::vector<uint32_t> counting_buffer(static_cast<size_t>(UCHAR_MAX) + 1, 0);
            counting_sort(
                OffsetIterator<RandomIt>(begin, 0), OffsetIterator<RandomIt>(separator, 0),
                UCHAR_MAX,
                begin, separator,
                temporary_array.begin(),
                counting_buffer
            );
            std::copy(temporary_array.begin(), temporary_array.begin() + (separator - begin), begin);
            counting_sort(separator, end, CHAR_MAX, separator, end, temporary_array.begin(), counting_buffer);
            std::copy(temporary_array.begin(), temporary_array.begin() + (end - separator), separator);
        }

        template <typename RandomIt>
        inline void integer_sort(RandomIt begin, RandomIt end, unsigned_int_type)
        {
            static_assert(
                std::is_integral<typename std::iterator_traits<RandomIt>::value_type>::value &&
                std::is_unsigned<typename std::iterator_traits<RandomIt>::value_type>::value,
                "must be a positive integer"
            );
            positive_integer_sort(begin, end);
        }

        template <typename RandomIt>
        inline void integer_sort(RandomIt begin, RandomIt end, int_type)
        {
            static_assert(
                std::is_integral<typename std::iterator_traits<RandomIt>::value_type>::value &&
                !std::is_unsigned<typename std::iterator_traits<RandomIt>::value_type>::value,
                "must be an integer"
            );
            auto separator = partition(begin, end);
            positive_integer_sort(separator, end);
            positive_integer_sort(begin, separator);
        }
    }
}

template <typename RandomIt>
void integer_sort(RandomIt begin, RandomIt end)
{
    details::integer_sort(
        begin, end,
        typename details::integer<typename std::iterator_traits<RandomIt>::value_type>::value_type()
    );
}

#endif //COUNTING_SORT_H_F02ABCD3_2DDF_4127_815F_84FDF6A80E00
