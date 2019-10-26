#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vptree.h"

#define IDX(d,i,k)  d*i + k

typedef struct {
	vptree **buffer;
	int n;
	int head;
	int tail;
	int empty;
	int full;
} Queue;
Queue *init(int n) {
	Queue *q = malloc(sizeof(Queue));
	q->buffer = malloc(n*sizeof(vptree*));
	q->head = 0;
	q->tail = 0;
	q->empty = 1;
	q->full = 0;
	return q;
}
int enqueue(Queue *q, vptree *T) {
	if(q->full) {
		return -1;
	}
	q->buffer[q->tail] = T;
	q->tail += 1;
	q->full = (q->tail == q->n);
	return 0;
}
vptree *dequeue(Queue *q){
	if(q->empty) {return NULL;}
	vptree *ret = q->buffer[(q->head)-1];
	q->head += 1;
	q->empty = (q->head == q->tail);
	return ret;

}
void delete(Queue *q) {
	free(q);
}

void time_execution (double *X, int n, int d);

void print_tree (vptree *T, int tabs );

int main (int argc, char** argv) {

	FILE *fin = fopen("data.in", "r");
	int n = atoi(argv[1]), d = atoi(argv[2]);
	double *X = malloc(n*d*sizeof(double));
	for (int i = 0; i < n; i++) {
    for (int k = 0; k < d; k++) {
			double y = (double)(i*k)/10;
			fscanf(fin, "%lf", &y);
			X[IDX(d,i,k)] = y;
    }
  }

	vptree *T = buildvp(X,n,d);

	print_tree(T,0);

	return 0;

}


void time_execution (double *X, int n, int d) {

	FILE *fout = fopen("data.out", "w'");
	int N[60];
	double T[60];
	int k = 0, i = 1;
	for(int i = 10; i < n; i *= 10) {
		for(int j = 1; j < 11; j++){
			N[k] = i*j;
			k++;
		}
	}

	time_t t1,t2;
	for(int i = 0; i < 50; i++) {
		printf("...%d\n", N[i]);
		t1 = time(NULL);
		buildvp(X,N[i],d);
		t2 = time(NULL);
		T[i] = t2-t1;
	}

	for(int i = 0; i < 50; i++) {
		fprintf(fout, "%d %f\n", N[i], T[i]);
	}

}


void print_tree (vptree *T, int tabs ) {
	if (T == NULL)
		return;
	for(int i = 0; i < tabs; i++){printf("\t");}
	printf("Index: %d, Median: %f\n", T->idx, T->md);
	print_tree(T->inner, tabs+1);
	print_tree(T->outer, tabs+1);
}
