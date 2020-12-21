cmake_minimum_required(VERSION 3.16)
project(multiThreadWithVar)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS -pthread)
add_executable(multiThreadWithVar main.cpp)