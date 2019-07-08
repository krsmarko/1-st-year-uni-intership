cmake_minimum_required(VERSION 3.0)

project(YaContest2 CXX)

if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug)
endif(NOT CMAKE_BUILD_TYPE)

set(CMAKE_CXX_STANDARD 11)

add_executable(ProblemA problem_a/problem_a.cpp)
