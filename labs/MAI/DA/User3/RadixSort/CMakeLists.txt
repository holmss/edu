cmake_minimum_required(VERSION 3.8)
project(RadixSort)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES
        main.cpp
        Radix.cpp
        Vector.cpp)

add_executable(RadixSort ${SOURCE_FILES})