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
        EXECUTE(data, three_way_quick_sort<V3_1Partitioner>, true);
        EXECUTE(data, three_way_quick_sort<V3_2Partitioner>, true);
        EXECUTE(data, three_way_quick_sort<V3_3Partitioner>, true);
        EXECUTE(data, three_way_quick_sort<V3_4Partitioner>, true);
        EXECUTE(data, two_way_quick_sort<V1_1Partitioner>, true);
        EXECUTE(data, two_way_quick_sort<V1_2Partitioner>, true);
        EXECUTE(data, two_way_quick_sort<V1_3Partitioner>, true);
        EXECUTE(data, two_way_quick_sort<V1_4Partitioner>, true);
        EXECUTE(data, two_way_quick_sort<V2_1Partitioner>, true);
        EXECUTE(data, two_way_quick_sort<V2_2Partitioner>, true);
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
    EXECUTE(data, std::sort, true);
}

int main()
{
    try
    {
        verification_test<int16_t>();
        verification_test<int64_t>();

        cache_test<int32_t>();
        printf("\n");
        cache_test<int64_t>();
        printf("\n");
        heap_sort_vs_merge_sort<int64_t>();
        printf("\n");

        std::random_device rd;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<> dis(0.0, 1.0);
        const size_t BUF_SIZE = 1023437;
        for (double i = 0; i <= 16; i += 1.0)
        {
            performance_test<int64_t>(BUF_SIZE, i + dis(gen));
            printf("\n");
        }

        quick_sort_extreme_cases<int64_t>(BUF_SIZE/10);
    }
    catch (std::exception const &e)
    {
        fprintf(stderr, "%s\n", e.what());
        return 1;
    }
    return 0;
}
//Standard mersenne_twister_engine seeded with rd()
