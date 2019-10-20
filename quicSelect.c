#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int cmp (const void* x, const void* y) {
	return *(double*)x - *(double*)y;
}

double quickSelect (double * A, int n, int k) {

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

int main () {

	srand(time(NULL));

	int n = rand() % 20;

	double A[n];

	for (int i = 0; i < n; i++) {
		A[i] = (double) (rand() % 100);
		printf("%.0f ", A[i]);
	}
	printf("\n");
	

	printf("QSelect Median = %0.0f\n", quickSelect(A, n, n/2));

	qsort(A, n, sizeof(double), cmp);

	for (int i = 0; i < n; i++) {
		printf("%.0f ", A[i]);
	}
	printf("\n %.0f \n", A[n/2]);

	return 0;

}
