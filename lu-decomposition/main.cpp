/*
 *  Main.cpp
 *
 *  LU decomposition
 *
 *  Student ID: xxxx-xx-xxxx
 *  Name: Kim Yongi
 *  May 10, 2021
 */

#include <cstdio>
#include <iostream>

const int N_ROW = 3;
const int N_COL = 3;

// A = LU
double A[N_ROW][N_COL] = {};
double L[N_ROW][N_COL] = {};

void inputMatrix(double X[][N_COL]);
void printMatrix(double X[][N_COL]);

int main() {
  // Input matrix A from the standard input
  inputMatrix(A);

  for (int i = 0; i < N_ROW; i++) {
    // Substitute components to L
    for (int j = i; j < N_ROW; j++) {
      L[j][i] = A[j][i];
    }

    // Gauss Elimination
    double a = A[i][i];
    for (int n = 0; n < N_COL; n++) {
      A[i][n] /= a;
    }
    for (int j = i + 1; j < N_ROW; j++) {
      double ap = A[j][i];
      for (int n = i; n < N_COL; n++) {
        A[j][n] -= ap * A[i][n];
      }
    }
  }

  // Print answers
  printMatrix(L);
  printMatrix(A); // Matrix U of A = LU
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
