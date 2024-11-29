# Minimum CMake version requirement
cmake_minimum_required(VERSION 3.10)

# Project name and language
project(FirstSDLProject LANGUAGES CXX)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
#include_directories(src/include)
include_directories(src/include/headers)
include_directories(src/include/headers/interfaces)

# Link directories
#link_directories(src/lib)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_ttf REQUIRED)

# Find SDL2 and its extensions
#find_package(PkgConfig REQUIRED)
# Use pkg-config to find SDL2 and its components
# pkg_check_modules(SDL2 REQUIRED sdl2)
# pkg_check_modules(SDL2_IMAGE REQUIRED SDL2_image)
# pkg_check_modules(SDL_2_ttf REQUIRED SDL2_ttf)

# Include directories for SDL2
include_directories(${SDL2_INCLUDE_DIRS} /usr/include/SDL2)

# Source files
file(GLOB SOURCES "src/cpp/*.cpp")

# Executable target
add_executable(main ${SOURCES})

# Link libraries
#target_link_libraries(main mingw32 SDL2main SDL2 SDL2_image SDL2_ttf)
target_link_libraries(main ${SDL2_LIBRARIES} /usr/lib64/libSDL2_image.so /usr/lib64/libSDL2_ttf.so)
