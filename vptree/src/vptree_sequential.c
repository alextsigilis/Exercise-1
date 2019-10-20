#include <stdlib.h>
#include <math.h>
#include "vptree.h"

#define GET(d, i, k)  i*d + k - 1

double findMedian (double * A, int n) {

	int k = n/2;

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

vptree * buildvp (double * X, int n, int d) {

	vptree *T = malloc(sizeof(vptree));

	//
	//    ALGORITHM
	// ================
	// 1. Choose a Vantage Point (VP)
	// 2. Compute the distance from the VP to every other point
	// 3. Find the median Distance
	// 4. Create the current node
	// 5. Recursivly compute left and right child
	// ---------------------------------------------------------

	// STEP 1:
	int pivot = n-1; // Uses the last element as pivot

	// STEP 2:
	double distance[n];
	for (int i = 0; i < n; i++) {
			distance[i] = 0;
			for (int k = 0; k < d; k++) {
				int idx = GET(d, i, k),
						pvt_idx = GET(d,pivot,k);
				distance[i] += pow(X[idx] - X[pvt_idx], 2);
			}
			distance[i] = sqrt( distance[i] );
	}

	// STEP 3:
	double medianDistance = findMedian(distance, n);

	// STEP 4:
	T->vp = malloc(d*sizeof(double));
	for (int k = 0; k < d; k++) {
		int idx = GET(d, pivot,k);
		T->vp[k] = X[idx];
	}

	T->md = medianDistance;

	T->idx = n-1;

	// STEP 5:
	if (n > 1) {
		int n1 = floor( (double)(n/2) ),
				n2 = ceil( (double)(n/2) );
		double *X_inner = X + 0*d,
					 *X_outer = X + n1*d;
		T->inner = buildvp(X_inner, n1, d);
		T->outer = buildvp(X_outer, n2, d);

		T->outer->idx += n1;
	}

	else {
		T->outer = NULL;
		T->inner = NULL;
	}

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
