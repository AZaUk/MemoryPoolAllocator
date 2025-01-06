cmake_minimum_required(VERSION 3.26)
project(APC)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(APC
        main.cpp
        MemoryPoolAllocator.cpp
        MemoryPoolAllocator.h)
