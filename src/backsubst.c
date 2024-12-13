#include "backsubst.h"
#include <math.h>
#include <stdio.h>
#define EPSILON 1e-10
/**
 * Zwraca 0 - wsteczne podstawienie zakonczone sukcesem
 * Zwraca 1 - błąd dzielenia przez 0 (element na diagonali = 0)
 * Zwraca 2 - błąd nieprawidłowych rozmiarów macierzy
 */
int  backsubst(Matrix *x, Matrix *mat, Matrix *b) {
	// Sprawdzenie, czy rozmiary macierzy są poprawne
	if (mat->r != mat->c || mat->r != b->r || b->c != 1 || x->r != b->r || x->c != 1) {
		return 2;
	}

	for (int i = mat->r - 1; i >= 0; i--) {
		double sum = b->data[i][0];
		for (int j = i + 1; j < mat->c; j++) {
			sum -= mat->data[i][j] * x->data[j][0];
		}

		// Sprawdzenie, czy element na diagonali jest równy 0
		//element nie będzie równy dokładnie zero nigdy, ponieważ działania na liczbach zmiennoprzecinkowych są obarczone błędem
		if (fabs(mat->data[i][i])  < EPSILON) {
			return 1;
		}

		x->data[i][0] = sum / mat->data[i][i];
	}

	return 0;
}


