#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#define N 2000

void print_vector(double* v, int n) {
    for (int i = 0; i < n; i++) {
        printf("%6.2lf/t", v[i]);
    }
    return;
}

double norm(double* v, int n) {
    double sum = 0;
    for (int i = 0; i < n; i++) {
        sum += v[i] * v[i];
    }
    return sum;
}

int main(void) {
    double h = 0.02;
    double V_0 = 0;
    double x_0 = 1;
    double omega = 1;

    double OMEGA = 0.8;

    double beta = 0;
    double F_0 = 0;

    // double beta = 0.4;
    // double F_0 = 0;

    // double beta = 0.4;
    // double F_0 = 0.1;

    double a1 = 1;
    double a2 = omega * omega * h * h - 2 - beta * h;
    double a3 = 1 + beta * h;

    double* d0 = new double[N + 1];
    double* d1 = new double[N + 1];
    double* d2 = new double[N + 1];
    double* b = new double[N + 1];
    double* x_n = new double[N + 1];
    double* x_s = new double[N + 1];

    double accuracy = pow(10.0, -6.0);

    //setting the leading elements
    d0[0] = 1;
    d0[1] = 1;

    d1[0] = 0;
    d1[1] = -1;

    d2[0] = 0;
    d2[1] = 0;

    b[0] = 1;
    b[1] = 0;

    //setting the rest of d and b vectors
    for (int i = 2; i < N + 1; i++) {
        d0[i] = a3;
        d1[i] = a2;
        d2[i] = a1;
        b[i] = F_0 * sin(OMEGA * h * i) * h * h;
    }

    for (int i = 0; i < N + 1; i++) {
        x_s[i] = 1;
        x_n[i] = 1;
    }

    int it = 0;
    double s_s = 0;
    double s_n = 0;
    while (it < 10000) {
        ++it;
        //calculate the new vector x_n
        for (int i = 2; i < N + 1; i++) {
            x_n[i] = (1. / d0[i]) * (b[i] - d1[i] * x_s[i - 1] - d2[i] * x_s[i - 2]);
        }

        s_s = norm(x_s, N + 1);
        s_n = norm(x_n, N + 1);
        std::cout << "accuracy = " << fabs(s_n - s_s) << std::endl;
        if (fabs(s_n - s_s) < accuracy) {
            std::cout << "it = " << it << std::endl;
            break;
        }

        //overwrite the old vector
        for (int i = 0; i < N + 1; i++) {
            x_s[i] = x_n[i];
        }
    }

    double t;
    FILE* f = fopen("output.dat", "w");
    for (int i = 0; i < N + 1; ++i) {
        fprintf(f, "%lf %lf\n", i * h, x_n[i]);
    }
    fclose(f);

    //free memory
    delete d0;
    delete d1;
    delete d2;
    delete b;
    delete x_n;
    delete x_s;
    return 0;
}