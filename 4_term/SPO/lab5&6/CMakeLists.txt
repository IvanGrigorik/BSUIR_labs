cmake_minimum_required(VERSION 3.21)
project(lab5 C)

set(CMAKE_C_STANDARD 11)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(lab5 main.c)

target_link_libraries(lab5 PRIVATE Threads::Threads)