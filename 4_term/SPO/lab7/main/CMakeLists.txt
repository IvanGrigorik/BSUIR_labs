cmake_minimum_required(VERSION 3.21)
project(main C)

set(CMAKE_C_STANDARD 11)

set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(main main.c functions.c)

target_link_libraries(main PRIVATE Threads::Threads)