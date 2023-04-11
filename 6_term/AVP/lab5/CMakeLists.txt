cmake_minimum_required(VERSION 3.25)
project(lab5 CUDA)

set(CMAKE_CUDA_STANDARD 17)

add_executable(lab5 main.cu Image.cu Image.h)

set_target_properties(lab5 PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)
