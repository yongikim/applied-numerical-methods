/*
 *  Main.cpp
 *
 *  Runge-Kutta method
 *
 *  Student ID: xxxx-xx-xxxx
 *  Name: Kim Yongi
 *  Jun 14, 2021
 */

#include <cmath>
#include <iomanip>
#include <iostream>

double DT[] = {1e-1, 5e-2, 2.5e-2, 1.25e-2, 6.25e-3};

void func(double x[], double f[]);
void rk4(double x[], size_t x_size, double dt);

int main() {
  size_t dt_size = sizeof(DT) / sizeof(DT[0]);
  for (int i = 0; i < dt_size; i++) {
    double dt = DT[i];
    double x[] = {1, 0};
    size_t x_size = sizeof(x) / sizeof(x[0]);
    for (int n = 0; n * dt < 10; n++) {
      rk4(x, x_size, dt);
    }
    double analytical_x = cos(10);
    double error = abs(x[0] - analytical_x);
    std::cout << std::fixed << std::setprecision(15) << error << std::endl;
  }
}

void func(double x[], double f[]) {
  double dxdt = x[1];
  double dydt = -x[0];

  f[0] = dxdt;
  f[1] = dydt;
};

void rk4(double x[], size_t x_size, double dt) {
  double y[x_size];
  double k[4][x_size];

  func(x, k[0]);
  for (int i = 0; i < x_size; i++) {
    y[i] = x[i] + k[0][i] * dt / 2;
  }
  func(y, k[1]);
  for (int i = 0; i < x_size; i++) {
    y[i] = x[i] + k[1][i] * dt / 2;
  }
  func(y, k[2]);
  for (int i = 0; i < x_size; i++) {
    y[i] = x[i] + k[2][i] * dt;
  }
  func(y, k[3]);

  for (int i = 0; i < x_size; i++) {
    x[i] = x[i] + (k[0][i] + 2 * k[1][i] + 2 * k[2][i] + k[3][i]) * dt / 6;
  }
}
