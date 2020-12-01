cmake_minimum_required(VERSION 3.5)
project(MatrixTest)

set(CMAKE_CXX_STANDARD 17)

if (NOT WIN32)
    set(CMAKE_CXX_FLAGS_RELEASE "-O3")
endif()

add_executable(multest matrix_mul_test.cpp)
