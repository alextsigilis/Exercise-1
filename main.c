#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vptree.h"

#define IDX(d,i,k)  d*i + k

void print_tree (vptree *T, int tabs );

int main (int argc, char** argv) {

	srand(time(NULL));

	int n = atoi(argv[1]), d = atoi(argv[2]);
	double *X = malloc(n*d*sizeof(double));
	for (int i = 0; i < n; i++) {
    for (int k = 0; k < d; k++) {
			double y = (double)(rand()%100);
			printf("%f ", y);
			X[IDX(d,i,k)] = y;
    }printf(";\n");
  }

	vptree *T = buildvp(X,n,d);

	print_tree(T,0);

	return 0;

}


void print_tree (vptree *T, int tabs) {
	if (T == NULL)
		return;
	for(int i = 0; i < tabs; i++){printf("\t");}
	printf("Index: %d, Median: %f\n", T->idx, T->md);
	print_tree(T->inner, tabs+1);
	print_tree(T->outer, tabs+1);
}
