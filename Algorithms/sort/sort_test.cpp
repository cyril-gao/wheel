#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <stdexcept>

#include "insertion_sort.h"
#include "merge_sort.h"
#include "heap_sort.h"
#include "quick_sort.h"
#include "counting_sort.h"
#include "str_sort.h"


#define EXECUTE(data, function, showing_duration)                             \
    do                                                                        \
    {                                                                         \
        auto copy(data);                                                      \
        auto begin = std::chrono::system_clock::now();                        \
        function(copy.begin(), copy.end());                                   \
        auto end = std::chrono::system_clock::now();                          \
        if (!std::is_sorted(copy.begin(), copy.end()))                        \
        {                                                                     \
            throw std::runtime_error(#function " is bad");                    \
        }                                                                     \
        double duration = std::chrono::duration<double>(end - begin).count(); \
        if (showing_duration)                                                 \
        {                                                                     \
            printf("%37s: %f seconds\n", #function, duration);                \
        }                                                                     \
    } while (false)

inline void print_separator()
{
    printf("_______________________________________________________\n");
}

template <typename T>
void verification_test()
{
    const size_t BUF_SIZE = 13873;
    std::random_device rd;
    std::uniform_int_distribution<T> dist(0, static_cast<T>(BUF_SIZE / 2));
    std::vector<T> data(BUF_SIZE);
    for (auto &v : data)
    {
        v = dist(rd);
    }

    EXECUTE(data, insertion_sort, false);
    EXECUTE(data, merge_sort, false);
    EXECUTE(data, heap_sort, false);
    EXECUTE(data, two_way_quick_sort<V1_1Partitioner>, false);
    EXECUTE(data, two_way_quick_sort<V1_2Partitioner>, false);
    EXECUTE(data, two_way_quick_sort<V1_3Partitioner>, false);
    EXECUTE(data, two_way_quick_sort<V1_4Partitioner>, false);
    EXECUTE(data, v2::two_way_quick_sort, false);
    EXECUTE(data, two_way_quick_sort<V2_1Partitioner>, false);
    EXECUTE(data, two_way_quick_sort<V2_2Partitioner>, false);
    EXECUTE(data, three_way_quick_sort<V3_1Partitioner>, false);
    EXECUTE(data, three_way_quick_sort<V3_2Partitioner>, false);
    EXECUTE(data, three_way_quick_sort<V3_3Partitioner>, false);
    EXECUTE(data, three_way_quick_sort<V3_4Partitioner>, false);
}

template <typename T>
void cache_test()
{
    for (size_t i = 16; i <= 1024; i += i)
    {
        std::random_device rd;
        std::uniform_int_distribution<T> dist(0, static_cast<T>(i / 2));
        std::vector<T> data(i);
        for (auto &v : data)
        {
            v = dist(rd);
        }
        print_separator();
        printf("%zu %zu-byte integers:\n", i, sizeof(T));
        EXECUTE(data, insertion_sort, true);
        EXECUTE(data, heap_sort, true);
        EXECUTE(data, std::sort, true);
        printf("\n");
    }
}

std::vector<std::string> create_string_buffer(
    const size_t buf_size,
    std::uniform_int_distribution<int16_t>& value_dist,
    std::uniform_int_distribution<size_t>& length_dist
) {
    std::random_device rd;
    std::vector<std::string> retval;
    retval.reserve(buf_size);
    for (size_t i = 0; i < buf_size; ++i) {
        size_t len = length_dist(rd);
        std::string tmp;
        tmp.reserve(len + 1);
        for (size_t j = 0; j < len; ++j) {
            tmp.push_back(static_cast<char>(value_dist(rd)));
        }
        retval.emplace_back(std::move(tmp));
    }
    return retval;
}

void str_sort_test(const size_t buf_size)
{
    std::uniform_int_distribution<int16_t> value_dist(' ', '~');
    std::uniform_int_distribution<size_t> length_dist(4, 128);
    using details::V4_1Partitioner;
    using details::V4_2Partitioner;
    for (int i = 0; i < 3; ++i) {
        size_t size = buf_size * (i + 1);
        print_separator();
        printf("%zu strings:\n", size);
        auto data = create_string_buffer(size, value_dist, length_dist);
        EXECUTE(data, msd_sort, true);
        EXECUTE(data, str_sort<V4_1Partitioner>, true);
        EXECUTE(data, str_sort<V4_2Partitioner>, true);
        EXECUTE(data, std::sort, true);
    }
}

template <typename T>
void heap_sort_vs_merge_sort()
{
    for (size_t i = 64; i <= 4096; i += i)
    {
        std::random_device rd;
        std::uniform_int_distribution<T> dist(0, static_cast<T>(i / 2));
        std::vector<T> data(i);
        for (auto &v : data)
        {
            v = dist(rd);
        }
        print_separator();
        printf("%zu %zu-byte integers:\n", i, sizeof(T));
        EXECUTE(data, heap_sort, true);
        EXECUTE(data, merge_sort, true);
        printf("\n");
    }
}

template <typename T>
void quick_sort_extreme_cases(const size_t buf_size)
{
    srand(static_cast<unsigned int>(time(nullptr)));
    for (unsigned int i = 10; i > 0; --i)
    {
        std::vector<T> data(buf_size);
        for (auto &v : data)
        {
            v = static_cast<T>(rand()) % i;
        }
        print_separator();
        printf("1/%u:\n", i);
        EXECUTE(data, std::sort, true);
        EXECUTE(data, v2::two_way_quick_sort, true);
        //EXECUTE(data, v3::three_way_quick_sort, true);
        EXECUTE(data, three_way_quick_sort<V3_1Partitioner>, true);
        EXECUTE(data, three_way_quick_sort<V3_2Partitioner>, true);
        EXECUTE(data, three_way_quick_sort<V3_3Partitioner>, true);
        EXECUTE(data, three_way_quick_sort<V3_4Partitioner>, true);
        /*if (i > 4)*/ {
            // may crash !!!
            EXECUTE(data, two_way_quick_sort<V1_1Partitioner>, true);
            EXECUTE(data, two_way_quick_sort<V1_2Partitioner>, true);
            EXECUTE(data, two_way_quick_sort<V1_3Partitioner>, true);
            EXECUTE(data, two_way_quick_sort<V1_4Partitioner>, true);
        }
        EXECUTE(data, two_way_quick_sort<V2_1Partitioner>, true);
        /*if (i > 4)*/ {
            // may crash !!!
            EXECUTE(data, two_way_quick_sort<V2_2Partitioner>, true);
        }
        v3::ThreeWayQuickSort<16, 8> three_way_quick_sort;
        EXECUTE(data, three_way_quick_sort, true);
        EXECUTE(data, v4::hybird_quick_sort<16>, true);
        printf("\n");
    }
}

template <typename T>
void performance_test(const size_t buf_size, const double factor)
{
    std::random_device rd;
    std::uniform_int_distribution<T> dist(0, static_cast<T>(buf_size / factor));
    std::vector<T> data(buf_size);
    for (auto &v : data)
    {
        v = dist(rd);
    }

    print_separator();
    printf("factor: %f\n", factor);
    EXECUTE(data, std::sort, true);
    EXECUTE(data, v2::two_way_quick_sort, true);
    //EXECUTE(data, v3::three_way_quick_sort, true);
    EXECUTE(data, two_way_quick_sort<V1_1Partitioner>, true);
    EXECUTE(data, two_way_quick_sort<V1_2Partitioner>, true);
    EXECUTE(data, two_way_quick_sort<V1_3Partitioner>, true);
    EXECUTE(data, two_way_quick_sort<V1_4Partitioner>, true);
    EXECUTE(data, two_way_quick_sort<V2_1Partitioner>, true);
    EXECUTE(data, two_way_quick_sort<V2_2Partitioner>, true);
    EXECUTE(data, three_way_quick_sort<V3_1Partitioner>, true);
    EXECUTE(data, three_way_quick_sort<V3_2Partitioner>, true);
    EXECUTE(data, three_way_quick_sort<V3_3Partitioner>, true);
    EXECUTE(data, three_way_quick_sort<V3_4Partitioner>, true);
    EXECUTE(data, merge_sort, true);
    EXECUTE(data, heap_sort, true);
    v3::ThreeWayQuickSort<16, 8> three_way_quick_sort_1;
    EXECUTE(data, three_way_quick_sort_1, true);
    v3::ThreeWayQuickSort<16, 16> three_way_quick_sort_2;
    EXECUTE(data, three_way_quick_sort_2, true);
    v3::ThreeWayQuickSort<8, 8> three_way_quick_sort_3;
    EXECUTE(data, three_way_quick_sort_3, true);
    v3::ThreeWayQuickSort<4, 8> three_way_quick_sort_4;
    EXECUTE(data, three_way_quick_sort_4, true);
    EXECUTE(data, v4::hybird_quick_sort<32>, true);
    EXECUTE(data, v4::hybird_quick_sort<16>, true);
    EXECUTE(data, v4::hybird_quick_sort<8>, true);
}

template <typename T>
void counting_sort_test_cast_for_bytes(size_t buf_size)
{
    std::random_device rd;
    std::uniform_int_distribution<int16_t> dist(
        std::numeric_limits<int16_t>::min(),
        std::numeric_limits<int16_t>::max()
    );
    std::vector<T> data(buf_size);
    for (auto& v : data) {
        v = static_cast<T>(dist(rd));
    }
    print_separator();
    printf("%zu %s:\n", buf_size, typeid(T).name());
    EXECUTE(data, std::sort, true);
    EXECUTE(data, integer_sort, true);
}

template <typename T>
void counting_sort_test_cast(size_t buf_size)
{
    std::random_device rd;
    std::uniform_int_distribution<T> dist(
        std::numeric_limits<T>::min(),
        std::numeric_limits<T>::max()
    );
    std::vector<T> data(buf_size);
    for (auto& v : data) {
        v = dist(rd);
    }
    print_separator();
    printf("%zu %s:\n", buf_size, typeid(T).name());
    EXECUTE(data, std::sort, true);
    EXECUTE(data, integer_sort, true);
}

void counting_sort_test(size_t buf_size)
{
    counting_sort_test_cast_for_bytes<char>(buf_size);
    counting_sort_test_cast_for_bytes<uint8_t>(buf_size);
    counting_sort_test_cast_for_bytes<int8_t>(buf_size);
    counting_sort_test_cast<int16_t>(buf_size);
    counting_sort_test_cast<uint16_t>(buf_size);
    counting_sort_test_cast<int32_t>(buf_size);
    counting_sort_test_cast<uint32_t>(buf_size);
    counting_sort_test_cast<int64_t>(buf_size);
    counting_sort_test_cast<uint64_t>(buf_size);
}

int main()
{
#if ( defined( _DEBUG ) || defined( DEBUG ) || defined( DBG ) )
    const size_t BUF_SIZE = 107;
#else
    const size_t BUF_SIZE = 1923437;
#endif
    try
    {
        {
            std::vector<std::string> data = {
                "98764", "3745672", "1236347", "3", "38374356", "9476453", "39072534", "7456623",
                "34866352", "5678452", "38456342", "5623434", "50798567", "263454", "8456456",
                "846353246", "347541", "45678456", "496754", "678905678", "845652", "37452",
                "6532645", "384563", "2634234", "657454", "5474567", "4557568", "2323348",
                "1233545", "426346", "345634", "456345", "23423", "435234", "564745",
                "2", "9", "8", "7", "6", "5", "4", "1"
            };
            EXECUTE(data, msd_sort, false);
            using details::V4_1Partitioner;
            using details::V4_2Partitioner;
            EXECUTE(data, str_sort<V4_1Partitioner>, false);
            EXECUTE(data, str_sort<V4_2Partitioner>, false);
        }
        verification_test<int16_t>();
        verification_test<int64_t>();

        cache_test<int32_t>();
        printf("\n");
        cache_test<int64_t>();
        printf("\n");
        heap_sort_vs_merge_sort<int64_t>();
        printf("\n");

        counting_sort_test(BUF_SIZE);
        printf("\n");

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        
        for (double i = 0; i <= 16; i += 1.0)
        {
            performance_test<int64_t>(BUF_SIZE + i * 235437, i + dis(gen));
            printf("\n");
        }

        quick_sort_extreme_cases<int64_t>(BUF_SIZE / 10);
        printf("\n");

        str_sort_test(BUF_SIZE);
        printf("\n");
    }
    catch (std::exception const &e)
    {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }
    return 0;
}
