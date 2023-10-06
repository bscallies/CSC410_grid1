cmake_minimum_required(VERSION 3.24)  # Use your CLion's supported CMake version
project(CSC410_grid1)                  # Name of your project

set(CMAKE_C_STANDARD 99)              # Set C Standard

# List your source files here
set(SOURCE_FILES main.c grid.c checker.c parallel.c)

add_executable(CSC410_grid1 ${SOURCE_FILES})  # Name of your executable and source files
include_directories(${CMAKE_CURRENT_SOURCE_DIR})