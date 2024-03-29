#include <cmath>
#include <ctime>
#include <iostream>

#define N 100
#define FUN(x, i) (f1(x[(i)]))

double f1(double x) {
    double alfa = rand() / (RAND_MAX + 1.0) - 0.5;
    // double alfa = 0;
    double result = 2 * sin(x) + sin(2 * x) + 2 * sin(3 * x) + alfa;
    return result;
}

double f2(double x) {
    double result = 2 * sin(x) + sin(2 * x) + 2 * cos(x) + cos(2 * x);
    return result;
}

double f3(double x) {
    double result = 2 * sin(1.1 * x) + sin(2.1 * x) + 2 * sin(3.1 * x);
    return result;
}

double F(double x, double *a, double *b, int MS, int MC) {
    double result = 0;
    for (int k = 0; k <= MS; k++) {
        result += a[k] * sin(k * x);
    }
    for (int j = 0; j <= MS; j++) {
        result += b[j] * cos(j * x);
    }
    return result;
}

void calc_a(double *a, int m, double *x, double *y) {
    printf("A, Ms = %d\n", m);
    for (int k = 0; k <= m; k++) {
        a[k] = 0;
        for (int i = 0; i < N; i++) {
            a[k] += y[i] * sin(k * x[i]);
        }
        a[k] *= 2.0 / (double)N;
        printf("%g\n", a[k]);
    }
    printf("\n");
}

void calc_b(double *b, int m, double *x, double *y) {
    printf("B, Mc = %d\n", m);
    for (int j = 0; j <= m; j++) {
        b[j] = 0;
        for (int i = 0; i < N; i++) {
            b[j] += y[i] * cos(j * x[i]);
        }
        b[j] *= 2.0 / (double)N;
        printf("%g\n", b[j]);
    }
    printf("\n");
}

int main(void) {
    srand(time(nullptr));
    double x[N];
    double y[N];

    double x_max = 2 * M_PI;
    double x_min = 0;
    double h = (x_max - x_min) / (N - 1.0);

    //nodes
    for (int i = 0; i < N; i++) {
        x[i] = x_min + i * h;
        // printf("%g\n", x[i]);
    }

    for (int i = 0; i < N; i++) {
        y[i] = FUN(x, i);
        // printf("%g\n", y[i]);
    }
    /*****************************************************/
    double a[2][30 + 1];
    double b[2][30 + 1];
    printf("\n");
    //a coefficients
    calc_a(a[0], 5, x, y);
    calc_a(a[1], 30, x, y);
    printf("\n");
    //b coefficients
    calc_b(b[0], 5, x, y);
    calc_b(b[1], 30, x, y);

    //Saving to files
    FILE *file1 = fopen("nodes.dat", "w");
    for (int i = 0; i < N; i++) {
        fprintf(file1, "%g\t%g\n", x[i], y[i]);
    }
    fclose(file1);

    FILE *file2 = fopen("approximation.dat", "w");
    double step = 0.01;
    double i = x_min;
    while (i < x_max) {
        fprintf(file2, "%g\t%g\t%g\n", i,
                F(i, a[0], b[0], 5, 5),
                F(i, a[1], b[1], 30, 30));
        i += step;
    }
    fclose(file2);

    FILE *file3 = fopen("coefficients_5.dat", "w");
    for (int k = 0; k <= 5; k++) {
        fprintf(file3, "%d\t%g\t%g\n", k, a[0][k], b[0][k]);
    }
    fclose(file3);

    FILE *file4 = fopen("coefficients_30.dat", "w");
    for (int j = 0; j <= 30; j++) {
        fprintf(file4, "%d\t%g\t%g\n", j, a[1][j], b[1][j]);
    }
    fclose(file4);

    return 0;
}