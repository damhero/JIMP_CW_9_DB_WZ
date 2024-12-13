#include "gauss.h"
#include <stdio.h>
#include <math.h>

/**
 * Zwraca 0 - eliminacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
    int n = mat->r; // Zakładamy, że macierz jest kwadratowa: r == c

    for (int k = 0; k < n - 1; k++) {
        // Sprawdzenie dzielenia przez zero (osobliwość)
        if (fabs(mat->data[k][k]) < 1e-12) {
            return 1; // Macierz osobliwa
        }

        // Eliminacja Gaussa
        for (int i = k + 1; i < n; i++) {
            double factor = mat->data[i][k] / mat->data[k][k];

            // Aktualizacja wierszy macierzy mat
            for (int j = k; j < n; j++) {
                mat->data[i][j] -= factor * mat->data[k][j];
            }

            // Aktualizacja macierzy b (kolumna wyników)
            b->data[i][0] -= factor * b->data[k][0];
        }
    }

    return 0; // Eliminacja zakonczona sukcesem
}

/**
 * Rozwiązuje układ równań przy użyciu podstawiania wstecznego.
 *
 * Zwraca 0 - sukces
 * Zwraca 1 - dzielenie przez 0 (macierz osobliwa)
 */
int backsubst(Matrix *mat, Matrix *b, Matrix *x) {
    int n = mat->r;

    for (int i = n - 1; i >= 0; i--) {
        // Sprawdzenie dzielenia przez zero (osobliwość)
        if (fabs(mat->data[i][i]) < 1e-12) {
            return 1; // Macierz osobliwa
        }

        double sum = b->data[i][0];

        for (int j = i + 1; j < n; j++) {
            sum -= mat->data[i][j] * x->data[j][0];
        }

        x->data[i][0] = sum / mat->data[i][i];
    }

    return 0; // Sukces
}

/**
 * Funkcja rozwiazuje uklad rownan Ax = b.
 *
 * Zwraca 0 - sukces
 * Zwraca 1 - macierz osobliwa
 */
int solve(Matrix *mat, Matrix *b, Matrix *x) {
    if (eliminate(mat, b) != 0) {
        return 1; // Eliminacja nie powiodla sie
    }

    if (backsubst(mat, b, x) != 0) {
        return 1; // Podstawianie wsteczne nie powiodlo sie
    }

    return 0; // Sukces
}
