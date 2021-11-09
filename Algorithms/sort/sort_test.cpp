#include <stdio.h>
#include <stdint.h>
#include <time.h>
#include <algorithm>
#include <vector>
#include <random>
#include <chrono>
#include <stdexcept>
#include <string>

#include "insertion_sort.h"
#include "merge_sort.h"
#include "heap_sort.h"
#include "quick_sort.h"
#include "counting_sort.h"
#include "str_sort.h"

struct PerformanceRecord
{
    std::string function_name;
    double duration;

    PerformanceRecord(const char * name, double d) : function_name(name), duration(d) {}
    PerformanceRecord() : PerformanceRecord("", 0.0) {}

    bool operator<(PerformanceRecord const& other) const noexcept
    {
        return duration < other.duration;
    }
};

void print_record(const char * name, double duration)
{
    printf("%37s: %f seconds\n", name, duration);
}

struct PerformanceRecorder
{
    std::vector<PerformanceRecord> records;
    void save(const char * name, double duration)
    {
        records.emplace_back(name, duration);
    }
};

struct NullPerformanceRecorder
{
    void save(const char *, double) {}
};

#define EXECUTE(data, function, showing_duration, performance_recorder)       \
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
            print_record(#function, duration);                                \
        }                                                                     \
        performance_recorder.save(#function, duration);                       \
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

    [[maybe_unused]] NullPerformanceRecorder recorder;
    EXECUTE(data, insertion_sort, false, recorder);
    EXECUTE(data, merge_sort, false, recorder);
    EXECUTE(data, heap_sort, false, recorder);
    EXECUTE(data, two_way_quick_sort<V1_1Partitioner>, false, recorder);
    EXECUTE(data, two_way_quick_sort<V1_2Partitioner>, false, recorder);
    EXECUTE(data, two_way_quick_sort<V1_3Partitioner>, false, recorder);
    EXECUTE(data, two_way_quick_sort<V1_4Partitioner>, false, recorder);
    EXECUTE(data, v2::two_way_quick_sort, false, recorder);
    EXECUTE(data, two_way_quick_sort<V2_1Partitioner>, false, recorder);
    EXECUTE(data, two_way_quick_sort<V2_2Partitioner>, false, recorder);
    EXECUTE(data, three_way_quick_sort<V3_1Partitioner>, false, recorder);
    EXECUTE(data, three_way_quick_sort<V3_2Partitioner>, false, recorder);
    EXECUTE(data, three_way_quick_sort<V3_3Partitioner>, false, recorder);
    EXECUTE(data, three_way_quick_sort<V3_4Partitioner>, false, recorder);
}

template <typename T>
void cache_test()
{
    [[maybe_unused]] NullPerformanceRecorder recorder;
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
        EXECUTE(data, insertion_sort, true, recorder);
        EXECUTE(data, heap_sort, true, recorder);
        EXECUTE(data, std::sort, true, recorder);
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
    [[maybe_unused]] NullPerformanceRecorder recorder;
    std::uniform_int_distribution<int16_t> value_dist(' ', '~');
    std::uniform_int_distribution<size_t> length_dist(4, 128);
    using details::V4_1Partitioner;
    using details::V4_2Partitioner;
    for (size_t i = 0; i < 3; ++i) {
        size_t size = buf_size * (i + 1);
        print_separator();
        printf("%zu strings:\n", size);
        auto data = create_string_buffer(size, value_dist, length_dist);
        EXECUTE(data, msd_sort, true, recorder);
        EXECUTE(data, str_sort<V4_1Partitioner>, true, recorder);
        EXECUTE(data, str_sort<V4_2Partitioner>, true, recorder);
        EXECUTE(data, std::sort, true, recorder);
    }
}

template <typename T>
void heap_sort_vs_merge_sort()
{
    [[maybe_unused]] NullPerformanceRecorder recorder;
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
        EXECUTE(data, heap_sort, true, recorder);
        EXECUTE(data, merge_sort, true, recorder);
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

        PerformanceRecorder recorder;
        EXECUTE(data, std::sort, false, recorder);
        EXECUTE(data, v2::two_way_quick_sort, false, recorder);
        //EXECUTE(data, v3::three_way_quick_sort, false, recorder);
        EXECUTE(data, three_way_quick_sort<V3_1Partitioner>, false, recorder);
        EXECUTE(data, three_way_quick_sort<V3_2Partitioner>, false, recorder);
        EXECUTE(data, three_way_quick_sort<V3_3Partitioner>, false, recorder);
        EXECUTE(data, three_way_quick_sort<V3_4Partitioner>, false, recorder);
        /*if (i > 4)*/ {
            // may crash !!!
            EXECUTE(data, two_way_quick_sort<V1_1Partitioner>, false, recorder);
            EXECUTE(data, two_way_quick_sort<V1_2Partitioner>, false, recorder);
            EXECUTE(data, two_way_quick_sort<V1_3Partitioner>, false, recorder);
            EXECUTE(data, two_way_quick_sort<V1_4Partitioner>, false, recorder);
        }
        EXECUTE(data, two_way_quick_sort<V2_1Partitioner>, false, recorder);
        /*if (i > 4)*/ {
            // may crash !!!
            EXECUTE(data, two_way_quick_sort<V2_2Partitioner>, false, recorder);
        }
        v3::ThreeWayQuickSort<16, 8> three_way_quick_sort;
        EXECUTE(data, three_way_quick_sort, false, recorder);
        EXECUTE(data, v4::hybird_quick_sort<16>, false, recorder);
    
        print_separator();
        printf("1/%u:\n", i);
        std::sort(recorder.records.begin(), recorder.records.end());
        for (auto const& record : recorder.records) {
            print_record(record.function_name.c_str(), record.duration);
        }
        printf("\n");
    }
}

template <typename T>
void performance_test(const size_t buf_size, const double factor)
{
    std::random_device rd;
    std::uniform_int_distribution<T> dist(0, static_cast<T>(static_cast<double>(buf_size) / factor));
    std::vector<T> data(buf_size);
    for (auto &v : data)
    {
        v = dist(rd);
    }

    PerformanceRecorder recorder;
    EXECUTE(data, std::sort, false, recorder);
    EXECUTE(data, v2::two_way_quick_sort, false, recorder);
    //EXECUTE(data, v3::three_way_quick_sort, true);
    EXECUTE(data, two_way_quick_sort<V1_1Partitioner>, false, recorder);
    EXECUTE(data, two_way_quick_sort<V1_2Partitioner>, false, recorder);
    EXECUTE(data, two_way_quick_sort<V1_3Partitioner>, false, recorder);
    EXECUTE(data, two_way_quick_sort<V1_4Partitioner>, false, recorder);
    EXECUTE(data, two_way_quick_sort<V2_1Partitioner>, false, recorder);
    EXECUTE(data, two_way_quick_sort<V2_2Partitioner>, false, recorder);
    EXECUTE(data, three_way_quick_sort<V3_1Partitioner>, false, recorder);
    EXECUTE(data, three_way_quick_sort<V3_2Partitioner>, false, recorder);
    EXECUTE(data, three_way_quick_sort<V3_3Partitioner>, false, recorder);
    EXECUTE(data, three_way_quick_sort<V3_4Partitioner>, false, recorder);
    EXECUTE(data, merge_sort, false, recorder);
    EXECUTE(data, heap_sort, false, recorder);
    v3::ThreeWayQuickSort<16, 8> three_way_quick_sort_1;
    EXECUTE(data, three_way_quick_sort_1, false, recorder);
    v3::ThreeWayQuickSort<16, 16> three_way_quick_sort_2;
    EXECUTE(data, three_way_quick_sort_2, false, recorder);
    v3::ThreeWayQuickSort<8, 8> three_way_quick_sort_3;
    EXECUTE(data, three_way_quick_sort_3, false, recorder);
    v3::ThreeWayQuickSort<4, 8> three_way_quick_sort_4;
    EXECUTE(data, three_way_quick_sort_4, false, recorder);
    EXECUTE(data, v4::hybird_quick_sort<64>, false, recorder);
    EXECUTE(data, v4::hybird_quick_sort<32>, false, recorder);
    EXECUTE(data, v4::hybird_quick_sort<16>, false, recorder);
    EXECUTE(data, v4::hybird_quick_sort<8>, false, recorder);
    print_separator();
    printf("factor: %f\n", factor);
    std::sort(recorder.records.begin(), recorder.records.end());
    for (auto const& record : recorder.records) {
        print_record(record.function_name.c_str(), record.duration);
    }
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
    [[maybe_unused]] NullPerformanceRecorder recorder;
    print_separator();
    printf("%zu %s:\n", buf_size, typeid(T).name());
    EXECUTE(data, std::sort, true, recorder);
    EXECUTE(data, integer_sort, true, recorder);
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
    [[maybe_unused]] NullPerformanceRecorder recorder;
    print_separator();
    printf("%zu %s:\n", buf_size, typeid(T).name());
    EXECUTE(data, std::sort, true, recorder);
    EXECUTE(data, integer_sort, true, recorder);
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

int main(int argc, char* argv[])
{
    bool verifying = false;
    if (argc > 1 && strcmp(argv[1], "verify") == 0) {
        verifying = true;
    }

#if ( defined( _DEBUG ) || defined( DEBUG ) || defined( DBG ) )
    size_t BUF_SIZE = 107;
#else
    size_t BUF_SIZE = 1923437;
#endif

    if (verifying) {
        BUF_SIZE = 21739;
    }

    try {
        {
            [[maybe_unused]] NullPerformanceRecorder recorder;
            std::vector<std::string> data = {
                "98764", "3745672", "1236347", "3", "38374356", "9476453", "39072534", "7456623",
                "34866352", "5678452", "38456342", "5623434", "50798567", "263454", "8456456",
                "846353246", "347541", "45678456", "496754", "678905678", "845652", "37452",
                "6532645", "384563", "2634234", "657454", "5474567", "4557568", "2323348",
                "1233545", "426346", "345634", "456345", "23423", "435234", "564745",
                "2", "9", "8", "7", "6", "5", "4", "1"
            };
            EXECUTE(data, msd_sort, false, recorder);
            using details::V4_1Partitioner;
            using details::V4_2Partitioner;
            EXECUTE(data, str_sort<V4_1Partitioner>, false, recorder);
            EXECUTE(data, str_sort<V4_2Partitioner>, false, recorder);
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

        if (!verifying) {
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<> dis(0.0, 1.0);
            
            for (double i = 0; i <= 16; i += 1.0) {
                performance_test<int64_t>(BUF_SIZE + static_cast<size_t>(i * 235437), i + dis(gen));
                printf("\n");
            }
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
