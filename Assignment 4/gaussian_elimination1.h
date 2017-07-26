#ifndef GAUSSIAN_ELIMINATION1_H_INCLUDED
#define GAUSSIAN_ELIMINATION1_H_INCLUDED

#include <stdio.h>

#define N 2

void print_mat(float a[N][N]);
void gaussian_elem(float a[N][N], float a_inv[N][N]);
void mat_mult(float a[N][N], float b[N][N], float c[N][N]);

#endif // GAUSSIAN_ELIMINATION1_H_INCLUDED
