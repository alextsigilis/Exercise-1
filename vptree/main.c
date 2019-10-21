#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "vptree.h"

#define IDX(d, i, k)  i*d + k

typedef struct {
  vptree ** stream;
  int front, back;
} Queue;
Queue* init_queue (int n) {
  Queue *q = malloc( sizeof(Queue) );

  q->stream = malloc( n * sizeof(vptree*) );

  q->front = 0;
  q->back = 0;

  return q;

}
void free_queue (Queue* q) {
  free(q);
}
void enqueue (Queue* q, vptree* node) {

  q->stream[q->back] = node;
  q->back += 1;

}
vptree* dequeue (Queue* q) {
  int i = q->front;
  q->front += 1;
  return q->stream[i];
}
int empty (Queue* q) {
  int f = q->front, b = q->back;

  return (f == b) && ((f > 0) && (b > 0));
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
    }
  }

  vptree *T = buildvp(X,n,d);

  printf("%f\n", T->md);

  return 0;

}
