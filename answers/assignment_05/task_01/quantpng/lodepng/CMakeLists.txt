cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(lodepng LANGUAGES CXX)

# add a library to the project using the specified source files
add_library(lodepng STATIC
    lodepng.cpp lodepng.h
)

# PUBLIC -> targets that link to this target get that include directory
target_include_directories(lodepng PUBLIC ./)