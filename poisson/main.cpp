/*
 *  Main.cpp
 *
 *  Poisson equation
 *
 *  Student ID: xxxx-xx-xxxx
 *  Name: Kim Yongi
 *  Jul 5, 2021
 */

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

int N;
const double TOLERANCE = 1e-15;

struct _node
{
    double u;  // current u
    double pu; // next u
};

std::vector<_node> node;

void boundaryNode(std::vector<_node> n)
{
    _node ref_first = n.front();
    ref_first.u = 0;
    ref_first.pu = 0;

    _node ref_last = n.back();
    ref_last.u = 0;
    ref_last.pu = 0;
}

void updateNode()
{
    for (int i = 1; i < N; i++)
    {
        node[i].u = node[i].pu;
    }
}

double func(double x, double dx)
{
    if (-dx <= x && x <= dx)
    {
        return -1. / (dx * dx) * (dx - fabs(x));
    }
    else
    {
        return 0.;
    }
}

void gaussSeidel()
{
    double tol = 1;

    while (tol > TOLERANCE)
    {
        tol = 0;
        for (int i = 1; i < N; i++)
        {
            double pu = node[i].pu;

            double n = (double)N;
            double j = i - n / 2.;
            double x = 2. / n * j;
            double dx = 2. / n;

            node[i].pu = (-dx * dx * func(x, dx) + node[i + 1].pu + node[i - 1].pu) / 2.;

            double tmp_tol = fabs(node[i].pu - pu);
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
        printf("%.15f\n", node[i].u);
    }
}

int main()
{
    std::cin >> N;
    for (int i = 0; i < N + 1; i++)
    {
        _node n;
        n.u = 0;
        n.pu = 0;

        node.push_back(n);
    }

    boundaryNode(node);
    gaussSeidel();
    updateNode();

    printNode();
}
