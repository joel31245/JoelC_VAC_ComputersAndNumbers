#include "gaussian_elimination1.h"
#include <stdio.h>
#include <math.h>
#include "gaussian_elimination.c"

int main(){
  float a[N][N];
  float a_inv[N][N];
  float c[N][N];

  double e = 1*pow(10,-8);

  a[0][0] = 1.0;
  a[0][1] = e;
  a[1][0] = 1.0;
  a[1][1] = 1.0;

  gaussian_elem(a, a_inv);
  printf("A\n"); print_mat(a);
  printf("A_inv\n"); print_mat(a_inv);
  mat_mult(a, a_inv, c);
  printf("A*A_inv\n"); print_mat(c);

  return 0;
}
