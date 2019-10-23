//
//
// WITH POINTS
//
//

#include <stdlib.h>
#include <math.h>
#include <assert.h>

#include <stdio.h>

#include "vptree.h"

#define IDX(d, i, k)  i*d + k

typedef struct {
	int d;
	double *coordiantes;
	int idx;
} point;

double distance (point *a, point *b) {

	int d = a->d;

	double x = 0;

	for(int k = 0; k < d; k++) {
		x += pow( a->coordiantes[k] - b->coordiantes[k] , 2);
	}

	x = sqrt(x);

	return x;

}

point *quickSelect (point **A, point *vp, int n, int k) {
	int start = 0;
	int end = n;

	while (start != end) {

		//
		// PARTITION
		//
		point *pivot = A[end-1];

		int i = start-1;

		for (int j = start; j < end-1; j++) {
			if ( distance(A[j],vp) <= distance(pivot,vp) ) {
				i++;
				point *tmp = A[j];
				A[j] = A[i];
				A[i] = tmp;
			}
		}

		point *tmp = A[i+1];
		A[i+1] = A[end-1];
		A[end-1] = tmp;
		i++;

		//
		// SELECT
		//
		if (i == k) {
			return A[i];
		}
		else if (i < k){
			start = i+1;
		}
		else {
			end = i;
		}
	}

	return A[start];
}

double findMedian (point **A, point *vp, int n) {

	if (n%2 != 0){ // n is odd
		point *p = quickSelect(A, vp, n, n/2);

		return distance(p, vp);
	}
	else {
		point *p1, *p2;

		p1 = quickSelect(A,vp,n,n/2);
		//p2 = quickSelect(A,vp,n,n/2-1);

		double d1 = distance(p1, vp);
		double d2 = distance(p1, vp);

		return (d1+d2)/2;
	}

}

vptree * vpt (point **A, int n) {

	vptree *T = malloc(sizeof(vptree));

	if(n == 0) {
		return NULL;
	}

	point *vp = A[n-1];

	T->vp = A[n-1]->coordiantes;
	T->idx = A[n-1]->idx;

	if(n==1) {
		T->md = 0;
		T->inner = NULL;
		T->outer = NULL;
		return T;
	}

	T->md = findMedian(A, vp, n-1);


	int n_inner, n_outer;

	n_inner = ceil((((double)(n)) - 1) / 2 );
	n_outer = floor( (((double)(n)) - 1) / 2  );

	T->inner = vpt(A, n_inner);
	T->outer = vpt(A+n_inner, n_outer);

	return T;

}

vptree * buildvp (double *X, int n, int d) {

	vptree *T;

	point **A = malloc(n*sizeof(point*));

	for(int p=0; p < n; p++) {
		A[p] = malloc(sizeof(point));
		A[p]->idx = p;
		A[p]->d = d;
		A[p]->coordiantes = X + IDX(d,p,0);

	}

	T = vpt(A, n);

	return T;

}

vptree * getInner (vptree * T) {
	return T->inner;
}

vptree * getOuter (vptree * T) {
	return T->outer;
}

double  getMD (vptree * T) {
	return T->md;
}

double * getVP (vptree * T) {
	return T->vp;
}

int getIDX (vptree * T) {
	return T->idx;
}
