# Minimum CMake version requirement
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(FirstSDLProject LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(src/include)
include_directories(src/include/headers)

# Link directories
link_directories(src/lib)

# Source files
file(GLOB SOURCES "src/cpp/*.cpp")

# Executable target
add_executable(main ${SOURCES})

# Link libraries
target_link_libraries(main mingw32 SDL2main SDL2 SDL2_image SDL2_ttf)
