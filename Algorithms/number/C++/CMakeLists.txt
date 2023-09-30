cmake_minimum_required(VERSION 3.5)
project(NumberStudy)

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

find_package(OpenSSL REQUIRED)

add_executable(integer_test integer_test.cpp integer.h check.h)
target_link_libraries(integer_test OpenSSL::Crypto)
set_target_properties(integer_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
add_test(NAME integer_test COMMAND integer_test "test")
