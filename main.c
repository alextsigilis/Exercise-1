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

void print_tree (vptree *T, int tabs ) {
	if (T == NULL)
		return;
	for(int i = 0; i < tabs; i++){printf("\t");}
	printf("Index: %d, Median: %f\n", T->idx, T->md);
	print_tree(T->inner, tabs+1);
	print_tree(T->outer, tabs+1);
}

int main (int argc, char** argv) {

	//FILE* fin = fopen("data.in", "r");

	int n = atoi(argv[1]), d = atoi(argv[2]);

	double *X = malloc(n*d*sizeof(double));

  for (int i = 0; i < n; i++) {
    for (int k = 0; k < d; k++) {
			double y = (double)(rand()%10)/10;
			//fscanf(fin, "%lf", &y);
			X[IDX(d,i,k)] = y;
    }
  }


	time_t t1,t2;
	printf("Starting execution...\n");
	t1 = time(NULL);
	buildvp(X,n,d);
	t2 = time(NULL);
	printf("It took: %f seconds\n", difftime(t2,t1));

	return 0;

}
