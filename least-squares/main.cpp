/*
 *  Main.cpp
 *
 *  Least Squares
 *
 *  Student ID: xxxx-xx-xxxx
 *  Name: Kim Yongi
 *  May 24, 2021
 */

#include <cmath>
#include <iomanip>
#include <iostream>

// Total number of terms in f(x,y)
const int N_TERMS = 6;

int main() {
  // Total number of points
  int N;
  std::cin >> N;

  // Points
  double x[N];
  double y[N];
  double z[N];
  for (int i = 0; i < N; i++) {
    std::cin >> x[i] >> y[i] >> z[i];
  }

  double G[N][N_TERMS];
  for (int i = 0; i < N; i++) {
    G[i][0] = 1;
    G[i][1] = x[i];
    G[i][2] = y[i];
    G[i][3] = x[i] * y[i];
    G[i][4] = x[i] * x[i];
    G[i][5] = y[i] * y[i];
  }

  double A[N_TERMS][N_TERMS]{};
  for (int i = 0; i < N_TERMS; i++) {
    for (int k = 0; k < N_TERMS; k++) {
      for (int j = 0; j < N; j++) {
        A[i][k] += G[j][i] * G[j][k];
      }
    }
  }

  double b[N_TERMS]{};
  for (int i = 0; i < 6; i++) {
    for (int j = 0; j < N; j++) {
      b[i] += G[j][i] * z[j];
    }
  }

  // LU_Decomposition
  // Copy A to U
  double U[N_TERMS][N_TERMS]{};
  double L[N_TERMS][N_TERMS]{};
  for (int i = 0; i < N_TERMS; i++) {
    for (int j = 0; j < N_TERMS; j++) {
      U[i][j] = A[i][j];
    }
  }

  for (int i = 0; i < N_TERMS; i++) {
    // Substitute components to L
    for (int j = i; j < N_TERMS; j++) {
      L[j][i] = U[j][i];
    }

    // Gauss Elimination
    double p = U[i][i];
    for (int n = 0; n < N_TERMS; n++) {
      U[i][n] /= p;
    }
    for (int j = i + 1; j < N_TERMS; j++) {
      double ap = U[j][i];
      for (int n = i; n < N_TERMS; n++) {
        U[j][n] -= ap * U[i][n];
      }
    }
  }

  // Solve LUa = b. c = Ua => Lc = b
  // Solve Lc = b for c
  double c[N_TERMS]{};
  for (int i = 0; i < N_TERMS; i++) {
    double sum = 0.;
    for (int j = 0; j < i; j++) {
      sum += L[i][j] * c[j];
    }
    c[i] = (b[i] - sum) / L[i][i];
  }
  // solve Ua = c for a
  double a[N_TERMS]{};
  for (int i = N_TERMS - 1; i >= 0; i--) {
    double sum = 0.;
    for (int j = i + 1; j < N_TERMS; j++) {
      sum += U[i][j] * a[j];
    }
    a[i] = c[i] - sum;
  }

  for (int i = 0; i < N_TERMS; i++) {
    printf("%lf\n", a[i]);
  }
}
