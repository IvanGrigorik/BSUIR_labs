cmake_minimum_required(VERSION 3.22)
project(lab10 C)

set(CMAKE_C_STANDARD 17)
set(THREADS_PREFER_PTHREAD_FLAG ON)
find_package(Threads REQUIRED)

add_executable(lab10 main.c)
target_link_libraries(lab10 rt Threads::Threads)