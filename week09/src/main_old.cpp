#include <cmath>
#include <ctime>
#include <iostream>

#define N 100
#define MS 5
#define MC 5
#define FUN(x, i) (f2(x[(i)]))

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

double F(double x, double *a, double *b) {
    double result = 0;
    for (int k = 0; k <= MS; k++) {
        result += a[k] * sin(k * x);
    }
    for (int j = 0; j <= MS; j++) {
        result += b[j] * cos(j * x);
    }
    return result;
}

int main(void) {
    srand(time(nullptr));
    double x[N];
    double y[N];
    double a[MS + 1];
    double b[MC + 1];

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

    printf("\n");
    //a coefficients
    for (int k = 0; k <= MS; k++) {
        a[k] = 0;
        for (int i = 0; i < N; i++) {
            a[k] += y[i] * sin(k * x[i]);
        }
        a[k] *= 2.0 / (double)N;
        printf("%g\n", a[k]);
    }
    printf("\n");
    //b coefficients
    for (int j = 0; j <= MC; j++) {
        b[j] = 0;
        for (int i = 0; i < N; i++) {
            b[j] += y[i] * cos(j * x[i]);
        }
        b[j] *= 2.0 / (double)N;
        printf("%g\n", b[j]);
    }

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
        fprintf(file2, "%g\t%g\n", i, F(i, a, b));
        i += step;
    }
    fclose(file2);

    return 0;
}