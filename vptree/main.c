#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vptree.h"

#define IDX(d, i, k)  i*d + k

void fun (vptree* T) {

  if(T == NULL) {
    return ;
  }

  printf("idx: %d, md: %f\n", T->idx, T->md);

  fun(T->inner);
  fun(T->outer);

}

int main () {

  FILE *in = fopen("data.in", "r");

  int n , d;

  fscanf(in, "%d %d", &n, &d);

  double X[n*d];

  for (int i = 0; i < n; i++) {
    for (int k = 0; k < d; k++) {
      double y;
      fscanf(in, "%lf", &y);
      X[IDX(d,i,k)] = y;
      printf("%f ", y);
    }
    printf("\n");
  }
  printf("\n");

  vptree* T = buildvp(X,n,d);

  fun(T);

  return 0;

}
