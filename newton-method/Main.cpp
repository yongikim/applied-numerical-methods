/*
 *  Main.cpp
 *
 *  Newton method
 *
 *  Student ID: xxxx-xx-xxxx
 *  Name: Kim Yongi
 *  Apr 19, 2021
 */

#include <iomanip>
#include <iostream>
#include <math.h>

double f(double x) { return exp(x) - 2.0 + x * x; }

double df(double x) { return exp(x) + 2.0 * x; }

int main() {
  double x, y;
  double next_x;

  std::cin >> x;

  next_x = x - f(x) / df(x);
  while (fabs(f(next_x)) >= 1e-12 && fabs(next_x - x) >= 1e-12) {
    x = next_x;
    next_x = x - f(x) / df(x);
  }

  std::cout << std::fixed << std::setprecision(6) << x << std::endl;
}
