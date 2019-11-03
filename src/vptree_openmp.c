#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <omp.h>
#include "vptree.h"

#include <stdio.h>

#define   MAX_DIST_THRDS      10
#define   DIST_THRD_THRES     10000*10
#define   VPT_THRD_THRESS     10000*10
#define   IDX(d, i, k)        i*d + k

//! Return the distance between 2 points
/*!
\param x1 		The first point
\param x2 		The second point
\param d 			The dimentions of the points
\return 	The distance from point x1 to x2 (double)
*/
double distance (double *x1, double *x2, int d) {
	double dist = 0;
	for(int k = 0; k < d; k++) {
		dist += pow( x1[k]-x2[k], 2 );
	}
	dist = sqrt(dist);
	return dist;
}



//! Return an array with the distances of every point in X,
//! to the last point in X
/*!
\param X 		The set of points
\param n		The number of points
\param d		The dimentions of the points
\return 	The distances (pointer to array of double)
*/
double *computeDistances (double *X, int n, int d) {

	double *dist = malloc( (n-1) * sizeof(double) );
	double *vp = X + (n-1)*d;

	omp_set_num_threads(8);
 	#pragma omp parallel if(n*d >= 1000000) shared(X,dist,vp, n, d)
	{
		#pragma omp for schedule(static)
		for(int i = 0; i < n-1; i++) {
			dist[i] = 0;
			for(int k = 0; k < d; k++) {
				dist[i] += pow((X[IDX(d,i,k)]- vp[k]), 2);
			}
			dist[i] = sqrt(dist[i]);
		}

	}
	return dist;
}


//! Returns the element of which k elements are less than or equal
/*!
\param dist 		The array of elements
\param n				The number of the elements
\param k				The dimentions of the points
\return 				The k-th element
*/
double quickSelect (double *dist, int n, int k) {
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
				double tmp_d = dist[j];
				dist[j] = dist[i];
				dist[i] = tmp_d;
			}
		}

		double tmp_d= dist[i+1];
		dist[i+1] = dist[end-1];
		dist[end-1] = tmp_d;
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


//! Returns the Vantage Point Tree
/*!
\param X 				The set of points
\param indexes	The indexes of the points
\param n				The number of the points
\param d				The dimentions of the points
\return 				The VPT tree
*/
vptree *vpt (double *X, int *indexes, int n, int d) {

	vptree *T = malloc(sizeof(vptree));

	if(n == 0) {
		return NULL;
	}

	int vp_idx = indexes[n-1];

	T->vp = malloc(d*sizeof(double));
	for(int k=0; k<d; k++) { T->vp[k] = X[ d*(n-1)+k];}

	T->idx = vp_idx;

	if(n==1) {
		T->md = 0;
		T->inner = NULL;
		T->outer = NULL;
		return T;
	}

	double *dist = computeDistances(X,n,d);
	double median = quickSelect(dist,n-1,(n-1)/2);
	T->md = median;
	free(dist);

	// partition to inner and outer elements
	int i = -1;
	for(int j = 0; j < n-1; j++) {
		if(distance(X+d*j, T->vp, d) <= T->md) {
			i++;
			for(int k = 0; k < d; k++) {
				double tmp_x = X[ IDX(d,j,k) ];
				X[ IDX(d,j,k) ] = X[ IDX(d,i,k) ];
				X[ IDX(d,i,k) ] = tmp_x;
			}
			// -------------- //
			int tmp_i = indexes[j];
			indexes[j] = indexes[i];
			indexes[i] = tmp_i;
		}
	}

	omp_set_nested(1);
	#pragma omp parallel shared(X,indexes,i,n,d) if(n*d > VPT_THRD_THRESS && omp_get_num_threads() < 20)
	{
		#pragma omp sections
		{
			#pragma omp section
			T->inner = vpt(X, indexes, i+1, d);
		}

		#pragma omp master
		T->outer = vpt(X+d*(i+1), indexes+(i+1), (n-1)-(i+1), d);
	}


	return T;

}


//! Build vantage-point tree given input dataset X
/*!
\param X Input data points, stored as [n-by-d] array
\param n Number of data points (rows of X)
\param d Number of dimensions (columns of X)
\return The vantage-point tree
*/
vptree * buildvp (double *X, int n, int d) {

	vptree *T;

	double *Y = malloc(n*d*sizeof(double));
	int *indexes = malloc(n*sizeof(int));

	for(int p=0; p < n; p++) {
		indexes[p] = p;
		for(int k=0; k < d; k++){
			Y[ IDX(d,p,k) ] = X[ IDX(d,p,k) ];
 		}
	}

	T = vpt(Y, indexes, n, d);

	return T;

}


//! Return vantage-point subtree with points inside radius
/*!
\param node A vantage-point tree
\return The vantage-point subtree
*/
vptree * getInner (vptree * T) {
	return T->inner;
}


//! Return vantage-point subtree with points outside radius
/*!
\param node A vantage-point tree
\return The vantage-point subtree
*/
vptree * getOuter (vptree * T) {
	return T->outer;
}


//! Return median of distances to vantage point
/*!
\param node A vantage-point tree
\return The median distance
*/
double  getMD (vptree * T) {
	return T->md;
}


//! Return the coordinates of the vantage point
/*!
\param node A vantage-point tree
\return The coordinates [d-dimensional vector]
*/
double * getVP (vptree * T) {
	return T->vp;
}


//! Return the index of the vantage point
/*!
\param node A vantage-point tree
\return The index to the input vector of data points
*/
int getIDX (vptree * T) {
	return T->idx;
}
