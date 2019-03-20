#include<iostream>
#include<gsl/gsl_linalg.h> // reuqires gsl installed
#include<math.h>

#define abs(X) ( (X)>0? (X):-(X) ) 
#define min(X,Y) ( (X)<(Y)? (X): (Y)  )
#define max(X,Y) ( (X)>(Y)? (X): (Y)  )

#define N 15
#define M 5

// void print_gsl_matrix(gsl_matrix *A, int m, int n){
//     for(int i = 0; i < m; i++){
//         for(int j = 0; j < n; j++){
//             printf("%6.2lf #", gsl_matrix_get(A, i, j) );
//         }
//         printf("#\n");
//     }
//     printf("\n\n");
// }

void print_matrix(double * A[N], int n){
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < n; j++)
        {
            printf("%6.2lf\t", A[i][j]);
        }
        printf("\n");
    }
    printf("\n\n");
}



int main(void){
    // gsl_matrix *A = gsl_matrix_calloc(N, N);
    // double ** A = new double* [N];
    double ** A = new double* [N];
    for(int i = 0; i < N; i++)
    {
        A[i] = new double[N];
    }

    double * b = new double[N];
    double * x = new double[N];

    for(int i = 0; i < N; i++){
        b[N] = i+1;
        x[N] = i+1;
        for(int j = 0; j < N; j++){
            if(abs(i-j) <= M){
                A[i][j] = 1. / (1 + abs(i-j) );
            }else {
                A[i][j] = 0.;
            }
        }
    }
    print_matrix(A, N);
    // gsl_permutation *P = gsl_permutation_calloc(N);


// ******** free memory
    // gsl_vector_free(x);
    // gsl_matrix_free(A);
    // gsl_permutation_free(P);

    return 0;
}