cmake_minimum_required(VERSION 3.21)
project(consumer C)

set(CMAKE_C_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(consumer main.c ../functions.c)

target_link_libraries(consumer PRIVATE Threads::Threads)