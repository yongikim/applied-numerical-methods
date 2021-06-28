/*
 *  Main.cpp
 *
 *  Central Difference
 *  d^2 u / dt^2 = c^2 d^2 u / dx^2
 *
 *  Student ID: xxxx-xx-xxxx
 *  Name: Kim Yongi
 *  Jun 21, 2021
 */

#include <cmath>
#include <iomanip>
#include <iostream>

struct _node {
    double z;   // at time t
    double zm;  // at time t - dt
    double zp;  // at time t + dt
};

const int N = 8;

_node node[N + 1]{};

const double dx = 2.0 / (double)N;  // dx = h
const double dt = 0.0625;           // dt = k

double c;
double cr2;

double u(double x) { return 0.05 * x * (2 - x); }

void boundNode() {
    node[0].z = 0;
    node[N].z = 0;
}

void initNode() {
    for (int i = 0; i <= N; i++) {
        double x = (double)i * dx;
        node[i].z = u(x);
    }
    (void)boundNode();

    for (int i = 1; i < N; i++) {
        node[i].zm =
            cr2 * (node[i + 1].z + node[i - 1].z) + 2. * (1. - cr2) * node[i].z;
        node[i].zm *= 0.5;
    }
}

void timeEvolve() {
    for (int i = 1; i < N; i++) {
        node[i].zp = cr2 * (node[i + 1].z + node[i - 1].z) - node[i].zm +
                     2. * (1. - cr2) * node[i].z;
    }
    for (int i = 1; i < N; i++) {
        node[i].zm = node[i].z;
        node[i].z = node[i].zp;
    }
}

int main() {
    std::cin >> c;
    cr2 = c * c * (dt / dx) * (dt / dx);

    (void)initNode();
    for (int j = 1; j <= 10; j++) {
        (void)timeEvolve();
    }
    for (int i = 0; i <= N; i++) {
        printf("%.15f\n", node[i].z);
    }
}
