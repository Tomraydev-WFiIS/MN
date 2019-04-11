#include <cmath>
#include <iostream>

double f(double x){
    return 1/ (1+ pow(x,2) );
}

double W(double x, int n, double *X, double *ir){
    double sum = 0;
    for(int j = 0; j <= n; j++){
        double product = 1;
        for(int i = 0; i <= j-1; i++){
            product *= x - X[i];
        }
        sum += ir[j] * product;
    }
}

void W_coefficients(double x, int n, double *X, double *ir){
    for(int j = 0; j <= n; j++){
        double product = ir[j];
        for(int i = 0; i <= j-1; i++){
            product *= x - X[i];
        }
        printf("x^%d = %g\n", j, product);
    }
}


int main(void) {
    //////////////////////// Nierownoodlegle wezly ////////////////////////
    
    int N = 6; // stopien wielomianu
    double x[N+1] = {-5, -2, -0.5, 0, 0.5, 2, 5}; // N+1 wezlow, N - stopien wielomianu
    double y[N+1];
    double derivative[N+1];

    for(int i = 0; i < N+1; i++){
        y[i] = f(x[i]);
    }

    for(int j = 0; j < N+1; j++){
        double sum = 0;
        for(int k = 0; k <= j; k++){
            double product = 1;
            for(int l = 0; l <= j; l++){
                if(l == k){
                    continue;
                }else{
                    product *= 1.0 / (x[k] - x[l]);
                }
            }
            sum += y[k] * product;
        }
        derivative[j] = sum;
    }

    //////////////////////// Rownoodlegle wezly ////////////////////////
    double x2[N+1];
    double y2[N+1];
    double derivative2[N+1];

    for(int i = 0; i < N+1; i++){
        x2[i] = -5 + (double)i * (5.0 -(-5.0))/6.0;
    }

    for(int i = 0; i < N+1; i++){
        y2[i] = f(x2[i]);
    }

    for(int j = 0; j < N+1; j++){
        double sum = 0;
        for(int k = 0; k <= j; k++){
            double product = 1;
            for(int l = 0; l <= j; l++){
                if(l == k){
                    continue;
                }else{
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
    double x_min = -5;
    double x_max = 5;
    double step = 0.01;

    double i = x_min;
    while(i < x_max){
        fprintf(f1, "%g\t%g\t%g\n", i, f(i), W(i, N, x, derivative));
        fprintf(f2, "%g\t%g\t%g\n", i, f(i), W(i, N, x2, derivative2));
        i += step;
    }
    fclose(f1);
    fclose(f2);

    //////////////////////// Tabelki ////////////////////////
    printf("Ilorazy roznicowe:\n");
    for(int i = 0; i < N+1; i++){
        printf("%g\t%g\n", derivative[i], derivative2[i]);
    }

    // printf("Wspolczynniki dla Nierownoleglych wezlow\n");
    // W_coefficients(i, N, x, derivative);
    // printf("Wspolczynniki dla Rownoleglych wezlow\n");
    // W_coefficients(i, N, x2, derivative2);

    return 0;
}