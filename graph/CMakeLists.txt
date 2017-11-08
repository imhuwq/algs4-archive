cmake_minimum_required(VERSION 3.8)
project(algs4_graph)

set(CMAKE_CXX_STANDARD 11)

include_directories(include)
file(GLOB graph_SRC
        main.cpp
        include/*.hpp
        src/*.cpp)

add_executable(graph ${graph_SRC})
