cmake_minimum_required(VERSION 3.28)
project(Course)

set(CMAKE_CXX_STANDARD 20)

add_executable(Course main.cpp
        del.cpp
        files.h
        files.cpp
        structures.h)
