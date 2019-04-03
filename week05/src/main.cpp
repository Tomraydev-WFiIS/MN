#include <math.h>
#include <stdio.h>
#include <iostream>
// #include "/opt/NR/numerical_recipes.c/nrutil.h"
// #include "/opt/NR/numerical_recipes.c/nrutil.c"
// #include "/opt/NR/numerical_recipes.c/tred2.c"
// #include "/opt/NR/numerical_recipes.c/tqli.c"
// #include "/opt/NR/numerical_recipes.c/pythag.c"

#include "../include/nrutil.c"
#include "../include/nrutil.h"
#include "../include/pythag.c"
#include "../include/tqli.c"
#include "../include/tred2.c"

#define N 7
#define IT_MAX 8

void printMatrix(float **A, int len);
void printVector(float *v, int len);
float *matrixTimesVector(float **A, int r, int c, float *v);
float scalarProduct(float *v1, float *v2, int len);
float norm(float *v, int len);
float *normalize(float *v, int len, float norm);
float **vectorProduct(float *v1, float *v2, int len);
float **redhot(float **W, float lambda, float *v1, float *v2, int len);  //chili peppers
void printMatrixLatex(float **, int m, int n);
void printVectorLatex(float *, int n);

int main(void) {
    float **A;
    float *d;
    float *e;
    float *ev;  //eigenvalues - wartosci wlasne

    ////////////////////// METODA BEZPOSREDNIA //////////////////////
    // Inicjalizacja macierzy A
    A = matrix(1, N, 1, N);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            A[i][j] = sqrt(i + j);
        }
    }
    // printMatrixLatex(A, N, N);

    d = vector(1, N);
    e = vector(1, N);

    tred2(A, N, d, e);  // Macierz A nadpisna przez macierz przejscia P

    tqli(d, e, N, A);  // A - wektory wlasne macierzy A, d - wartosci wlasne

    printf("Wartosci wlasne wyznaczone metoda bezposrednia\n");
    ev = vector(1, N);
    for (int i = 1; i <= N; i++) {
        ev[i] = d[N - i + 1];
    }

    printVector(ev, N);
    printVectorLatex(ev, N);

    ////////////////////// METODA ITERACYJNA //////////////////////
    float *lambda = vector(1, N);  // wartosci wlasne
    float **lambdas = matrix(1, IT_MAX, 1, N);
    float *x_0 = vector(1, N);
    float *x_1 = vector(1, N);

    //Inicjalizacja W = A
    float **W = matrix(1, N, 1, N);
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= N; j++) {
            W[i][j] = sqrt(i + j);
        }
    }

    //iteracje k
    for (int k = 1; k <= N; k++) {
        for (int i = 1; i <= N; i++) {
            x_0[i] = 1;
        }

        for (int i = 1; i <= IT_MAX; i++) {
            x_1 = matrixTimesVector(W, N, N, x_0);
            lambda[k] = scalarProduct(x_1, x_0, N) / scalarProduct(x_0, x_0, N);
            lambdas[i][k] = abs(ev[k] - lambda[k]);
            x_1 = normalize(x_1, N, norm(x_1, N));
            x_0 = x_1;
        }
        W = redhot(W, lambda[k], x_0, x_0, N);
    }

    FILE *f = fopen("eigenvalues.dat", "w");
    for (int i = 1; i <= IT_MAX; i++) {
        fprintf(f, "%d\t", i);
        for (int k = 1; k <= N; k++) {
            fprintf(f, "%g\t", lambdas[i][k]);
        }
        fprintf(f, "\n");
    }
    fclose(f);

    printf("Wartosci wlasne wyznaczone metoda iteracyjna\n");
    printVector(lambda, N);
    printVectorLatex(lambda, N);

    return 0;
}

void printMatrix(float **A, int len) {
    for (int i = 1; i <= len; i++) {
        for (int j = 1; j <= len; j++) {
            printf("%lf\t", A[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    return;
}

void printVector(float *v, int len) {
    for (int i = 1; i <= len; i++) {
        printf("%g\t", v[i]);
    }
    printf("\n\n");
}

float *matrixTimesVector(float **A, int r, int c, float *v) {
    float *o = vector(1, r);
    for (int i = 1; i <= r; i++) {
        float sum = 0;
        for (int j = 1; j <= c; j++) {
            sum += A[i][j] * v[j];
        }
        o[i] = sum;
    }
    return o;
}

float scalarProduct(float *v1, float *v2, int len) {
    float sum = 0;
    for (int i = 1; i <= len; i++) {
        sum += v1[i] * v2[i];
    }
    return sum;
}

float norm(float *v, int len) {
    float sum = 0;
    for (int i = 1; i <= len; i++) {
        sum += v[i] * v[i];
    }
    sum = sqrt(sum);
    return sum;
}

float *normalize(float *v, int len, float norm) {
    float *o = vector(1, len);
    for (int i = 1; i <= len; i++) {
        o[i] = v[i] / norm;
    }
    return o;
}

float **vectorProduct(float *v1, float *v2, int len) {
    float **O = matrix(1, len, 1, len);

    for (int i = 1; i <= len; i++) {
        for (int j = 1; j <= len; j++) {
            O[i][j] = v1[i] * v2[j];
        }
    }
    return O;
}

float **redhot(float **W, float lambda, float *v1, float *v2, int len) {
    float **O = matrix(1, len, 1, len);
    float **X = matrix(1, len, 1, len);
    X = vectorProduct(v1, v2, len);

    for (int i = 1; i <= len; i++) {
        for (int j = 1; j <= len; j++) {
            O[i][j] = W[i][j] - lambda * X[i][j];
        }
    }
    return O;
}

void printMatrixLatex(float **A, int m, int n) {
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            printf("%6.2lf #", A[i][j]);
        }
        printf("#\n");
    }
    printf("\n\n");
}

void printVectorLatex(float *v, int n) {
    for (int i = 1; i <= n; i++) {
        // printf("λ%d = %g,\n", i, v[i]);
        printf("%g\n", v[i]);
    }
    printf("\n\n");
}