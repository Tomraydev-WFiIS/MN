#include<stdio.h>
#include<math.h>


double f(double x){
    return log(pow(x, 3) + 3*pow(x,2) + x + 0.1) * sin(18*x);
}

void trapezoid(int n, double D[n+1][n+1]){
    for(int w = 0; w <= n; w++){
        int N = pow(2, w);
        // printf("N = %d", N);
        double h = 1.0/(double)N;
        for(int i = 0; i < N; i++){
            D[w][0] += (h/2.0) * (f(i*h) + f((i+1)*h) );
        }
    }
    return;
}

void three_eights(int n, double D[n+1][n+1]){
    for(int w = 0; w <= n; w++){
        int N = 3*pow(2, w);
        double h = 1.0/(double)N;
        for(int i = 0; i <= (N/3)-1; i++){
            D[w][0] += (3*h/8.0) * (f(3*i*h) + 3*f((3*i+1)*h) + 3*f((3*i+2)*h)  + f((3*i+3)*h) );
        }
    }
    return;
}

void richardson(int n, double D[n+1][n+1]){
    for(int w = 1; w <= n; w++){
        for(int k = 1; k <= n; k++){
            D[w][k] = (pow(4, k) * D[w][k-1] - D[w-1][k-1]) / (pow(4,k) - 1.0);
        }
    }
    return;
}

int main(void){
    int n = 8;

    //trapezoid
    double D[n+1][n+1];
    for(int i = 0; i < n+1; i++){
        for(int j = 0; j < n+1; j++){
            D[i][j] = 0;
        }
    }
    trapezoid(n, D);
    richardson(n, D);
    
    FILE *file1 = fopen("output.dat", "w");
    for(int w = 0; w <= n; w++){
        for(int k = 0 ; k < w; k++){
            fprintf(file1, "%g\t", D[w][k]);
        }
        fprintf(file1, "\n");
    }
    fprintf(file1, "\n\n");
    

    // 3/8
    for(int i = 0; i < n+1; i++){
        for(int j = 0; j < n+1; j++){
            D[i][j] = 0;
        }
    }
    three_eights(n, D);
    richardson(n, D);
    for(int w = 0; w <= n; w++){
        for(int k = 0 ; k < w; k++){
            fprintf(file1, "%g\t", D[w][k]);
        }
        fprintf(file1, "\n");
    }

    return 0;
}

/* do sprawozdania
przedyskutowac zbieznosc kolumny i diagonali 
*/