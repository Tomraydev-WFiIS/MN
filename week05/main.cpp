#include <stdio.h>
#include <math.h>
#include <iostream>
#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/tred2.c"
#include "/opt/NR/numerical_recipes.c/tqli.c"
#include "/opt/NR/numerical_recipes.c/pythag.c"

#define n 7
#define IT_MAX 8

void printMatrix(float ** A, int len);
void printVector(float *v, int len);
float *matrixTimesVector(float **A, int r, int c, float *v);
float scalarProduct(float *v1, float *v2, int len);
float norm(float *v, int len);
float *normalize(float *v, int len, float norm);
float **vectorProduct(float *v1, float *v2, int len);
float **redhot(float **W, float lambda, float *v1, float *v2, int len);//chili peppers


int main(void){
    float **A;
    float *d;
    float *e;

    A = matrix(1, n, 1, n);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            A[i][j] = sqrt(i+j);
        }
    }

    d = vector(1,n);
    e = vector(1,n);

    tred2(A, n, d, e); // Macierz A nadpisna przez macierz przejscia P

    tqli(d, e, n, A); // A - wektory wlasne macierzy A, d - wartosci wlasne

    printf("Wartosci wlasne wyznaczone metoda bezposrednia\n");
    printVector(d, n);

    // METODA ITERACYJNA
    printf("Wartosci wlasne wyznaczone metoda iteracyjna\n");
    float *lambda = vector(1,n);// wartosci wlasne

    //Inicjalizacja W = A
    float ** W = matrix(1, n, 1, n);
    for(int i = 1; i <= n; i++){
        for(int j = 1; j <= n; j++){
            W[i][j] = sqrt(i+j);
        }
    }

    float *x_0 = vector(1,n);
    float *x_1 = vector(1,n);
    //iteracje k
    for(int k = 1; k <= n; k++){
        for(int i = 1; i <= n; i++){
            x_0[i] = 1;
        }

        for(int i = 0; i < IT_MAX; i++){
            x_1 = matrixTimesVector(W, n, n, x_0);
            lambda[k] = scalarProduct(x_1, x_0, n) / scalarProduct(x_0, x_0, n);
            x_1 = normalize(x_1, n, norm(x_1, n) );
            x_0 = x_1;
        }
        W = redhot(W, lambda[k], x_0, x_0, n);
    }
    printVector(lambda, n);

    return 0;
}

void printMatrix(float ** A, int len){
    for(int i = 1; i <= len; i++){
        for(int j = 1; j <= len; j++){
            printf("%lf\t", A[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
    return;
}

void printVector(float *v, int len){
    for(int i = 1; i <= len; i++){
        printf("%g\t", v[i]);
    }
    printf("\n\n");
}

float *matrixTimesVector(float **A, int r, int c, float *v){
    float *o = vector(1, r);
    for(int i = 1; i <= r; i++){
        float sum = 0;
        for(int j = 1; j <= c; j++){
            sum += A[i][j] * v[j];
        }
        o[i] = sum;
    }
    return o;
}

float scalarProduct(float *v1, float *v2, int len){
    float sum = 0;
    for(int i = 1; i <= len; i++){
        sum += v1[i] * v2[i];
    }
    return sum;
}

float norm(float *v, int len){
    float sum = 0;
    for(int i = 1; i <= len; i++){
        sum += v[i] * v[i];
    }
    sum = sqrt(sum);
    return sum;
}

float *normalize(float *v, int len, float norm){
    float *o = vector(1, len);
    for(int i = 1; i <= len; i++){
        o[i] = v[i] / norm;
    }
    return o;
}

float **vectorProduct(float *v1, float *v2, int len){
    float **O = matrix(1, len, 1, len);

    for(int i = 1; i <= len; i++){
        for(int j = 1; j <= len; j++){
            O[i][j] = v1[i] * v2[j];
        }
    }
    return O;
}

float **redhot(float **W, float lambda, float *v1, float *v2, int len){
    float **O = matrix(1, len, 1, len);
    float **X = matrix(1, len, 1, len);
    X = vectorProduct(v1, v2, n);

    for(int i = 1; i <= len; i++){
        for(int j = 1; j <= len; j++){
            O[i][j] = W[i][j] - lambda * X[i][j];
        }
    }
    return O;
}

/*
FUNKCJE
1. macierz * wektor,
2. Iloczyn skalarny
3. Redukcja macierzy
*/