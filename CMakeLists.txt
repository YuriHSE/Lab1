cmake_minimum_required(VERSION 3.29)
project(LinearAlgebra)

set(CMAKE_CXX_STANDARD 20)

add_executable(untitled
        src/matrix.cpp
        include/matrix.h
        tests/test1.cpp
)