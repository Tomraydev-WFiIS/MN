#include <cmath>
#include <ctime>
#include <iostream>

double f(double x, double y) {
    double val = (5.0 / 2.0) * pow((x * x - y), 2) + pow((1.0 - x), 2);
    return val;
}

double dfx(double x, double y, double delta_x) {
    double numerator = f(x + delta_x, y) - f(x - delta_x, y);
    double denominator = 2 * delta_x;
    return (numerator / denominator);
}

double dfy(double x, double y, double delta_y) {
    double numerator = f(x, y + delta_y) - f(x, y - delta_y);
    double denominator = 2 * delta_y;
    return (numerator / denominator);
}

double norm(double* r) {
    return sqrt((r[0] * r[0]) + (r[1] * r[1]));
}

//beware of badly implemented momentum
void gradient_descent(double* x, double* y, double* len, double delta, double eps, double h) {
    int i = 0;
    double diff[1000][2] = {0, 0};
    double m = 0.05;
    while (i < 999) {
        x[i + 1] = x[i] - h * dfx(x[i], y[i], delta);
        y[i + 1] = y[i] - h * dfy(x[i], y[i], delta);
        if (i > 15) {
            for (int j = 0; j < 9; j++) {
                x[i + 1] = x[i + 1] + (1.0 - j / 10) * m * diff[i - j][0];
                y[i + 1] = y[i + 1] + (1.0 - j / 10) * m * diff[i - j][1];
            }
        }
        diff[i][0] = x[i + 1] - x[i];
        diff[i][1] = y[i + 1] - y[i];
        printf("x=%g\ty=%g\tf=%g\n", x[i + 1], y[i + 1], f(x[i + 1], y[i + 1]));
        *len = i + 2;
        if (norm(diff[i]) < eps) {
            printf("\ni = %d, norm = %g\n\n", i, norm(diff[i]));
            break;
        }
        i++;
    }
    printf("\ni = %d, norm = %g\n\n", i, norm(diff[i]));
    return;
}

int main(void) {
    double delta = 10e-4;
    double eps = 1e-2;
    double eps2 = 1e-3;
    double h = 0.1;

    double x[1000];
    double y[1000];
    double len = 0;

    double x2[1000];
    double y2[1000];
    double len2 = 0;

    //Starting conditions
    x[0] = -0.75;
    y[0] = 1.75;
    x2[0] = -0.75;
    y2[0] = 1.75;

    //Gradient descent
    gradient_descent(x, y, &len, delta, eps, h);
    gradient_descent(x2, y2, &len2, delta, eps2, h);

    FILE* file1 = fopen("out.dat", "w");
    for (int i = 0; i < len; i++) {
        fprintf(file1, "%g\t%g\n", x[i], y[i]);
    }
    //mock data \/
    fprintf(file1, "\n\n");
    for (int i = 0; i < len2; i++) {
        fprintf(file1, "%g\t%g\n", x2[i], y2[i]);
    }
    fclose(file1);

    return 0;
}
