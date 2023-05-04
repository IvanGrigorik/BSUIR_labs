cmake_minimum_required(VERSION 3.23)
project(lab4 CUDA)

set(CMAKE_CUDA_STANDARD 17)
find_package(Thrust REQUIRED CONFIG)
thrust_create_target(Thrust)

add_executable(lab4 main.cu)

set_target_properties(lab4 PROPERTIES
        CUDA_SEPARABLE_COMPILATION ON)
target_link_libraries(lab4 Thrust)
