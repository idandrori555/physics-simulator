cmake_minimum_required(VERSION 3.25)
project(PhysicsSimulator CXX)

# Enforce C++23 standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 1. Fetch SDL3 from source automatically
include(FetchContent)
FetchContent_Declare(
    SDL3
    GIT_REPOSITORY https://github.com/libsdl-org/SDL.git
    GIT_TAG        main # Or use a specific tag like release-3.2.0
)

# Disable SDL3 components you might not need to speed up compilation
set(SDL_SHARED ON CACHE BOOL "" FORCE)
set(SDL_STATIC OFF CACHE BOOL "" FORCE)
set(SDL_TEST_LIBRARY OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(SDL3)

# 2. Collect all source files
set(SOURCES
    src/main.cpp
    src/vector.cpp
    src/object.cpp
    src/simulator.cpp
    src/graphics.cpp
)

# Define the executable target
add_executable(physics_sim ${SOURCES})

# Include directory setup
target_include_directories(physics_sim PRIVATE 
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

# Link against the fetched SDL3 target
# SDL3 provides a single main target: SDL3::SDL3
target_link_libraries(physics_sim PRIVATE SDL3::SDL3)

# Turn on useful compiler warnings to keep the code clean
if(MSVC)
    target_compile_options(physics_sim PRIVATE /W4)
else()
    target_compile_options(physics_sim PRIVATE -Wall -Wextra -Wpedantic)
endif()
