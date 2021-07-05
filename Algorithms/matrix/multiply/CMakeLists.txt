cmake_minimum_required(VERSION 3.5)
project(MatrixTest)

set(CMAKE_CXX_STANDARD 17)

if (NOT WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -Wextra -Wconversion -Wpedantic")
endif()

add_executable(multest matrix_mul_test.cpp matrix_multiply.h matrix.h)
