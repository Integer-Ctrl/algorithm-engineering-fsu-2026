cmake_minimum_required(VERSION 3.9 FATAL_ERROR)
project(test_fizzbuzz LANGUAGES CXX)

# embed library fizzbuzz in project test_fizzbuzz
add_subdirectory(fizzbuzz)

# catch is a header only library for testing
# embed library catch in project test_fizzbuzz
add_subdirectory(catch)

# create executable with all tests
add_executable(fizzbuzz_tests catch_main.cpp catch_tests_fizzbuzz.cpp)

# link libraries fizzbuzz and catch to executable
target_link_libraries(fizzbuzz_tests PRIVATE fizzbuzz PRIVATE catch)