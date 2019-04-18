#include <cmath>
#include <iostream>

double f(double x) {
    return 1 / (1 + pow(x, 2));
}

double W(double x, int n, double *X, double *ir) {
    double sum = 0;
    for (int j = 0; j <= n; j++) {
        double product = 1;
        for (int i = 0; i <= j - 1; i++) {
            product *= x - X[i];
        }
        sum += ir[j] * product;
    }
}

void W_coefficients(double x, int n, double *X, double *ir) {
    double alfa[n + 1];
    for (int i = 0; i < n + 1; i++) {      //coefficients
        for (int j = n + 1; j > i; j--) {  // sums
            //nope
        }
    }
}

int main(void) {
    //////////////////////// Nierownoodlegle wezly ////////////////////////

    int N = 6;                                       // stopien wielomianu
    double x[N + 1] = {-5, -2, -0.5, 0, 0.5, 2, 5};  // N+1 wezlow, N - stopien wielomianu
    double y[N + 1];
    double derivative[N + 1];

    for (int i = 0; i < N + 1; i++) {
        y[i] = f(x[i]);
    }

    for (int j = 0; j < N + 1; j++) {
        double sum = 0;
        for (int k = 0; k <= j; k++) {
            double product = 1;
            for (int l = 0; l <= j; l++) {
                if (l == k) {
                    continue;
                } else {
                    product *= 1.0 / (x[k] - x[l]);
                }
            }
            sum += y[k] * product;
        }
        derivative[j] = sum;
    }

    //////////////////////// Rownoodlegle wezly ////////////////////////
    double x2[N + 1];
    double y2[N + 1];
    double derivative2[N + 1];

    for (int i = 0; i < N + 1; i++) {
        x2[i] = -5 + (double)i * (5.0 - (-5.0)) / 6.0;
    }

    for (int i = 0; i < N + 1; i++) {
        y2[i] = f(x2[i]);
    }

    for (int j = 0; j < N + 1; j++) {
        double sum = 0;
        for (int k = 0; k <= j; k++) {
            double product = 1;
            for (int l = 0; l <= j; l++) {
                if (l == k) {
                    continue;
                } else {
                    product *= 1.0 / (x2[k] - x2[l]);
                }
            }
            sum += y2[k] * product;
        }
        derivative2[j] = sum;
    }

    //////////////////////// Zapis do pliku ////////////////////////

    FILE *f1 = fopen("output.dat", "w");
    FILE *f2 = fopen("output2.dat", "w");
    FILE *f3 = fopen("points1.dat", "w");
    FILE *f4 = fopen("points2.dat", "w");
    double x_min = -5;
    double x_max = 5;
    double step = 0.01;

    double i = x_min;
    while (i < x_max) {
        fprintf(f1, "%g\t%g\t%g\n", i, f(i), W(i, N, x, derivative));
        fprintf(f2, "%g\t%g\t%g\n", i, f(i), W(i, N, x2, derivative2));
        i += step;
    }
    for (int i = 0; i < N + 1; i++) {
        fprintf(f3, "%g\t%g\n", x[i], f(x[i]));
        fprintf(f4, "%g\t%g\n", x2[i], f(x2[i]));
    }
    fclose(f1);
    fclose(f2);
    fclose(f3);
    fclose(f4);

    //////////////////////// Tabelki ////////////////////////
    // printf("Ilorazy roznicowe:\n");
    // for (int i = 0; i < N + 1; i++) {
    //     printf("%g\t%g\n", derivative[i], derivative2[i]);
    // }

    for (int i = 0; i < N + 1; i++) {
        printf("%g", derivative2[i]);
        for (int j = 0; j < i; j++) {
            printf(" * ");
            if (x[j] >= 0) {
                printf("(x - %g)", x2[j]);
            } else {
                printf("(x + %g)", -x2[j]);
            }
        }
        printf(" + \n");
    }

    return 0;
}