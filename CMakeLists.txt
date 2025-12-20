cmake_minimum_required(VERSION 4.1)
project(cpp_lab3)

set(CMAKE_CXX_STANDARD 20)

add_executable(cpp_lab3 main.cpp
        include/sort.h
        benchmark.cpp
        nanobench.h
)
