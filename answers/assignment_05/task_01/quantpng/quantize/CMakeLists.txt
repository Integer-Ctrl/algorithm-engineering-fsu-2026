cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(quantize LANGUAGES C)

# search for OpenMP, REQUIRED -> fatal error if not found
find_package(OpenMP REQUIRED)

# add a library to the project using the specified source files
add_library(quantize STATIC
    blur.c blur.h
    kmeans.c kmeans.h
    libimagequant.c libimagequant.h
    mediancut.c mediancut.h
    mempool.c mempool.h
    nearest.c nearest.h
    pam.c pam.h
)

# link to the imported target provided by the FindOpenMP module
target_link_libraries(quantize PUBLIC OpenMP::OpenMP_C)

# PUBLIC -> targets that link to this target get that include directory
target_include_directories(quantize PUBLIC ./)