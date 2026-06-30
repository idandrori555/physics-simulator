cmake_minimum_required(VERSION 3.25)
project(PhysicsSimulator CXX)

# Enforce C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Collect all source files
set(SOURCES
    src/main.cpp
    src/vector.cpp
    src/object.cpp
    src/simulator.cpp
)

# Define the executable target
add_executable(physics_sim ${SOURCES})

# Include directory setup
# This ensures files can simply include via "include/simulator.hpp" or similar
target_include_directories(physics_sim PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Turn on useful compiler warnings to keep the code clean
if(MSVC)
    target_compile_options(physics_sim PRIVATE /W4)
else()
    target_compile_options(physics_sim PRIVATE -Wall -Wextra -Wpedantic)
endif()
