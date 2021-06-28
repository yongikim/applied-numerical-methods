/*
 *  Main.cpp
 *
 *   Clank-Nicolson
 *
 *  Student ID: xxxx-xx-xxxx
 *  Name: Kim Yongi
 *  Jun 28, 2021
 */

#include <iostream>
#include <iomanip>
#include <cmath>

/* 
 *  du / dt = c * d^2 u / dx^2
 */

const int N = 10;
double p, q, r;

struct _node
{
  double z;  // at time t
  double pz; // at time d+dt
};

_node node[N + 1]{};

void boundaryNode()
{
  node[0].z = 0;
  node[0].pz = 0;

  node[N].z = 1;
  node[N].pz = 1;
}

void updateNode()
{
  for (int i = 1; i < N; i++)
  {
    node[i].z = node[i].pz;
  }
}

void gaussSeidel()
{
  double tol = 1.;

  while (tol > 1e-15)
  {
    tol = 0.;
    for (int i = 1; i < N; i++)
    {
      double pz = node[i].pz;

      // Right hand
      double first = q * node[i].z - node[i + 1].z - node[i - 1].z;
      // Left hand
      double second = node[i - 1].pz + node[i + 1].pz;
      // Solve for z(x,t+dt)
      node[i].pz = (second - first) / p;

      double tmp_tol = fabs(node[i].pz - pz);
      if (tmp_tol > tol)
      {
        tol = tmp_tol;
      }
    }
  }
}

void printNode()
{
  for (int i = 0; i <= N; i++)
  {
    printf("%.15f\n", node[i].z);
  }
}

int main()
{
  double c;
  double dx = 1. / (double)N;
  double dt = 1e-2;

  std::cin >> c;

  r = c * dt / (dx * dx);
  double ir = dx * dx / (c * dt);

  p = 2.0 * (1. + ir);
  q = 2.0 * (1 - ir);

  for (int i = 0; i < 10; i++)
  {
    boundaryNode();
    gaussSeidel();
    updateNode();
  }

  printNode();
}
