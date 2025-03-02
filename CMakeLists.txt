# Minimum required version of CMake
cmake_minimum_required(VERSION 3.10)

# Project name
project(ChatTerm)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 11)

# Include directories for header files
include_directories(${CMAKE_SOURCE_DIR}/lib)

# Add the server and client executable
add_executable(server src/server.cpp)
add_executable(client src/client.cpp)

# Link libraries (if you have any external libraries, e.g., pthreads for threads)
# target_link_libraries(server pthread)
# target_link_libraries(client pthread)

