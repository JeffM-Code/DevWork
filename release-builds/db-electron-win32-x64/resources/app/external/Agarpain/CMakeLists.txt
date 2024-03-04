cmake_minimum_required(VERSION 3.10)

project(Agarpain)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

file(GLOB_RECURSE SOURCES "src/*.c")

add_executable(Agarpain ${SOURCES})

target_include_directories(Agarpain PUBLIC ${PROJECT_SOURCE_DIR}/include)