# Exam Assignment 28.10.2026

## Task 1
> Read Chapter 3 titled Programming Multi-core and Shared Memory Multiprocessors Using OpenMP (pp. 47–78) in Introduction to Parallel Computing (Trobec et al., 2018)

### Task 1.1
> - When run with one thread per logical core, threads from Listing 3.1 display their numbers randomly, while those from Listing 3.2 show them in the same order. Explain why.

Both code snippets use the OpenMP directive `#pragma omp parallel` without specifying any explicit ordering for the execution of the threads. However, the difference between Listing 3.1 and Listing 3.2 is the execution time of the individual threads.

In Listing 3.1, each thread performs the same trivial operation, printing a simple message to the output. Therefore, the threads take approximately the same amount of time to execute, leading to a race condition who prints first. As result, the output can appear in any order.

In contrast, in Listing 3.2 each thread computes a fibonacci number, but a different one! Would all threads compute the same fibonacci number, the same race condition would occur as in Listing 3.1. But since each thread computes a different number, the execution times of the threads vary. Therefore, a thread with a lower ID will compute a smaller fibonaccy number and finish faster than a thread with a higher ID. As a result, the output of Listing 3.2 is displayed in the same order.

### Task 1.2
> - What do you think, does the code snippet in Listing 3.10 use the cores efficiently, why yes, why no. Consider also the variable size in your argumentation.

**Why yes**: The code snippet in Listing 3.10 has a high degree of parallelism, as both for-loops are parallelized using the `collapse(2)` clause. Another positive aspect is, that within each iteration, the performed operations need approximately the same amount of work and therefore time. So no thread will idle unnecessarily waiting for other threads to finish their iterations. Also, no synchronization is needed besides the implicit barrier and no race conditions exist. Pointer swapping is also good to avoid copying of data.

**Why no**: Within each while-loop, a parallel region is created and destroyed, which creates overhead. For large `size` variables, the overhead gets negligible, but for small `size` variables, the overhead can be significant, reducing the efficiency. Small `size` variables also have the disadvantage of not utilizing all cores efficiently, as the number of iterations may be smaller than the number of available threads and the performed operation is quite trivial.

### Task 1.3
> - From Lecture 1, take your parallelized version of pi_monte_carlo.cpp and modify it based on the insights from Example 3.5 on computing π using random shooting, particularly the random number generation method. Report the changes you do and their impact on performance.

Starting point is my parallelized version [pi_monte_carlo_parallel.cpp](task_01/pi_monte_carlo_parallel.cpp) from lecture 1.

Without further modifications I get the following performance on 10 threads:

```sh
$ g++ -fopenmp pi_monte_carlo_parallel.cpp -o pi_monte_carlo_parallel.exe  
$ OMP_NUM_THREADS=10 ./pi_monte_carlo_parallel.exe
pi: 3.14197
run_time: 2.00111 s
n: 100000000
```

My first refinement was to remove the `#pragma omp atomic` directive and instead of using a local counter (`local_counter`) for each thread, replacing it with a reduction clause on the `counter` variable. Therefore, I added `# pragma omp parallel for reduction(+:counter)` to the for-loop.

This simplifies the code but did not improve the performance, see [pi_monte_carlo_parallel_reduction.cpp](task_01/pi_monte_carlo_parallel_reduction.cpp) result:

```sh
$ g++ -fopenmp pi_monte_carlo_parallel_reduction.cpp -o pi_monte_carlo_parallel_reduction.exe
$ OMP_NUM_THREADS=10 ./pi_monte_carlo_parallel_reduction.exe 
pi: 0.314113
run_time: 1.99701 s
n: 100000000
```

Another refinement was to replace the `default_random_engine` and `uniform_real_distribution` that each thread used to generate random numbers, with the random number generator introduced in example 3.5:

```cpp
double rnd (unsigned int * seed) {
  *seed = (1140671485 * (* seed) + 12820163) % (1 << 24);
  return ((double)(*seed)) / (1 << 24);
}
```

Using the custom random number generator increased the performance significantly, see [pi_monte_carlo_parallel_reduction_rnd.cpp](task_01/pi_monte_carlo_parallel_reduction_rnd.cpp) result:

```sh
$ g++ -fopenmp pi_monte_carlo_parallel_reduction_rnd.cpp -o pi_monte_carlo_parallel_reduction_rnd.exe
$ OMP_NUM_THREADS=10 ./pi_monte_carlo_parallel_reduction_rnd.exe                                     
pi: 0.314128
run_time: 0.125803 s
n: 100000000
```

## Task 2 (optional)
> Do the coding warmup on slide 20. (optional)

### Task 2.1
> Parallelize the serial π program (pi_numerical_integration.cpp ) from the first lecture by adding only one extra line of code.

I added `#pragma omp parallel for reduction(+:sum)`.

Comparison of the serial [pi_numerical_integration.cpp](task_02/pi_numerical_integration.cpp) and parallel version [pi_numerical_integration_parallel.cpp](task_02/pi_numerical_integration_parallel.cpp) on 10 threads:

```sh
$ g++ -Ofast -std=c++11 -march=native -fopenmp pi_numerical_integration.cpp -o pi_numerical_integration.exe
$ ./pi_numerical_integration.exe                                                  
pi with 100000000 steps is 3.1415926535894241 in 0.0537626 seconds

$ g++ -Ofast -std=c++11 -march=native -fopenmp pi_numerical_integration_parallel.cpp -o pi_numerical_integration_parallel.exe
$ OMP_NUM_THREADS=10 ./pi_numerical_integration_parallel.exe                                                                 
pi with 100000000 steps is 3.1415926535897758 in 0.0283461 seconds
```

Speedup of around 2x.

### Task 2.2
> The program on page 21 generates and saves an image of the mandelbrot set. Reduce the runtime of the program without degrading the image quality.

Comparison of the serial [mandelbrot.cpp](task_02/mandelbrot.cpp) and improved version [mandelbrot_improved.cpp](task_02/mandelbrot_improved.cpp) on 10 threads:

```sh
$ g++ -Ofast -std=c++11 -march=native -fopenmp mandelbrot.cpp -o mandelbrot.exe                  
$ OMP_NUM_THREADS=10 ./mandelbrot.exe                                                            
1.61356 seconds

$ g++ -Ofast -std=c++11 -march=native -fopenmp mandelbrot_improved.cpp -o mandelbrot_improved.exe
$ OMP_NUM_THREADS=10 ./mandelbrot_improved.exe                                                   
0.335914 seconds
```

Speedup of around 5x.

Images generated by both programs are identical, see [mandelbrot.pgm](task_02/mandelbrot.pgm) and [mandelbrot_improved.pgm](task_02/mandelbrot_improved.pgm).