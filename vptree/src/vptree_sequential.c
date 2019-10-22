#include <stdlib.h>
#include <math.h>
#include "vptree.h"

#define IDX(i, k)  i*d + k

double quickSelect (double *A, int n, int k) {
	int start = 0;
	int end = n;

	while (start != end) {

		//
		// PARTITION
		//
		double pivot = A[end-1];

		int i = start-1;

		for (int j = start; j < end-1; j++) {
			if (A[j] <= pivot) {
				i++;
				double tmp = A[j];
				A[j] = A[i];
				A[i] = tmp;
			}
		}

		double tmp = A[i+1];
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

double findMedian (double *A, int n) {

	int k1, k2;
	double m1, m2;
	if (n%2 == 0) { // If even
		k1 = n/2;
		k2 = n/2 - 1;
	}
	else{ // If odd
		k1 = n/2;
		k2 = n/2;
	}

	m1 = quickSelect(A, n, k1);
	m2 = quickSelect(A, n, k2);


	return (m1+m2)/2;


}

vptree * vpt (double *X, int* idx, int n, int d) {

	vptree *T = malloc(sizeof(vptree));

	if(n == 0) {
		return NULL;
	}

	else if(n==1) {
		T->md = 0;
		T->idx = idx[n-1];
		T->inner = NULL;
		T->outer = NULL;
		return T;
	}


	int pivot_idx = idx[n-1];
	T->idx = pivot_idx;

	double dist[n-1],dist_m[n-1];

	for(int i=0; i<n-1;i++) { // Foreach point

		dist[i] = 0;

		for(int k=0; k<d;k++) {
			dist[i] += pow( X[ IDX(i,k) ] - X[ IDX(pivot_idx,k )]	, 2 ); // Σ(x_i - p_i)^2
		}
		dist[i] = sqrt(dist[i]); √Σ(x_i - pi)^2
		dist_m[i] = dist[i];

	}


	double median = findMedian(dist_m, n-1);
	T->md = median;

	// Find the inner points and outer points
	int n1 = ceil( (double)(n-1)/2 );
	int n2 = floor( (double)(n-1)/2 );

	int *inner_idx = malloc(n1*sizeof(int));
	int *outer_idx = malloc(n2*sizeof(int));

	double *inner_points = malloc(n1*d*sizeof(double));
	double *outer_points = malloc(n2*d*sizeof(double));

	int j1 = 0, j2 = 0;

	for(int i = 0; i < n-1; i++) {

		if (dist[i] <= median) {
			inner_idx[j1] = idx[i];
			for(int k = 0; k < d; k++) {
				inner_points[ IDX(j1,k) ] = X[ IDX(i,k) ];
			}
			j1++;
		}

		else {
			outer_idx[j2] = idx[i];
			for(int k = 0; k < d; k++) {
				outer_points[ IDX(j2,k) ] = X[ IDX(i,k) ];
			}
			j2++;
		}

	}

	// Recurse
	T->inner = vpt(inner_points, inner_idx, n1, d);
	T->outer = vpt(outer_points, outer_idx, n2, d);

	return T;

}

vptree * buildvp (double *X, int n, int d) {

	vptree *T;

	int *idx = malloc(n*sizeof(int));

	for(int i=0; i<n; i++) {
		idx[i] = i;
	}

	T = vpt(X, idx, n, d);

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
