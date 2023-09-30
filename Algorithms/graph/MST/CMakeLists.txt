cmake_minimum_required(VERSION 3.5)
project(MSTStudy)

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

include_directories("../../heap")

add_executable(mst_test mst_test.cpp mst.cpp prim.cpp kruskal.cpp uf.cpp uf.h mst.h graph_factory.h graph.h check.h)
set_target_properties(mst_test PROPERTIES DEBUG_POSTFIX ${CMAKE_DEBUG_POSTFIX})
add_test(NAME mst_test COMMAND mst_test)
