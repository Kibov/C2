cmake_minimum_required(VERSION 3.26)
project(FernFlower)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -static -static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")
include_directories(include)


add_executable(FernFlower main.cpp
        Include/network_operations.h
        Include/shell.h
        Source/shell.cpp
        Source/network_operations.cpp
        Source/agent.cpp
        Include/agent.h
        Source/systeminfo.cpp
        Include/systeminfo.h
        Include/config.h)

target_link_libraries(FernFlower winhttp)