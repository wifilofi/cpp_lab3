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

# Настройки для разных компиляторов
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(-Wall -Wextra -O3 -march=native)
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        add_compile_options(-Wno-unused-command-line-argument)
    endif ()
elseif (CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
    add_compile_options(/W4 /O2 /arch:AVX2)
endif ()


add_executable(benchmark
        benchmark.cpp)

target_link_libraries(benchmark PRIVATE nanobench)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})


#[[
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/visualize.py
        ${CMAKE_BINARY_DIR}/visualize.py
        COPYONLY)

add_custom_target(visualize
        COMMAND python visualize.py
        WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
        DEPENDS benchmark
)
]]

#[[
add_executable(visualize
        visualize.py)
]]
