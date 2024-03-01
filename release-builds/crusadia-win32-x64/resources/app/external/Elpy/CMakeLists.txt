cmake_minimum_required(VERSION 3.10)
project(Elpy)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 20)

# Include directories
include_directories(include)

# Automatically find source files
file(GLOB SOURCES "src/*.cpp" "src/DataStructures/*.cpp" "src/Algorithms/*.cpp")

# Define the executable
add_executable(Elpy ${SOURCES})

# Set different compile options for debug and release builds
set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")

# set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -march=native")

# set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} -s")