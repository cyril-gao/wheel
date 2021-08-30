cmake_minimum_required(VERSION 3.5)
project(NumberStudy)

set(CXX_STANDARD_VERSION 20)
add_compile_definitions(CXX_STANDARD_VERSION=${CXX_STANDARD_VERSION})

set(CMAKE_CXX_STANDARD ${CXX_STANDARD_VERSION})
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /W4 /FA")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} /Wall")
else()
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wconversion -Wpedantic")
    set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -Wall -Wextra")
endif()

enable_testing()

find_package(OpenSSL REQUIRED)

add_executable(integer_test integer_test.cpp integer.h check.h)
target_link_libraries(integer_test OpenSSL::Crypto)
add_test(NAME integer_test COMMAND integer_test "test")
