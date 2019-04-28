#include <gsl/gsl_linalg.h>  // requires gsl to be installed
#include <math.h>
#include <stdio.h>

#define N 21  //Liczba wezlow

double fun(double x) {
    // return 1.0 / (1.0 + x * x);
    return cos(2 * x);
}

void wyznaczM(double* xw, double* yw, double* m, int n, double alfa, double beta) {
    double h = (xw[n - 1] - xw[0]) / (n - 1.0);
    gsl_matrix* A = gsl_matrix_calloc(n, n);
    gsl_vector* d = gsl_vector_calloc(n);
    double mu = 0.5;
    double lambda = 0.5;
    //Generating A
    gsl_matrix_set(A, 0, 0, 1);
    gsl_matrix_set(A, n - 1, n - 1, 1);
    for (int i = 1; i < n - 1; i++) {
        gsl_matrix_set(A, i, i - 1, mu);
        gsl_matrix_set(A, i, i, 2);
        gsl_matrix_set(A, i, i + 1, lambda);
    }
    //Generating d
    gsl_vector_set(d, 0, alfa);
    gsl_vector_set(d, n - 1, beta);
    for (int i = 1; i < n - 1; i++) {
        double val = 6.0 / (h + h) * (((yw[i + 1] - yw[i]) / h) - ((yw[i] - yw[i - 1]) / h));
        gsl_vector_set(d, i, val);
    }
    //Solving the linear equations
    gsl_linalg_HH_svx(A, d);
    //copying results to the m matrix
    for (int i = 0; i < n; i++) {
        m[i] = gsl_vector_get(d, i);
    }
    gsl_vector_free(d);
    gsl_matrix_free(A);
    return;
}

double wyznaczSx(double* xw, double* yw, double* m, int n, double x) {
    double h = (xw[n - 1] - xw[0]) / (n - 1.0);
    // znajdz pierwszy podprzedział (i-1):xw[i−1]<=x <=xw[i]
    int i = 1;
    for (i = 1; i < n; i++) {
        if (x < xw[i]) {
            break;
        }
    }
    // Sx=........................
    double A = (yw[i] - yw[i - 1]) / h - (h / 6) * (m[i] - m[i - 1]);
    double B = yw[i - 1] - m[i - 1] * h * h / 6;
    double Sx = m[i - 1] * pow((xw[i] - x), 3) / (6 * h);
    Sx += m[i] * pow((x - xw[i - 1]), 3) / (6 * h);
    Sx += A * (x - xw[i - 1]) + B;
    return Sx;
}

double second_derivative(double x, double delta, double (*f)(double)) {
    double n = f(x - delta) - 2 * f(x) + f(x + delta);
    double d = delta * delta;
    return n / d;
}

int main(void) {
    double x_min = -5;
    double x_max = 5;
    double h = (x_max - x_min) / (N - 1.0);
    double x[N];
    double y[N];
    double m[N];  // drugie pochodne
    for (int i = 0; i < N; i++) {
        x[i] = x_min + i * h;
        // printf("%g\n", x[i]);
    }
    // printf("\ny\n");
    for (int i = 0; i < N; i++) {
        y[i] = fun(x[i]);
        // printf("%g\n", y[i]);
    }

    wyznaczM(x, y, m, N, 0, 0);

    //////////////////////// Saving to files ////////////////////////
    FILE* file1 = fopen("interpolation.dat", "w");
    FILE* file2 = fopen("nodes.dat", "w");
    FILE* file3 = fopen("d2.dat", "w");
    FILE* file4 = fopen("d2_nodes.dat", "w");

    //FILE 1
    double step = 0.01;
    double i = x_min;
    while (i < x_max) {
        fprintf(file1, "%g\t%g\t%g\n", i, fun(i), wyznaczSx(x, y, m, N, i));
        i += step;
    }

    //FILE 2
    for (int i = 0; i < N; i++) {
        fprintf(file2, "%g\t%g\n", x[i], y[i]);
    }

    //FILE 3
    i = x_min;
    while (i < x_max) {
        fprintf(file3, "%g\t%g\n", i, second_derivative(i, 0.01, fun));
        i += step;
    }
    //FILE 4
    for (int i = 0; i < N; i++) {
        fprintf(file4, "%g\t%g\t%g\n", x[i], m[i], second_derivative(x[i], 0.01, fun));
    }

    fclose(file1);
    fclose(file2);
    fclose(file3);
    fclose(file4);

    printf("Program executed successfully\n");
    return 0;
}
/*
mu = 1/2;
lambda = 1/2
macierz A, wektor wyrazow wolnych d - gsl

DO ZROBIENIA:
N =  5, 8, 21
f=  f1, f2
*/