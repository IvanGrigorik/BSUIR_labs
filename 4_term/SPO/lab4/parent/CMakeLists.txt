cmake_minimum_required(VERSION 3.21)
project(parent C)

set(CMAKE_C_STANDARD 11)

add_executable(parent main.c parent_functions.c parent_functions.h)
