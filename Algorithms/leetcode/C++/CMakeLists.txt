cmake_minimum_required(VERSION 3.5)
project(LeetcodeStudy)

set(CXX_STANDARD_VERSION 20)

if (WIN32)
    set(CXX_LATEST_VERSION_ENABLED 0)
    if (MSVC_VERSION GREATER_EQUAL "1900")
        include(CheckCXXCompilerFlag)
        CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
        if (_cpp_latest_flag_supported)
            add_compile_options("/std:c++latest")
            set(CXX_LATEST_VERSION_ENABLED 1)
        endif()
    endif()
    if (NOT ${CXX_LATEST_VERSION_ENABLED})
        set(CXX_STANDARD_VERSION 17)
    endif()
endif()
add_compile_definitions(CXX_STANDARD_VERSION=${CXX_STANDARD_VERSION})

set(CMAKE_CXX_STANDARD ${CXX_STANDARD_VERSION})
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /FA")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Wall")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra")
endif()

include(TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN_MACHINE)
if (NOT IS_BIG_ENDIAN_MACHINE)
    add_definitions(-DLITTLE_ENDIAN_MACHINE)
endif()

enable_testing()

add_executable(intervals_test intervals_test.cpp check.h)
add_test(NAME intervals_test COMMAND intervals_test)
add_executable(reverse_words_test reverse_words_test.cpp check.h)
add_test(NAME reverse_words_test COMMAND reverse_words_test)
add_executable(copy_list_with_random_pointer copy_list_with_random_pointer.cpp check.h)
add_test(NAME copy_list_with_random_pointer COMMAND copy_list_with_random_pointer)
add_executable(text_justification text_justification.cpp check.h)
add_test(NAME text_justification COMMAND text_justification)
add_executable(largest_number_test largest_number_test.cpp check.h)
add_test(NAME largest_number_test COMMAND largest_number_test)
add_executable(word_ladder_test word_ladder_test.cpp check.h)
add_test(NAME word_ladder_test COMMAND word_ladder_test)
add_executable(sliding_window_maximum sliding_window_maximum.cpp check.h)
add_test(NAME sliding_window_maximum COMMAND sliding_window_maximum)
add_executable(minimum_window_substring minimum_window_substring.cpp check.h)
add_test(NAME minimum_window_substring COMMAND minimum_window_substring)
add_executable(decode_string_test decode_string_test.cpp check.h)
add_test(NAME decode_string_test COMMAND decode_string_test)
add_executable(interleaving_string_test interleaving_string_test.cpp check.h)
add_test(NAME interleaving_string_test COMMAND interleaving_string_test)
add_executable(distinct_subsequences_test distinct_subsequences_test.cpp check.h)
add_test(NAME distinct_subsequences_test COMMAND distinct_subsequences_test)
add_executable(scramble_string_test scramble_string_test.cpp check.h)
add_test(NAME scramble_string_test COMMAND scramble_string_test)
add_executable(longest_consecutive_sequence longest_consecutive_sequence.cpp check.h)
target_include_directories(longest_consecutive_sequence PUBLIC ../../sort)
add_test(NAME longest_consecutive_sequence COMMAND longest_consecutive_sequence)
add_executable(top_k_frequent_elements_test top_k_frequent_elements_test.cpp check.h)
target_include_directories(top_k_frequent_elements_test PUBLIC ../../sort)
add_test(NAME top_k_frequent_elements_test COMMAND top_k_frequent_elements_test)
add_executable(median_of_two_sorted_arrays_test median_of_two_sorted_arrays_test.cpp check.h)
add_test(NAME median_of_two_sorted_arrays_test COMMAND median_of_two_sorted_arrays_test)
add_executable(largest_rectangle_in_histogram_test largest_rectangle_in_histogram_test.cpp check.h)
add_test(NAME largest_rectangle_in_histogram_test COMMAND largest_rectangle_in_histogram_test)
add_executable(linked_list_test linked_list_test.cpp check.h)
add_test(NAME linked_list_test COMMAND linked_list_test)
add_executable(array_algorithms_test array_algorithms_test.cpp check.h)
add_test(NAME array_algorithms_test COMMAND array_algorithms_test)
add_executable(search_test search_test.cpp check.h)
add_test(NAME search_test COMMAND search_test)
add_executable(backtracking_test backtracking_test.cpp check.h)
add_test(NAME backtracking_test COMMAND backtracking_test)
add_executable(dynamic_programming_test dynamic_programming_test.cpp check.h)
add_test(NAME dynamic_programming_test COMMAND dynamic_programming_test)
add_executable(number_test number_test.cpp check.h)
add_test(NAME number_test COMMAND number_test)
add_executable(segment_tree_test segment_tree_test.cpp check.h)
add_test(NAME segment_tree_test COMMAND segment_tree_test)
