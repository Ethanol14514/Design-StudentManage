cmake_minimum_required(VERSION 3.30)
project(bigG)

set(CMAKE_CXX_STANDARD 20)

add_executable(bigG main.cpp
        Student.h
        Student.cpp)
