/*
 *  Main.cpp
 *
 *  Runge-Kutta method
 *
 *  Student ID: xxxx-xx-xxxx
 *  Name: Kim Yongi
 *  Jun 14, 2021
 */

#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

double DT = 0.1;

void func(double x[], double f[]);
void rk4(double x[], size_t x_size);

int main() {
  double x[] = {1, 0};
  size_t x_size = sizeof(x) / sizeof(x[0]);
  // FILE *fp = fopen("./x_hist.txt", "w");
  for (int n = 0; n * DT < 10; n++) {
    rk4(x, x_size);
    // fprintf(fp, "%lf, %lf, %lf\n", n * DT, x[0], x[1]);
  }
  std::cout << std::fixed << std::setprecision(15) << x[0] << std::endl;
  // fclose(fp);
}

void func(double x[], double f[]) {
  double dxdt = x[1];
  double dydt = -x[0];

  f[0] = dxdt;
  f[1] = dydt;
};

void rk4(double x[], size_t x_size) {
  double y[x_size];
  double k[4][x_size];

  func(x, k[0]);
  for (int i = 0; i < x_size; i++) {
    y[i] = x[i] + k[0][i] * DT / 2;
  }
  func(y, k[1]);
  for (int i = 0; i < x_size; i++) {
    y[i] = x[i] + k[1][i] * DT / 2;
  }
  func(y, k[2]);
  for (int i = 0; i < x_size; i++) {
    y[i] = x[i] + k[2][i] * DT;
  }
  func(y, k[3]);

  for (int i = 0; i < x_size; i++) {
    x[i] = x[i] + (k[0][i] + 2 * k[1][i] + 2 * k[2][i] + k[3][i]) * DT / 6;
  }
}
