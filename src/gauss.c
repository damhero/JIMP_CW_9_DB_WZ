#include "gauss.h"
#include <stdio.h>
#include <math.h>
#include "backsubst.h"

/**
 * Zwraca 0 - eliminacja zakonczona sukcesem
 * Zwraca 1 - macierz osobliwa - dzielenie przez 0
 */
int eliminate(Matrix *mat, Matrix *b) {
    int n = mat->r; // Zakładamy, że macierz jest kwadratowa: r == c

    for (int k = 0; k < n - 1; k++) {
        // Sprawdzenie dzielenia przez zero (osobliwość)
        int maxRow = k;
    for (int i = k + 1; i < n; i++) {
        if (fabs(mat->data[i][k]) > fabs(mat->data[maxRow][k])) {
            maxRow = i; // Znaleziono nowy największy element
        }
    }
    if (maxRow != k) {
        // Zamiana wierszy mat
        for (int j = 0; j < n; j++) {
            double temp = mat->data[k][j];
            mat->data[k][j] = mat->data[maxRow][j];
            mat->data[maxRow][j] = temp;
        }
        // Zamiana elementów w macierzy b
        double tempB = b->data[k][0];
        b->data[k][0] = b->data[maxRow][0];
        b->data[maxRow][0] = tempB;
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
