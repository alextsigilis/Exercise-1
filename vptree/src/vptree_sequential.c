#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "vptree.h"

#define IDX(d, i, k)  i*d + k

typedef struct {
	double *point;
	int idx;
	int d;
	double distance;
} tuple;

//! Calculates the distances
//! from every point in a specific point,
//! in d-dimensional space
/*!
	\param A				Input tuple points
	\param n				Number of data points (rows of X)
	\param d				Number of dimensions (collumns of  X)
	\param point		Τhe point at which distances are taken

	\Return 				void
*/
void distances (tuple *A, int n, int d, double *point){

	double* dist = malloc( n * sizeof(double) );

	// Για κάθε σημείο
	for(int i = 0; i < n; i++) {

		dist[i] = 0;

		// Πρόσθεσε τα τετράγωνα των διαφορών
		for(int k = 0; k < d; k++) {
			dist[i] += pow(
											A[i].point[k] - point[k],
											2
										);
		}

		// Πάρε την τετραγωνική ρίζα
		dist[i] = sqrt(dist[i]);
	}

	for(int i = 0; i < n; i++) {
		A[i].distance = dist[i];
	}
}

//! Returns the kth smallest element in
//! an unordered.
/*!
	\param A		Input un-unordered array of tuples
	\param n		Number of elements in A
	\param k		Defines the kth element

	\return The kth smallest elements
					(also changes the array)
*/
double quickSelect (tuple * A, int n, int k) {
	int start = 0;
	int end = n;

	while (start != end) {

		//
		// PARTITION
		//
		tuple pivot = A[end-1];

		int i = start-1;

		for (int j = start; j < end-1; j++) {
			if (A[j].distance <= pivot.distance) {
				i++;
				tuple tmp = A[j];
				A[j] = A[i];
				A[i] = tmp;
			}
		}

		tuple tmp = A[i+1];
		A[i+1] = A[end-1];
		A[end-1] = tmp;
		i++;

		//
		// SELECT
		//
		if (i == k) {
			return A[i].distance;
		}
		else if (i < k){
			start = i+1;
		}
		else {
			end = i;
		}
	}

	return A[start].distance;
}

vptree * vpt (tuple *A, int start, int end, int d) {

	int n = end-start;

	if (n <= 0) {
		return NULL;
	}

	// Allcate the memory for the vptree
	vptree *T = malloc(sizeof(vptree));


	// Store the index of the vp in the original array
	T->idx = A[end-1].idx;

	// Allocate and store the coordinates of the vp
	T->vp = malloc(d*sizeof(double));
	for(int k = 0; k < d; k++) T->vp[k] = A[end-1].point[k];


	// Calculate the distances from the vantage point
	distances(A, n-1, d, T->vp);

	// Find the median distance
	double medianDistance = quickSelect(A, n-1, (n-1)/2);
	T->md = medianDistance;

	// Split into sub problems
	T->inner = vpt(A, start, start+n/2, d);
	T->outer = vpt(A, start+n/2+1, end, d);

	return T;

}


vptree * buildvp (double *X, int n, int d) {

	vptree *T = malloc(sizeof(vptree));
	tuple A[n];

	for(int i = 0; i < n; i++){

		A[i].d = d;
		A[i].point = malloc(d*sizeof(double));
		A[i].distance = 0;

		for(int k = 0; k < d; k++) {
			A[i].point[k] = X[ IDX(d,i,k)  ];
		}
		A[i].idx = i;
	}

	T = vpt(A, 0, n, d);

	return T;

}

vptree * getInner (vptree * T) {return T->inner;}
vptree * getOuter (vptree * T) {return T->outer;}
double  getMD (vptree * T) {return T->md;}
double * getVP (vptree * T) {return T->vp;}
int getIDX (vptree * T) {return T->idx;}
