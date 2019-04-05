#include <cmath>
#include <iostream>

#define N 5
#define IT_MAX 30

double getRJ(double *a, double *b, double x, int n) {
    b[n] = 0;
    for (int k = n - 1; k >= 0; k--) {
        b[k] = a[k + 1] + x * b[k + 1];
    }
    double Rj = a[0] + x * b[0];
    return Rj;
}

inline double y(double a, double b, double x) {
    return a * x + b;
}
inline double polynomial(double *a, double len, double x) {
    double sum = 240;
    sum += -196 * pow(x, 1);
    sum += -92 * pow(x, 2);
    sum += 33 * pow(x, 3);
    sum += 14 * pow(x, 4);
    sum += 1 * pow(x, 5);
    return sum;
}

int main(void) {
    double a[N + 1] = {240, -196, -92, 33, 14, 1};
    double b[N + 1];
    double c[N];
    double x0;
    double x1;
    double Rj;
    double Rpj;
    FILE *f = fopen("roots.dat", "w");
    // FILE *f2 = fopen("graph.dat", "w");

    // double dy;
    // double A[IT_MAX];
    // double B[IT_MAX];
    // int n_tangent;

    for (int L = 1; L <= N; L++) {
        printf("L\tit\tx0\tRj\tRpj\n");
        int n = N - L + 1;
        x0 = 10;
        for (int it = 1; it <= IT_MAX; it++) {
            // if (L == 2) {
            //     dy = (polynomial(a, N + 1, x0 + 1.0e-4) - polynomial(a, N + 1, x0 - 1.0e-4)) / (2 * 1.0e-4);
            //     A[it] = dy;
            //     B[it] = -dy * x0 + polynomial(a, N + 1, x0);
            // }
            Rj = getRJ(a, b, x0, n);
            Rpj = getRJ(b, c, x0, n - 1);
            x1 = x0 - Rj / Rpj;
            printf("%d\t%d\t%g\t%g\t%g\n", L, it, x0, Rj, Rpj);
            fprintf(f, "%d\t%d\t%g\t%g\t%g\n", L, it, x0, Rj, Rpj);
            if (fabs(x1 - x0) < 1.0e-7) {
                // if (L == 2) n_tangent = it;
                break;
            }
            x0 = x1;
        }
        for (int i = 0; i <= (n - 1); i++) {
            a[i] = b[i];
        }
        printf("\n");
        fprintf(f, "\n");
    }

    // Writing the tangent lines
    // for (int i = 0; i < 2000; i++) {
    //     double x = ((double)i - 1000) / 100.0;
    //     fprintf(f2, "%g\t%g\t", x, polynomial(a, N + 1, x));
    //     for (int j = 1; j <= n_tangent; j++) {
    //         fprintf(f2, "%g\t", y(A[j], B[j], x));
    //     }
    //     fprintf(f2, "\n");
    // }

    fclose(f);
    // fclose(f2);

    return 0;
}

/*
Funkcja obliczajaca reszte R - wzory 3-5; - zwraca Rj, 
przyjmuje (tablice a - ustalona,b -ustalana, aktualne przyblizenie x)
*/