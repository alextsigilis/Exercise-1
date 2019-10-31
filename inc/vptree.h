#ifndef __VPTREE_H_
#define __VPTREE_H_

// type definition of vptree

typedef struct tmp_struct {
  double* vp;         // The coordinates vantage point (an array with lenght d)
  double md;         // The median distance
  int idx;           // The index in the initial set
  struct tmp_struct* inner; // The inner sub-tree
  struct tmp_struct* outer; // The outer sub-tree
} vptree;


//! Returns the Vantage Point Tree
/*!
\param X 				The set of points
\param indexes	The indexes of the points
\param n				The number of the points
\param d				The dimentions of the points
\return 				The VPT tree
*/
vptree *vpt (double *X, int *indexes, int n, int d);

// ========== LIST OF ACCESSORS
//! Build vantage-point tree given input dataset X
/*!
\param X Input data points, stored as [n-by-d] array
\param n Number of data points (rows of X)
\param d Number of dimensions (columns of X)
\return The vantage-point tree
*/
vptree * buildvp(double *X, int n, int d);


//! Return vantage-point subtree with points inside radius
/*!
\param node A vantage-point tree
\return The vantage-point subtree
*/
vptree * getInner(vptree * T);


//! Return vantage-point subtree with points outside radius
/*!
\param node A vantage-point tree
\return The vantage-point subtree
*/
vptree * getOuter(vptree * T);


//! Return median of distances to vantage point
/*!
\param node A vantage-point tree
\return The median distance
*/
double getMD(vptree * T);


//! Return the coordinates of the vantage point
/*!
\param node A vantage-point tree
\return The coordinates [d-dimensional vector]
*/
double * getVP(vptree * T);


//! Return the index of the vantage point
/*!
\param node A vantage-point tree
\return The index to the input vector of data points
*/
int getIDX(vptree * T);

#endif // __VPTREE_H_
