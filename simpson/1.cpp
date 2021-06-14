/*
 *  Main.cpp
 *
 *  Simpson 1
 *
 *  Student ID: xxxx-xx-xxxx
 *  Name: Kim Yongi
 *  Jun 5, 2021
 */

#include <functional>
#include <iomanip>
#include <iostream>

// function to integrate
double func(double);
// simpson method
double simpson_integrate(std::function<double(double)>, double, double);

double X_LEFT = 0.0;
double X_RIGHT = 1.0;
int N = 1024;

int main() {
  std::cout << std::fixed << std::setprecision(10)
            << simpson_integrate(func, X_LEFT, X_RIGHT) << std::endl;
}

double func(double x) { return 1.0 / (1.0 + x * x); }

double simpson_integrate(std::function<double(double)> fn, double from,
                         double to) {
  double h = (to - from) / N;
  double sum_1 = 0.0;
  double sum_2 = 0.0;

  for (int i = 1; i <= N / 2 - 1; i++) {
    sum_1 += fn(from + 2.0 * i * h);
  }

  for (int i = 1; i <= N / 2; i++) {
    sum_2 += fn(from + (2.0 * i - 1.0) * h);
  }

  return h / 3.0 * (fn(from) + fn(to) + 2.0 * sum_1 + 4.0 * sum_2);
}
