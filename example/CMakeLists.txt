project(symbolicmath_examples)

cmake_minimum_required(VERSION 2.8)

#========================================================

include_directories( ../include )

#set(CMAKE_CXX_STANDARD 11)
add_definitions(-std=c++11) 

add_executable( Example
    example.cc
    )
