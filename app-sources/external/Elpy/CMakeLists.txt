cmake_minimum_required(VERSION 3.10)
project(Elpy)

set(CMAKE_CXX_STANDARD 20)

include_directories(include)

file(GLOB SOURCES "src/*.cpp" "src/DataStructures/*.cpp" "src/Algorithms/*.cpp")

add_executable(Elpy ${SOURCES})

set(CMAKE_CXX_FLAGS_DEBUG "-g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3 -DNDEBUG")