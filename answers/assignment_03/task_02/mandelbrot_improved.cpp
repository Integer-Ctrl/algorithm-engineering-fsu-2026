#include <complex>
#include <fstream>
#include <iostream>
#include <omp.h>
#include <vector>

using namespace std;

constexpr int width = 4000;
constexpr int height = width;

int compute_pixel(int x, int y) { // compute the gray value of a pixel
  complex<double> point(2.0 * x / width - 1.5, 2.0 * y / height - 1.0);
  complex<double> z(0, 0);
  constexpr int iterations = 100;
  int nb_iter = 0;
  // test if point in mandelbrot set
  while (abs(z) < 2 && nb_iter < iterations) {
    z = z * z + point;
    nb_iter++;
  }
  // white color (255) if point in mandelbrot set, else a shade of gray
  return (255 * nb_iter) / iterations;
}

int main() { // generate mandelbrot pgm (portable graymap)
  const string image_name = "mandelbrot_improved.pgm";
  remove(image_name.c_str()); // remove file from disk
  const double start = omp_get_wtime();

  // Improvement 1: create a look-up table for pixel values to avoid repeated string conversions
  vector<string> look_up{256};
#pragma omp for schedule(dynamic)
  for (int i = 0; i < 256; i++) {
    look_up[i] = to_string(i) + "\n";
  }
  ofstream image(image_name); // file output stream
  if (image.is_open()) {
    image << "P2\n" << width << " " << height << " 255\n"; // pgm header

    // Improvement 2: parallelize the pixel computation and
#pragma omp parallel
    {
      // use a string buffer for each thread to avoid conflicts
      string buffer; // each thread has its own string buffer
      buffer.reserve(width * 4); // reserve enough space to avoid reallocation

      // Improvement 3: parallelize the outer loop and use ordered directive to maintain the order of pixel values
#pragma omp for schedule(dynamic) ordered
      for (int i = 0; i < height; i++) {
        buffer.clear(); // clear the buffer for each row
        for (int j = 0; j < width; j++) {
          buffer += look_up[compute_pixel(j, i)]; // add pixel value to buffer
        }
#pragma omp ordered // ensure that the rows are written in order
        image << buffer; // write the buffer to the file
      }
    } // END #pragma omp parallel
    image.close(); // close file output stream
  } else {
    cout << "Could not open the file!";
  }
  cout << omp_get_wtime() - start << " seconds" << endl;
}
