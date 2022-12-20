cmake_minimum_required(VERSION 3.23)
project(lab6)

set(CMAKE_CXX_STANDARD 17)
link_libraries(ws2_32 wsock32 strmiids bthprops winmm.lib)

add_executable(lab6 main.cpp)
