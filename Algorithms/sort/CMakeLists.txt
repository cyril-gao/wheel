cmake_minimum_required(VERSION 3.5)
project(SortStudy)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_EXTENSIONS OFF)

if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /FA")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Wall")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fprofile-arcs -ftest-coverage")
endif()

set(CMAKE_DEBUG_POSTFIX d)
enable_testing()

include(TestBigEndian)
TEST_BIG_ENDIAN(IS_BIG_ENDIAN_MACHINE)
if (NOT IS_BIG_ENDIAN_MACHINE)
    add_definitions(-DLITTLE_ENDIAN_MACHINE)
endif()

add_executable(sort_test sort_test.cpp insertion_sort.h merge_sort.h heap_sort.h quick_sort.h counting_sort.h str_sort.h)
set_target_properties(sort_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
add_test(NAME sort_test COMMAND sort_test "verify")
