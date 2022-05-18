cmake_minimum_required(VERSION 3.22)
project(client C)

set(CMAKE_C_STANDARD 17)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(client main.c)

target_link_libraries(client Threads::Threads)