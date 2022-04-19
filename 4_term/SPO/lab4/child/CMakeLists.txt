cmake_minimum_required(VERSION 3.21)
project(child C)

set(CMAKE_C_STANDARD 11)

add_executable(child main.c functions_child.c functions_child.h)
