set(HEADER_FILES
        ../Include/network_operations.h
        ../Include/shell.h
        ../Include/agent.h
        ../Include/systeminfo.h
        ../Include/config.h
        ../Include/persistance.h
        ../Include/is_debugger_present.h
        ../Include/xor_data.h
        catch.hpp) # Make sure this is the correct relative path to catch.hpp

# Define the source files for your tests
set(TEST_SOURCES
        main.cpp
        ../Source/network_operations.cpp
        ../Source/shell.cpp
        ../Source/agent.cpp
        ../Source/systeminfo.cpp
        ../Source/persistance.cpp
        ../Source/is_debugger_present.cpp
        ../Source/xor_data.cpp)

# Create the test executable
add_executable(tests ${TEST_SOURCES} ${HEADER_FILES})
target_link_libraries(tests winhttp)