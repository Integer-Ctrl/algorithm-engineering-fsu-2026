cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(quantpng LANGUAGES CXX C)

# embed library lodepng in project quantpng
add_subdirectory(lodepng)

# embed library quantize in project quantpng
add_subdirectory(quantize)

# create executable with name pi
add_executable(quantpng main.cpp)

# lodepng already uses OpenMP, so no need to link OpenMP again to quantpng
target_link_libraries(quantpng PUBLIC lodepng quantize)