cmake_minimum_required(VERSION 3.20)
project(Sort C)

set(CMAKE_C_STANDARD 11)

MATH(EXPR stack_size "1024*1024*1024")
set(CMAKE_EXE_LINKER_FLAGS "-Wl,-stack,${stack_size}")

add_executable(Sort main.c Vector.c Vector.h SortAlgorithm.c SortAlgorithm.h)
