#include "gaussian_elimination1.h"

void print_mat(float a[N][N]){
  int i,j;
  for(i=0; i<N; ++i){
    printf("  [");
    for(j=0; j<N; ++j){
      printf("%5g", a[i][j]);
      if (j != N-1) printf(", ");
    }
    printf("]\n");
  }
}

void gaussian_elem(float a[N][N], float a_inv[N][N]){
  float a_tmp[N][N], scale;
  int i, j, k;

  for(i=0; i<N; ++i) {
    for(j=0; j<N; ++j) {
      a_tmp[i][j] = a[i][j];
      a_inv[i][j] = (i == j) ? 1.0 : 0.0;
    }
  }

  for (i=0; i<N; i++){
    scale = 1.0 / a_tmp[i][i];
    for (j = 0; j< N; j++){
      a_tmp[i][j] *= scale;
      a_inv[i][j] *= scale;
    }
    for(k = 0; k<N; k++){
      if (k == i)
        continue;
      scale = a_tmp[k][i];
      for (j=0; j<N; ++j){
        a_tmp[k][j] -= scale*a_tmp[i][j];
        a_inv[k][j] -= scale*a_inv[i][j];
      }
    }
  }//END OF 2nd FOR LOOP
} // END OF FUNCTION

void mat_mult(float a[N][N], float b[N][N], float c[N][N]){
  int i, j, k;
  for (i=0; i<N; ++i){
    for (j=0; j<N; ++j){
      c[i][j] = 0.0;
    }
  }
  for(i=0; i<N; ++i){
    for(j=0; j<N; ++j){
      for(k=0; k<N; ++k){
        c[i][j] += a[i][k]*b[k][j];
      }
    }
  }
}
