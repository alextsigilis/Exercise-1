
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include "vptree.h"

#define IDX(d, i, k)  i*d + k

double *compute_distances (double *X, int* indexes, int n, int d) {

	double *dist = malloc( (n-1) * sizeof(double) );

	int vp_idx = indexes[n-1];

	for(int p = 0; p < n-1; p++) {
		dist[p] = 0;
		int i = indexes[p];
		for(int k = 0; k < d; k++) {
			dist[p] += pow( X[ IDX(d,i,k) ] - X[ IDX(d,vp_idx,k) ] , 2 );
		}
		dist[p] = sqrt(dist[p]);
	}

	return dist;

}

double quickSelect (double *dist, int *indexes, int n, int k) {
	int start = 0;
	int end = n;

	while (start != end) {

		//
		// PARTITION
		//
		double pivot = dist[end-1];

		int i = start-1;

		for (int j = start; j < end-1; j++) {
			if ( dist[j] <= pivot ) {
				i++;
				//--------------------
				double tmp_d = dist[j];
				dist[j] = dist[i];
				dist[i] = tmp_d;
				//----------------
				int tmp_i = indexes[j];
				indexes[j] = indexes[i];
				indexes[i] = tmp_i;
			}
		}

		double tmp_d= dist[i+1];
		dist[i+1] = dist[end-1];
		dist[end-1] = tmp_d;
		// -----------------
		int tmp_i = indexes[i+1];
		indexes[i+1] = indexes[end-1];
		indexes[end-1] = tmp_i;
		i++;
		//
		// SELECT
		//
		if (i == k) {
			return dist[i];
		}
		else if (i < k){
			start = i+1;
		}
		else {
			end = i;
		}
	}

	return dist[start];
}

vptree * vpt (double *X, int *indexes, int n, int d) {

	vptree *T = malloc(sizeof(vptree));

	if(n == 0) {
		return NULL;
	}

	int vp_idx = indexes[n-1];

	T->vp = &(X[ IDX(d,vp_idx,0) ]);
	T->idx = vp_idx;

	if(n==1) {
		T->md = 0;
		T->inner = NULL;
		T->outer = NULL;
		return T;
	}

	double *dist = compute_distances(X,indexes,n,d);
	T->md = quickSelect(dist, indexes, n-1, (n-1)/2);
	free(dist);

	int n_inner, n_outer;
	n_inner = ceil((((double)(n)) - 1) / 2 );
	n_outer = floor( (((double)(n)) - 1) / 2  );

	T->inner = vpt(X, indexes, n_inner, d);
	T->outer = vpt(X, indexes+n_inner, n_outer, d);

	return T;

}

vptree * buildvp (double *X, int n, int d) {

	vptree *T;

	int *indexes = malloc(n*sizeof(int));

	for(int p=0; p < n; p++) {
		indexes[p] = p;
	}

	T = vpt(X, indexes, n, d);

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
