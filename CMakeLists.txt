cmake_minimum_required(VERSION 3.8)
project(algs4)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

# for search
file(GLOB SEARCH_TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src/search src/search/*.cpp)
foreach (search_test_src ${SEARCH_TEST_SRCS})
    string(REPLACE ".cpp" "" testname ${search_test_src})
    string(CONCAT search_test_src ${CMAKE_CURRENT_SOURCE_DIR}/src/search/ ${search_test_src})
    add_executable(${testname} ${search_test_src})
endforeach (search_test_src ${SEARCH_TEST_SRCS})


# for graph
file(GLOB GRAPH_TEST_SRCS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src/graph src/graph/*.cpp)
foreach (graph_test_src ${GRAPH_TEST_SRCS})
    string(REPLACE ".cpp" "" testname ${graph_test_src})
    string(CONCAT graph_test_src ${CMAKE_CURRENT_SOURCE_DIR}/src/graph/ ${graph_test_src})
    add_executable(${testname} ${graph_test_src})
endforeach (graph_test_src ${GRAPH_TEST_SRCS})
