#include <iostream>
#include <math.h>

double f(double x);
bool isEnd(double a, double b);

int main() {
  // ends of region [a, b]
  double a, b;

  // midpoint of [a, b]
  double c;

  std::cin >> a >> b;

  // bisection  method
  while (!isEnd(a, b)) {
    c = (a + b) / 2;

    if (f(a) * f(c) > 0) {
      a = c;
    } else {
      b = c;
    }
  }

  std::cout << c << std::endl;
}

// function f(x) in equation f(x) = 0
double f(double x) { return x * x * x - 3.0 * x * x + 9.0 * x - 8.0; }

// exit condition for bisection method
bool isEnd(double a, double b) { return fabs(a - b) < 1e-6; }
