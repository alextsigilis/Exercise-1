#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vptree.h"

#define IDX(d,i,k)  d*i + k

void fun(vptree *T) {

	if(T==NULL){
		printf("NULL\n");
		return;
	}
	printf("IDX: %d, Med.= %f\n", T->idx, T->md);

	fun(T->inner);
	fun(T->outer);
}

int main (int argc, char** argv) {

	FILE* fin = fopen("data.in", "r");
	
	int n,d;

	n = atoi(argv[1]);
	d = atoi(argv[2]);

	double *X = malloc(n*d*sizeof(double));

  for (int i = 0; i < n; i++) {
    for (int k = 0; k < d; k++) {
			double y = (double) (rand()%100);
			X[IDX(d,i,k)] = y;
    }
  }

	//printf("Start Proccessing\n");
	//time_t t1 = time(NULL);
	buildvp(X,n,d);
	//time_t t2 = time(NULL);
	//printf("It took %f seconds.\n", difftime(t2,t1));

	return 0;

}
