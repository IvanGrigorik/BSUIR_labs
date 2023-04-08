cmake_minimum_required(VERSION 3.25)
project(lab5_6 CUDA)

set(CMAKE_CUDA_STANDARD 17)

add_executable(lab5_6 main.cu)

set_target_properties(lab5_6 PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)
