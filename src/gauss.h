#ifndef _GAUSS_H
#define _GAUSS_H

#include "mat_io.h"

/**
 * Zwraca 0 - elimnacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b);
int solve(Matrix *mat, Matrix *b, Matrix *x);
void swapRows(Matrix *mat, Matrix *b, int row1, int row2);

#endif
