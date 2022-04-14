cmake_minimum_required(VERSION 3.21)
project(lab8 C)

set(CMAKE_C_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(lab8 main.c circle.h)

target_link_libraries(lab8 PRIVATE Threads::Threads)