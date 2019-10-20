#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vptree.h"

int main () {

  srand(time(NULL));

  int N = 10;
  int d = 2;

  double* A = malloc(N * d * sizeof(double));

  for (int i = 0; i < N*d; i++) {
    A[i] = ( (double) (rand() % 100) ) / ((double) (rand() % 10 +1));
  }
  for (int i = 0; i < N; i++) {
    printf("(");
    for (int k = 0; k < d-1; k++) {
      printf("%.1f, ", A[i*d+k-1]);
    }
    printf("%.1f)\n", A[i*d+d-1-1]);
  }
  printf("\n");

  vptree* T = buildvp(A, N, d);

  T = NULL;

  return 0;
}
