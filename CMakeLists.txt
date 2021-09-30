cmake_minimum_required(VERSION 3.20)
project(Sort C)

set(CMAKE_C_STANDARD 11)

add_executable(Sort main.c Vector.c Vector.h SortAlgorithm.c SortAlgorithm.h)
