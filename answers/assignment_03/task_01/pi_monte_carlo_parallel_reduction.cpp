#include <iostream>
#include <omp.h>
#include <random>

using namespace std;

int main() {
  unsigned int seed = 0;

  int n = 100000000; // number of points to generate
  int counter = 0; // counter for points lying in the first quadrant of a unit circle
  auto start_time = omp_get_wtime(); // omp_get_wtime() is an OpenMP library routine

  // compute n points and test if they lie within the first quadrant of a unit circle
#pragma omp parallel 
    {
      // Assign each thread its own random number generator
      int num_threads = omp_get_num_threads();
      int thread_id = omp_get_thread_num();

      default_random_engine thread_re{seed + thread_id}; // different seed for each thread
      uniform_real_distribution<double> thread_zero_to_one{0.0, 1.0};

# pragma omp parallel for reduction(+:counter)
      for (int i = thread_id; i < n; i += num_threads) {
        auto x = thread_zero_to_one(thread_re); // generate random number between 0.0 and 1.0
        auto y = thread_zero_to_one(thread_re); // generate random number between 0.0 and 1.0
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
