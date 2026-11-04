#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

// Random number generator from example 3.5
double rnd (unsigned int * seed) {
  *seed = (1140671485 * (* seed) + 12820163) % (1 << 24);
  return ((double)(*seed)) / (1 << 24);
}

int main() {
  unsigned int seed = 0;

  int n = 100000000; // number of points to generate
  int counter = 0; // counter for points lying in the first quadrant of a unit circle
  auto start_time = omp_get_wtime(); // omp_get_wtime() is an OpenMP library routine

  // compute n points and test if they lie within the first quadrant of a unit circle
#pragma omp parallel 
    {
      int num_threads = omp_get_num_threads();
      int thread_id = omp_get_thread_num();
      unsigned int thread_seed = thread_id; // each thread has its own seed for random number generation

# pragma omp parallel for reduction(+:counter)
      for (int i = thread_id; i < n; i += num_threads) {
        auto x = rnd(&thread_seed); // generate random number between 0.0 and 1.0
        auto y = rnd(&thread_seed); // generate random number between 0.0 and 1.0
        if (x * x + y * y <= 1.0) { // if the point lies in the first quadrant of a unit circle
          ++counter;
        }
      }
    }

  auto run_time = omp_get_wtime() - start_time;
  auto pi = 4 * (double(counter) / n);

  cout << "pi: " << pi << endl;
  cout << "run_time: " << run_time << " s" << endl;
  cout << "n: " << n << endl; }
