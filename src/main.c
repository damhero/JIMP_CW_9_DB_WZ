#include "gauss.h"
#include "backsubst.h"
#include "mat_io.h"
#include <stdlib.h>
#include <stdio.h>




int main(int argc, char ** argv) {
	FILE* file = fopen("./bin/bin","w");
	int res;
	Matrix * A = readFromFile(argv[1]);
	Matrix * b = readFromFile(argv[2]);
	Matrix * x;

	if (A == NULL) return -1;
	if (b == NULL) return -2;
	printToScreen(A);
	printToScreen(b);

	res = eliminate(A,b);
	fprintf(file,"Result: %d\n", res);
	x = createMatrix(b->r, 1);
	if (x != NULL) {
		res = backsubst(x,A,b);
		if(res==0){
		printToScreen(x);
		freeMatrix(x);
		freeMatrix(A);
		freeMatrix(b);
		return EXIT_SUCCESS;
		} else{
			freeMatrix(x);
			freeMatrix(A);
			freeMatrix(b);
			fprintf(stderr,"[!] Macierz osobliwa.\n");
			return EXIT_SUCCESS;
		}
	} else {
		fprintf(stderr,"Błąd! Nie mogłem utworzyć wektora wynikowego x.\n");
		return EXIT_FAILURE;
	}
}
