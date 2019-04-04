#include <iostream>
#include <cmath>

#define N 5
#define IT_MAX 30

double getRJ(double *a, double *b, double x, int n){
    b[n] = 0;
    for(int k = n-1; k >= 0; k--){
        b[k] = a[k+1] + x*b[k+1];
    }
    double Rj = a[0] + x*b[0];
    return Rj;
}

int main(void){
    double a[N+1] = {240, -196, -92, 33, 14, 1};
    double b[N+1];
    double c[N];
    double x0;
    double x1;
    double Rj;
    double Rpj;
    FILE *f = fopen("output.dat", "w");

    for(int L = 1; L <= N; L++){
        printf("L\tit\tx0\tRj\tRpj\n");
        int n = N - L + 1;
        x0 = 0;
        for(int it = 1; it <= IT_MAX; it++){
            Rj = getRJ(a, b, x0, n);
            Rpj = getRJ(b, c, x0, n-1);
            x1=x0-Rj/Rpj;
            printf("%d\t%d\t%g\t%g\t%g\n", L, it, x0, Rj,Rpj);
            fprintf(f, "%d\t%d\t%g\t%g\t%g\n", L, it, x0, Rj,Rpj);
            if(fabs(x1 - x0) < 1.0e-7){
                break;
            }
            x0 = x1;
        }
        for(int i=0; i<=(n-1); i++){
            a[i]=b[i];
        }
        printf("\n");
        fprintf(f,"\n");
    }
    fclose(f);

    return 0;
}


/*
Funkcja obliczajaca reszte R - wzory 3-5; - zwraca Rj, 
przyjmuje (tablice a - ustalona,b -ustalana, aktualne przyblizenie x)
*/