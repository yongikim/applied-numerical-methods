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
#include <math.h>

double DT[] = {1.0e-1, 5.0e-2, 2.5e-2, 1.25e-2, 6.25e-3};

void func(double x[], double f[]);
void rk4(double x[], size_t x_size, double dt);

int main() {
  /* FILE *fp = fopen("data.txt", "w"); */

  size_t dt_size = sizeof(DT) / sizeof(DT[0]);
  double data_points[dt_size][2];

  // Solve equation and calculate error for each Δt
  for (int i = 0; i < dt_size; i++) {
    // Solve equation
    double dt = DT[i];
    double x[] = {1, 0};
    size_t x_size = sizeof(x) / sizeof(x[0]);
    for (int n = 0; n * dt < 10; n++) {
      rk4(x, x_size, dt);
    }

    // Calculate error
    double analytical_x = cos(10);
    double error = abs(x[0] - analytical_x);
    data_points[i][0] = dt;
    data_points[i][1] = error;
  }

  // Least squares
  int n_terms = 2;
  double G[dt_size][n_terms];
  for (int i = 0; i < dt_size; i++) {
    G[i][0] = 1;
    G[i][1] = log(DT[i]);
  }

  double A[n_terms][n_terms];
  for (int i = 0; i < n_terms; i++) {
    for (int k = 0; k < n_terms; k++) {
      A[i][k] = 0;
      for (int j = 0; j < dt_size; j++) {
        A[i][k] += G[j][i] * G[j][k];
      }
    }
  }

  double b[n_terms];
  for (int i = 0; i < n_terms; i++) {
    b[i] = 0;
    for (int j = 0; j < dt_size; j++) {
      b[i] += G[j][i] * log(data_points[j][1]);
    }
  }

  // LU_Decomposition
  // Copy A to U
  double U[n_terms][n_terms];
  double L[n_terms][n_terms];
  for (int i = 0; i < n_terms; i++) {
    for (int j = 0; j < n_terms; j++) {
      U[i][j] = A[i][j];
    }
  }

  for (int i = 0; i < n_terms; i++) {
    // Substitute components to L
    for (int j = i; j < n_terms; j++) {
      L[j][i] = U[j][i];
    }

    // Gauss Elimination
    double p = U[i][i];
    for (int n = 0; n < n_terms; n++) {
      U[i][n] /= p;
    }
    for (int j = i + 1; j < n_terms; j++) {
      double ap = U[j][i];
      for (int n = i; n < n_terms; n++) {
        U[j][n] -= ap * U[i][n];
      }
    }
  }

  // Solve LUa = b. c = Ua => Lc = b
  // Solve Lc = b for c
  double c[n_terms];
  for (int i = 0; i < n_terms; i++) {
    double sum = 0.;
    for (int j = 0; j < i; j++) {
      sum += L[i][j] * c[j];
    }
    c[i] = (b[i] - sum) / L[i][i];
  }
  // solve Ua = c for a
  double a[n_terms];
  for (int i = n_terms - 1; i >= 0; i--) {
    double sum = 0.;
    for (int j = i + 1; j < n_terms; j++) {
      sum += U[i][j] * a[j];
    }
    a[i] = c[i] - sum;
  }

  /* for (int i = 0; i < dt_size; i++) { */
  /*   fprintf(fp, "%g, %g, %g\n", data_points[i][0], log(data_points[i][1]),
   */
  /*           a[0] + a[1] * log(data_points[i][0])); */
  /* } */

  /* fclose(fp); */

  std::cout << std::fixed << std::setprecision(16) << a[1] << std::endl;
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
