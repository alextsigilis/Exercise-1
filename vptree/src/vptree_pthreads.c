#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "vptree.h"



vptree * buildvp (double * X, int n, int d) {

	printf("WORKS!!!\n");

  return (vptree*) NULL;

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
