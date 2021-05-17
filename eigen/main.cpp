/*
 *  Main.cpp
 *
 *  minimum absolute value of eigen value and its eigen vector
 *  A: 3x3
 *
 *  Student ID: xxxx-xx-xxxx
 *  Name: Kim Yongi
 *  May 17, 2021
 */

#include <cmath>
#include <cstdio>

const int N_ROW = 3;
const int N_COL = 3;

// A = LU
double A[N_ROW][N_COL] = {};
double L[N_ROW][N_COL] = {};
double U[N_ROW][N_COL] = {};

// An attempt vector
// This will be the eigen value for the smallest absolute eigen value of A
double x[3]{};

void inputMatrix(double X[][N_COL]);
void printMatrix(double X[][N_COL]);
void luDecomp();
void applyInvA(double x[N_ROW]);
double eigenValue(double x[N_ROW]);

int main() {
  // Input matrix A from the standard input
  inputMatrix(A);

  // LU decomposition
  luDecomp();

  // Calculate eigen value and eigen vector
  double x[N_ROW]{};
  x[0] = 1.;
  double dev = 100;
  double ev;
  while (dev > 1e-12) {
    double tmp = ev;
    applyInvA(x);
    ev = eigenValue(x);
    dev = fabs(ev - tmp);
  }

  // Print answers
  printf("%lf\n", ev);
  if (x[0] < 0.) {
    for (int i = 0; i < N_ROW; i++) {
      x[i] *= -1.;
    }
  }
  for (int i = 0; i < N_ROW; i++) {
    printf("%lf\n", x[i]);
  }
}

void luDecomp() {
  // Copy A to U
  for (int i = 0; i < N_ROW; i++) {
    for (int j = 0; j < N_COL; j++) {
      U[i][j] = A[i][j];
    }
  }

  for (int i = 0; i < N_ROW; i++) {
    // Substitute components to L
    for (int j = i; j < N_ROW; j++) {
      L[j][i] = U[j][i];
    }

    // Gauss Elimination
    double a = U[i][i];
    for (int n = 0; n < N_COL; n++) {
      U[i][n] /= a;
    }
    for (int j = i + 1; j < N_ROW; j++) {
      double ap = U[j][i];
      for (int n = i; n < N_COL; n++) {
        U[j][n] -= ap * U[i][n];
      }
    }
  }
}

void applyInvA(double x[N_ROW]) {
  // LUx = x'
  // y = Ux
  // Ly = x'

  // solve Ly = x' for y
  double y[N_ROW]{};
  for (int i = 0; i < N_ROW; i++) {
    double sum = 0.;
    for (int j = 0; j < i; j++) {
      sum += L[i][j] * y[j];
    }
    y[i] = (x[i] - sum) / L[i][i];
  }

  // solve Ux = y for x
  double z[N_ROW]{};
  for (int i = N_ROW - 1; i >= 0; i--) {
    double sum = 0.;
    for (int j = i + 1; j < N_COL; j++) {
      sum += U[i][j] * z[j];
    }
    z[i] = y[i] - sum;
  }

  double norm{};
  for (int i = 0; i < N_ROW; i++) {
    norm += z[i] * z[i];
  }
  norm = sqrt(norm);
  for (int i = 0; i < N_ROW; i++) {
    x[i] = z[i] / norm;
  }
}

double eigenValue(double x[N_ROW]) {
  double y[N_ROW]{};
  // x^T Ax = ev

  // Ax
  for (int i = 0; i < N_ROW; i++) {
    for (int j = 0; j < N_COL; j++) {
      y[i] += A[i][j] * x[j];
    }
  }

  // ev (eigen value) = x^T Ax
  double ev{};
  for (int i = 0; i < N_ROW; i++) {
    ev += x[i] * y[i];
  }

  return ev;
}

// Input matrix from the standard input
void inputMatrix(double X[][N_COL]) {
  for (int i = 0; i < N_ROW; i++) {
    for (int j = 0; j < N_COL; j++) {
      scanf("%lf", &X[i][j]);
    }
  }
}

// Print matrix
void printMatrix(double X[][N_COL]) {
  for (int i = 0; i < N_ROW; i++) {
    for (int j = 0; j < N_COL; j++) {
      printf("%lf\n", X[i][j]);
    }
  }
}
