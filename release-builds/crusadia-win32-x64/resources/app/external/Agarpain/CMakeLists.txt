cmake_minimum_required(VERSION 3.10)

# Set the project name
project(Agarpain)

# Specify the C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED True)

# Add the executable
add_executable(Agarpain
src/main.c

src/calculation/calculations_controller.c
src/calculation/mechanics_calculation_controller.c
src/calculation/thermal_physics_calculation_controller.c

src/calculation/mechanics_calculations.c
src/calculation/thermal_physics_calculations.c)

# Include directories
target_include_directories(Agarpain PUBLIC ${PROJECT_SOURCE_DIR}/include)