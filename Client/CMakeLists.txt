cmake_minimum_required(VERSION 3.26)
project(FernFlower)

set(CMAKE_CXX_STANDARD 20)
include_directories(include)


add_executable(FernFlower main.cpp
        Include/network_operations.h
        Include/shell.h
        Source/shell.cpp
        Source/network_operations.cpp)

target_link_libraries(FernFlower winhttp)