cmake_minimum_required(VERSION 3.16)
project(multiThreadWithMutex)

set(CMAKE_CXX_STANDARD 14)
SET(CMAKE_CXX_FLAGS -pthread)
add_executable(multiThreadWithMutex main.cpp)