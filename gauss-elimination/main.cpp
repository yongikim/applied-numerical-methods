/*
 *  Main.cpp
 *
 *  Gauss Elimination
 *
 *  Student ID: xxxx-xx-xxxx
 *  Name: Kim Yongi
 *  Apr 26, 2021
 */

#include <cmath>
#include <iomanip>
#include <iostream>

void printVector(double x[3]);
void printMatrix(double a[3][3]);
void swapRows(double a[3][3], double b[3], int i);

int main() {
  // ax = b
  double a[3][3];
  double b[3];
  double x[4] = {0};

  // pivot
  double p;

  // Read a and b
  for (int i = 0; i < 3; i++) {
    std::cin >> a[i][0] >> a[i][1] >> a[i][2] >> b[i];
  }

  // Forward elimination
  for (int i = 0; i < 3; i++) {
    for (int j = i + 1; j < 3; j++) {
      swapRows(a, b, i);

      p = a[j][i] / a[i][i];
      for (int k = i; k < 3; k++) {
        a[j][k] -= a[i][k] * p;
      }
      b[j] -= b[i] * p;
    }
  }

  // printMatrix(a);

  // Backward substitution
  for (int i = 2; i >= 0; i--) {
    p = a[i][i];
    x[i] = b[i] / p;
    for (int j = i + 1; j < 3; j++) {
      x[i] -= a[i][j] / p * x[j];
    }
  }

  // Answer
  printVector(x);
}

// Print vector
void printVector(double x[3]) {
  printf("%lf\n", x[0]);
  printf("%lf\n", x[1]);
  printf("%lf\n", x[2]);
}

// Print matrix
void printMatrix(double a[3][3]) {
  printf("%lf %lf %lf\n", a[0][0], a[0][1], a[0][2]);
  printf("%lf %lf %lf\n", a[1][0], a[1][1], a[1][2]);
  printf("%lf %lf %lf\n", a[2][0], a[2][1], a[2][2]);
}

// Swap rows of a and b so that always the biggest pivot is used
void swapRows(double a[3][3], double b[3], int i) {
  double e = 1e-12;
  double tmp, m;

  for (int n = i + 1; n < 3; n++) {
    if (fabs(a[i][i]) < fabs(a[n][i])) {
      tmp = b[i];
      b[i] = b[n];
      b[n] = tmp;

      for (int j = 0; j < 3; j++) {
        tmp = a[i][j];
        a[i][j] = a[n][j];
        a[n][j] = tmp;
      }
    }

    if (fabs(a[i][i]) < e) {
      printf("Error: No answer exists");
      exit(1);
    }
  }
};
