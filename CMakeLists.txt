cmake_minimum_required(VERSION 4.1)
project(cpp_lab3)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
        nanobench
        GIT_REPOSITORY https://github.com/martinus/nanobench.git
        GIT_TAG v4.1.0
        GIT_SHALLOW TRUE)

FetchContent_MakeAvailable(nanobench)

add_executable(lab3
        main.cpp
        include/sort.h
)

# google test
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.17.0
)

add_executable(sort_tests
sort_tests.cpp)

target_link_libraries(
        sort_tests
        gtest
)


# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)


add_executable(benchmark
        benchmark.cpp
)

target_link_libraries(benchmark PRIVATE nanobench)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
enable_testing()