cmake_minimum_required(VERSION 3.20)
project(Lab5_rhombic_inheritance)

set(CMAKE_CXX_STANDARD 14)

add_executable(Lab5_rhombic_inheritance main.cpp Man.cpp Man.h Employee.cpp Employee.h Programmer.cpp Programmer.h Student.cpp Student.h University_Student.cpp University_Student.h Student_Programmer.cpp Student_Programmer.h menu_functions.cpp menu_functions.h getters.cpp getters.h)
