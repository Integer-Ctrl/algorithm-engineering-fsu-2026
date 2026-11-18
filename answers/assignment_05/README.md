# Exam Assignment 11.11.2026

## Task 1
> The program in quantpng.zip uses a Makefile for compilation. Add three CMakeLists.txt so that the program can be built with CMake. You can also restructure the code files by saving them in new subfolders. (see video for hints)

See project [task_01/quantpng](task_01/quantpng) including the three CMakeLists.txt files.

To keep the existing Makefile unchanged and working, I did not add `include` and `src` subdirectories

```sh
$ mkdir build
$ cd build 
$ cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_C_COMPILER=gcc -DCMAKE_BUILD_TYPE=Release ..
-- The CXX compiler identification is GNU 13.3.0
-- The C compiler identification is GNU 13.3.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/g++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Detecting C compiler ABI info
-- Detecting C compiler ABI info - done
-- Check for working C compiler: /usr/bin/gcc - skipped
-- Detecting C compile features
-- Detecting C compile features - done
-- Found OpenMP_C: -fopenmp (found version "4.5") 
-- Found OpenMP_CXX: -fopenmp (found version "4.5") 
-- Found OpenMP: TRUE (found version "4.5")  
-- Configuring done (0.6s)
-- Generating done (0.0s)
-- Build files have been written to: /home/fhofer/ddrive/dev/fsu/algorithm-engineering-fsu-2026/answers/assignment_05/task_01/quantpng/build
$ cmake --build . --parallel 8                                                       
[  8%] Building CXX object lodepng/CMakeFiles/lodepng.dir/lodepng.cpp.o
[ 16%] Building C object quantize/CMakeFiles/quantize.dir/blur.c.o
[ 25%] Building C object quantize/CMakeFiles/quantize.dir/kmeans.c.o
[ 33%] Building C object quantize/CMakeFiles/quantize.dir/libimagequant.c.o
[ 41%] Building C object quantize/CMakeFiles/quantize.dir/nearest.c.o
[ 50%] Building C object quantize/CMakeFiles/quantize.dir/mediancut.c.o
[ 66%] Building C object quantize/CMakeFiles/quantize.dir/mempool.c.o
[ 66%] Building C object quantize/CMakeFiles/quantize.dir/pam.c.o
[ 75%] Linking C static library libquantize.a
[ 75%] Built target quantize
[ 83%] Linking CXX static library liblodepng.a
[ 83%] Built target lodepng
[ 91%] Building CXX object CMakeFiles/quantpng.dir/main.cpp.o
[100%] Linking CXX executable quantpng
[100%] Built target quantpng
$ ./quantpng ../pluto.png                                                            
Written quantized_example.png
```

## Task 2
> Create a static library that computes fizzbuzz. Test this static library using Catch2. See [here](https://mariusbancila.ro/blog/2018/03/29/writing-cpp-unit-tests-with-catch2/) for sample code for the fizzbuzz function and test cases. (see video for hints)

See project [task_02/test_fizzbuzz](task_02/test_fizzbuzz).

Test cases where taken from [Marius Bancila's Blog | Writing C++ unit tests with Catch2](https://mariusbancila.ro/blog/2018/03/29/writing-cpp-unit-tests-with-catch2/)

```sh
$ mkdir build 
$ cd build
$ cmake -DCMAKE_CXX_COMPILER=g++ -DCMAKE_BUILD_TYPE=Release ..
-- The CXX compiler identification is GNU 13.3.0
-- Detecting CXX compiler ABI info
-- Detecting CXX compiler ABI info - done
-- Check for working CXX compiler: /usr/bin/g++ - skipped
-- Detecting CXX compile features
-- Detecting CXX compile features - done
-- Configuring done (0.2s)
-- Generating done (0.0s)
-- Build files have been written to: /home/fhofer/ddrive/dev/fsu/algorithm-engineering-fsu-2026/answers/assignment_05/task_02/test_fizzbuzz/build
$ cmake --build . --parallel 8                                
[ 20%] Building CXX object fizzbuzz/CMakeFiles/fizzbuzz.dir/src/fizzbuzz.cpp.o
[ 40%] Linking CXX static library libfizzbuzz.a
[ 40%] Built target fizzbuzz
[ 60%] Building CXX object CMakeFiles/fizzbuzz_tests.dir/catch_main.cpp.o
[ 80%] Building CXX object CMakeFiles/fizzbuzz_tests.dir/catch_tests_fizzbuzz.cpp.o
[100%] Linking CXX executable fizzbuzz_tests
[100%] Built target fizzbuzz_tests
$ ./fizzbuzz_tests 
===============================================================================
All tests passed (68 assertions in 3 test cases)
```

All tests passed successfully.