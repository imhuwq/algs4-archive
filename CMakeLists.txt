cmake_minimum_required(VERSION 3.8)
project(algs4)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)

# for graph
file(GLOB TEST_CLIENTS RELATIVE ${CMAKE_CURRENT_SOURCE_DIR}/src/graph src/graph/*.cpp)
foreach (testclientsrc ${TEST_CLIENTS})
    string(REPLACE ".cpp" "" testname ${testclientsrc})
    string(CONCAT testclientsrc ${CMAKE_CURRENT_SOURCE_DIR}/src/graph/ ${testclientsrc})
    add_executable(${testname} ${testclientsrc})
endforeach (testclientsrc ${TEST_CLIENTS})

add_executable(main main.cpp)
