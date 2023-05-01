cmake_minimum_required(VERSION 3.25)
project(lab5 CUDA)

set(CMAKE_CUDA_STANDARD 17)
#find_package(Thrust REQUIRED CONFIG)
#thrust_create_target(Thrust)

add_executable(lab5 main.cu Image.cu Image.cuh cpu.cu utilities.cuh)

set_target_properties(lab5 PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
#target_link_libraries(lab5 Thrust)