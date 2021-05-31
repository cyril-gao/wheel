#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#include <limits>
#include <numeric>
#include <algorithm>
#include <initializer_list>
#include <type_traits>
#include <vector>
#include <utility>


#include "check.h"

namespace details
{
    std::pair<size_t, size_t> get_aligned_size(size_t n)
    {
        size_t retval = 1;
        size_t bits = 0;
        while (retval < n) {
            retval <<= 1;
            ++bits;
        }
        return std::make_pair(retval, bits);
    }
}

template <typename T>
class SumSegmentTree
{
    const size_t m_length;
    const std::pair<size_t, size_t> m_aligned_length_and_bits;
    std::vector<T> m_array;

    size_t get_index(size_t position, size_t bits) const
    {
        size_t bits_diff = m_aligned_length_and_bits.second - bits;
        return (position >> bits) + (1 << bits_diff) - 1;
    }

    T get_sum(size_t begin, size_t end, size_t diff, size_t aligned_diff, size_t bits) const
    {
        assert(diff <= aligned_diff);
        size_t mask = -1;
        mask <<= bits;
        size_t aligned_begin = begin & mask;
        assert(aligned_begin + aligned_diff >= end);
        if (begin != aligned_begin || diff != aligned_diff) {
            aligned_diff >>= 1;
            size_t aligned_mid = aligned_begin + aligned_diff;

            --bits;
            if (end <= aligned_mid || begin >= aligned_mid) {
                return get_sum(begin, end, end - begin, aligned_diff, bits);
            } else {
                return (
                    get_sum(begin, aligned_mid, aligned_mid - begin, aligned_diff, bits) +
                    get_sum(aligned_mid, end, end - aligned_mid, aligned_diff, bits)
                );
            }
        } else {
            size_t i = get_index(aligned_begin, bits);
            return m_array[i];
        }
    }

    T get_sum(size_t begin, size_t end) const
    {
        assert(begin < end && end <= m_length);
        size_t diff = end - begin;
        const auto [aligned_diff, bits] = details::get_aligned_size(diff);
        size_t mask = -1;
        mask <<= bits;
        size_t aligned_begin = begin & mask;
        size_t aligned_end = aligned_begin + aligned_diff;
        if (end <= aligned_end) {
            return get_sum(begin, end, diff, aligned_diff, bits);
        } else {
            return (get_sum(begin, aligned_end) + get_sum(aligned_end, end));
        }
    }
public:
    explicit SumSegmentTree(size_t max_size) :
        m_length(max_size),
        m_aligned_length_and_bits(details::get_aligned_size(m_length)),
        m_array((m_aligned_length_and_bits.first << 1) - 1)
    {
    }

    template <typename I>
    explicit SumSegmentTree(I begin, I end) : SumSegmentTree(end - begin)
    {
        std::copy(begin, end, &m_array[(1 << m_aligned_length_and_bits.second) - 1]);
        for (
            int bits = static_cast<int>(m_aligned_length_and_bits.second) - 1;
            bits >= 0;
            --bits
        ) {
            for (size_t count = 1 << bits, index = count - 1, i = 0; i < count; ++i, ++index) {
                size_t right = (index + 1) << 1;
                size_t left = right - 1;
                m_array[index] = m_array[left] + m_array[right];
            }
        }
    }

    template <typename V>
    explicit SumSegmentTree(std::initializer_list<V> elements) :
        SumSegmentTree(elements.begin(), elements.end())
    {
    }

    T sum(size_t begin, size_t end = -1) const
    {
        if (end > m_length) {
            end = m_length;
        }
        if (begin < end) {
            return get_sum(begin, end);
        } else {
            return T{};
        }
    }

    void replace(size_t index, T new_value)
    {
        assert(index < m_length);
        index += ((1 << m_aligned_length_and_bits.second) - 1);
        if constexpr (std::is_signed_v<T>) {
            T diff = new_value - m_array[index];
            if (diff != 0) {
                while (true) {
                    m_array[index] += diff;
                    if (index != 0) {
                        if ((index & 1) == 0) {
                            --index;
                        }
                        index >>= 1;
                    } else {
                        break;
                    }
                }
            }
        } else {
            if (m_array[index] != new_value) {
                T diff;
                int flag;
                if (new_value > m_array[index]) {
                    diff = new_value - m_array[index];
                    flag = 1;
                } else {
                    diff = m_array[index] - new_value;
                    flag = -1;
                }
                auto modifier = [=](T& value) {
                    if (flag > 0) {
                        value += diff;
                    } else {
                        value -= diff;
                    }
                };
                while (true) {
                    modifier(m_array[index]);
                    if (index != 0) {
                        if ((index & 1) == 0) {
                            --index;
                        }
                        index >>= 1;
                    } else {
                        break;
                    }
                }
            }
        }
    }

    size_t size() const { return m_length; }
};

void sum_segment_tree_test()
{
    {
        int nums[] = {9, 1, 7, 3, 2, 0, -10, 4, 5, 6, -9};
        const size_t size = std::size(nums);
        auto begin = std::begin(nums);
        SumSegmentTree<int> sst(begin, std::end(nums));
        for (size_t span = 1; span <= size; ++span) {
            for (size_t i = 0, j = i + span; j <= size; ++i, ++j) {
                auto expectation = std::accumulate(begin + i, begin + j, 0);
                examine(sst.sum(i, j) == expectation, "SumSegmentTree is failed for the input: [%zu, %zu) at the line: %d\n", i, j, __LINE__);
            }
        }
        for (int retry = 0; retry < 100; ++retry) {
            size_t index = static_cast<size_t>(rand()) % size;
            int new_value = rand() % 100;
            nums[index] = new_value;
            sst.replace(index, new_value);
            for (size_t span = 1; span <= size; ++span) {
                for (size_t i = 0, j = i + span; j <= size; ++i, ++j) {
                    auto expectation = std::accumulate(begin + i, begin + j, 0);
                    examine(sst.sum(i, j) == expectation, "SumSegmentTree is failed for the input: [%zu, %zu) at the line: %d\n", i, j, __LINE__);
                }
            }
        }
    }

    {
        uint32_t nums[] = {9, 1, 7, 3, 11, 12, 0, 2, 8, 13, 14, 10, 4, 5, 6, 19, 21};
        const size_t size = std::size(nums);
        auto begin = std::begin(nums);
        SumSegmentTree<uint32_t> sst(begin, std::end(nums));
        for (size_t span = 1; span <= size; ++span) {
            for (size_t i = 0, j = i + span; j <= size; ++i, ++j) {
                auto expectation = std::accumulate(begin + i, begin + j, 0u);
                examine(sst.sum(i, j) == expectation, "SumSegmentTree is failed for the input: [%zu, %zu) at the line: %d\n", i, j, __LINE__);
            }
        }
        for (int retry = 0; retry < 100; ++retry) {
            size_t index = static_cast<size_t>(rand()) % size;
            uint32_t new_value = rand() % 100;
            nums[index] = new_value;
            sst.replace(index, new_value);
            for (size_t span = 1; span <= size; ++span) {
                for (size_t i = 0, j = i + span; j <= size; ++i, ++j) {
                    auto expectation = std::accumulate(begin + i, begin + j, 0u);
                    examine(sst.sum(i, j) == expectation, "SumSegmentTree is failed for the input: [%zu, %zu) at the line: %d\n", i, j, __LINE__);
                }
            }
        }
    }

    {
        size_t size = rand();
        size %= (1024 * 8);
        std::vector<uint32_t> nums(size);
        auto begin = std::begin(nums);
        SumSegmentTree<uint32_t> sst(size);
        for (size_t span = 1; span <= size; ++span) {
            for (size_t i = 0, j = i + span; j <= size; ++i, ++j) {
                auto expectation = std::accumulate(begin + i, begin + j, 0u);
                examine(sst.sum(i, j) == expectation, "SumSegmentTree is failed for the input: [%zu, %zu) at the line: %d\n", i, j, __LINE__);
            }
        }
        for (int retry = 0; retry < 100; ++retry) {
            size_t index = static_cast<size_t>(rand()) % size;
            uint32_t new_value = rand() % 100;
            nums[index] = new_value;
            sst.replace(index, new_value);
            for (size_t span = 1; span <= size; ++span) {
                for (size_t i = 0, j = i + span; j <= size; ++i, ++j) {
                    auto expectation = std::accumulate(begin + i, begin + j, 0u);
                    examine(sst.sum(i, j) == expectation, "SumSegmentTree is failed for the input: [%zu, %zu) at the line: %d\n", i, j, __LINE__);
                }
            }
        }
    }
}

template <typename T>
class MinimumSegmentTree
{
    const size_t m_length;
    const std::pair<size_t, size_t> m_aligned_length_and_bits;
    std::vector<T> m_array;

    size_t get_index(size_t position, size_t bits) const
    {
        size_t bits_diff = m_aligned_length_and_bits.second - bits;
        return (position >> bits) + (1 << bits_diff) - 1;
    }

    T get_minimum(size_t begin, size_t end, size_t diff, size_t aligned_diff, size_t bits) const
    {
        assert(diff <= aligned_diff);
        size_t mask = -1;
        mask <<= bits;
        size_t aligned_begin = begin & mask;
        assert(aligned_begin + aligned_diff >= end);
        if (begin != aligned_begin || diff != aligned_diff) {
            aligned_diff >>= 1;
            size_t aligned_mid = aligned_begin + aligned_diff;

            --bits;
            if (end <= aligned_mid || begin >= aligned_mid) {
                return get_minimum(begin, end, end - begin, aligned_diff, bits);
            } else {
                return std::min(
                    get_minimum(begin, aligned_mid, aligned_mid - begin, aligned_diff, bits),
                    get_minimum(aligned_mid, end, end - aligned_mid, aligned_diff, bits)
                );
            }
        } else {
            size_t i = get_index(aligned_begin, bits);
            return m_array[i];
        }
    }

    T get_minimum(size_t begin, size_t end) const
    {
        assert(begin < end && end <= m_length);
        size_t diff = end - begin;
        const auto [aligned_diff, bits] = details::get_aligned_size(diff);
        size_t mask = -1;
        mask <<= bits;
        size_t aligned_begin = begin & mask;
        size_t aligned_end = aligned_begin + aligned_diff;
        if (end <= aligned_end) {
            return get_minimum(begin, end, diff, aligned_diff, bits);
        } else {
            return std::min(get_minimum(begin, aligned_end), get_minimum(aligned_end, end));
        }
    }
public:
    template <typename I>
    explicit MinimumSegmentTree(I begin, I end) :
        m_length(end - begin),
        m_aligned_length_and_bits(details::get_aligned_size(m_length)),
        m_array((m_aligned_length_and_bits.first << 1) - 1)
    {
        size_t length = (1 << m_aligned_length_and_bits.second) - 1;
        std::copy(begin, end, &m_array[length]);
        length += m_length;
        for (
            int bits = static_cast<int>(m_aligned_length_and_bits.second) - 1, bits_diff = 0;
            bits >= 0;
            --bits, ++bits_diff
        ) {
            for (size_t count = 1 << bits, index = count - 1, i = 0; i < count; ++i, ++index) {
                size_t right = (index + 1) << 1;
                size_t left = right - 1;
                if ((right << bits_diff) < length) {
                    m_array[index] = std::min(m_array[left], m_array[right]);
                } else if ((left << bits_diff) < length) {
                    m_array[index] = m_array[left];
                }
            }
        }
    }

    template <typename V>
    explicit MinimumSegmentTree(std::initializer_list<V> elements) :
        MinimumSegmentTree(elements.begin(), elements.end())
    {
    }

    T minimum(size_t begin, size_t end = -1) const
    {
        if (end > m_length) {
            end = m_length;
        }
        if (begin < end) {
            return get_minimum(begin, end);
        } else {
            return std::numeric_limits<T>::min();
        }
    }

    void replace(size_t index, const T& new_value)
    {
        assert(index < m_length);
        size_t length = (1 << m_aligned_length_and_bits.second) - 1;
        index += length;
        T old = m_array[index];
        m_array[index] = new_value;
        if (old != new_value) {
            if ((index & 1) == 0) {
                --index;
            }
            index >>= 1;

            length += m_length;

            for (size_t bits_diff = 0; ; ++bits_diff) {
                if (index != 0) {
                    size_t right = (index + 1) << 1;
                    size_t left = right - 1;
                    T old = m_array[index];
                    if ((right << bits_diff) < length) {
                        m_array[index] = std::min(m_array[left], m_array[right]);
                    } else if ((left << bits_diff) < length) {
                        m_array[index] = m_array[left];
                    }
                    if (old == m_array[index]) {
                        break;
                    }
                    if ((index & 1) == 0) {
                        --index;
                    }
                    index >>= 1;
                } else {
                    break;
                }
            }
        }
    }

    size_t size() const { return m_length; }
};


void minimum_segment_tree_test()
{
    {
        int nums[] = {9, 1, 7, 3, 2, 0, -10, 4, 5, 6, -9};
        const size_t size = std::size(nums);
        auto begin = std::begin(nums);
        MinimumSegmentTree<int> mst(begin, std::end(nums));
        mst.minimum(6, 8);
        for (size_t span = 1; span <= size; ++span) {
            for (size_t i = 0, j = i + span; j <= size; ++i, ++j) {
                auto expectation = *std::min_element(begin + i, begin + j);
                examine(mst.minimum(i, j) == expectation, "MinimumSegmentTree is failed for the input: [%zu, %zu) at the line: %d\n", i, j, __LINE__);
            }
        }
        for (int retry = 0; retry < 100; ++retry) {
            size_t index = static_cast<size_t>(rand()) % size;
            int new_value = rand() % 100;
            nums[index] = new_value;
            mst.replace(index, new_value);
            for (size_t span = 1; span <= size; ++span) {
                for (size_t i = 0, j = i + span; j <= size; ++i, ++j) {
                    auto expectation = *std::min_element(begin + i, begin + j);
                    auto result = mst.minimum(i, j);
                    //assert(result == expectation);
                    examine(result == expectation, "MinimumSegmentTree is failed for the input: [%zu, %zu) at the line: %d\n", i, j, __LINE__);
                }
            }
        }
    }

    {
        uint32_t nums[] = {9, 1, 7, 3, 11, 12, 0, 2, 8, 13, 14, 10, 4, 5, 6, 19, 21};
        const size_t size = std::size(nums);
        auto begin = std::begin(nums);
        MinimumSegmentTree<uint32_t> mst(begin, std::end(nums));
        for (size_t span = 1; span <= size; ++span) {
            for (size_t i = 0, j = i + span; j <= size; ++i, ++j) {
                auto expectation = *std::min_element(begin + i, begin + j);
                examine(mst.minimum(i, j) == expectation, "MinimumSegmentTree is failed for the input: [%zu, %zu) at the line: %d\n", i, j, __LINE__);
            }
        }
        for (int retry = 0; retry < 100; ++retry) {
            size_t index = static_cast<size_t>(rand()) % size;
            uint32_t new_value = rand() % 100;
            nums[index] = new_value;
            mst.replace(index, new_value);
            for (size_t span = 1; span <= size; ++span) {
                for (size_t i = 0, j = i + span; j <= size; ++i, ++j) {
                    auto expectation = *std::min_element(begin + i, begin + j);
                    auto result = mst.minimum(i, j);
                    //assert(result == expectation);
                    examine(result == expectation, "MinimumSegmentTree is failed for the input: [%zu, %zu) at the line: %d\n", i, j, __LINE__);
                }
            }
        }
    }

    {
        size_t size = rand();
        size %= (1024 * 8);
        std::vector<uint32_t> nums(size);
        for (auto& n : nums) {
            n = rand() % 1000;
        }
        auto begin = std::begin(nums);
        MinimumSegmentTree<uint32_t> mst(begin, std::end(nums));
        for (size_t span = 1; span <= size; ++span) {
            for (size_t i = 0, j = i + span; j <= size; ++i, ++j) {
                auto expectation = *std::min_element(begin + i, begin + j);
                examine(mst.minimum(i, j) == expectation, "MinimumSegmentTree is failed for the input: [%zu, %zu) at the line: %d\n", i, j, __LINE__);
            }
        }
        for (int retry = 0; retry < 100; ++retry) {
            size_t index = static_cast<size_t>(rand()) % size;
            uint32_t new_value = rand() % 100;
            nums[index] = new_value;
            mst.replace(index, new_value);
            for (size_t span = 1; span <= size; ++span) {
                for (size_t i = 0, j = i + span; j <= size; ++i, ++j) {
                    auto expectation = *std::min_element(begin + i, begin + j);
                    auto result = mst.minimum(i, j);
                    //assert(result == expectation);
                    examine(result == expectation, "MinimumSegmentTree is failed for the input: [%zu, %zu) at the line: %d\n", i, j, __LINE__);
                }
            }
        }
    }
}


int main()
{
    sum_segment_tree_test();
    minimum_segment_tree_test();
    printf("OK\n");
    return 0;
}