#include<stdio.h>
#include<gsl/gsl_linalg.h> // reuqires gsl installed
#include<math.h>

#define N 4

void print_matrix(gsl_matrix *A, int m, int n){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            printf("%6.2lf #", gsl_matrix_get(A, i, j) );
        }
        printf("#\n");
    }
    printf("\n\n");
}



int main(void){
    double delta = 2;
    int signum;
    double det_A;
    double cond;

    gsl_matrix *A = gsl_matrix_calloc(N, N);
    gsl_matrix *AA = gsl_matrix_calloc(N, N);
    gsl_matrix *A_inv = gsl_matrix_calloc(N, N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            double x = 1/(i + j + delta);
            gsl_matrix_set(A, i, j, x);
            gsl_matrix_set(AA, i, j, x);
        }
    }

    print_matrix(A, N, N);
    gsl_permutation *P = gsl_permutation_calloc(N);
    gsl_linalg_LU_decomp(A, P, &signum);

    // Determinant
    det_A = 1;
    for(int i = 0; i < N; i++){
        det_A *= gsl_matrix_get(A, i, i);
    }
    printf("Det(A) = %g\n\n", det_A);

    printf("*****Lower Matrix*****\n");
    gsl_matrix *L = gsl_matrix_calloc(N, N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < i+1; j++){
            gsl_matrix_set(L, i, j, gsl_matrix_get(A, i, j) );
            if(i == j){
                gsl_matrix_set(L, i, j, 1 );
            }
        }
    }
    print_matrix(L, N, N);

    printf("*****Upper Matrix*****\n");
    gsl_matrix *U = gsl_matrix_calloc(N, N);
    for(int i = 0; i < N; i++){
        for(int j = i; j < N; j++){
            gsl_matrix_set(U, i, j, gsl_matrix_get(A, i, j) );
        }
    }
    print_matrix(U, N, N);
    gsl_vector* x = gsl_vector_calloc(N);
    gsl_vector* b = gsl_vector_calloc(N);


    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            gsl_vector_set(b, j, 0);
        }
        gsl_vector_set(b, i, 1);
        gsl_linalg_LU_solve(A, P, b, x);
        for(int j = 0; j < N; j++){
            gsl_matrix_set(A_inv, j, i, gsl_vector_get(x, j));
        }
    }
    printf("*****A inversed*****\n");
    print_matrix(A_inv, N, N);
    
    gsl_matrix* m_product = gsl_matrix_calloc(N, N);
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            double val = 0;
            for(int k = 0; k < N; k++){
                val += gsl_matrix_get(AA, i, k) * gsl_matrix_get(A_inv, k, j);
            }
            gsl_matrix_set(m_product, i, j, val);
        }
    }
    printf("*****A * A_inversed *****\n");
    print_matrix(m_product, N, N);

    double max_AA;
    double max_A_inv;
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            if(gsl_matrix_get(AA, i, j)  > max_AA){
                max_AA = gsl_matrix_get(AA, i, j);
            }
            if(gsl_matrix_get(A_inv, i, j)  > max_A_inv){
                max_A_inv = gsl_matrix_get(A_inv, i, j);
            }
        }
    }
    cond = max_AA * max_A_inv;
    printf("Condition number of matrices A and A_inverse: %g\n", cond);


    gsl_vector_free(x);
    gsl_vector_free(b);
    gsl_matrix_free(A);
    gsl_matrix_free(AA);
    gsl_matrix_free(A_inv);
    gsl_matrix_free(L);
    gsl_matrix_free(U);
    gsl_matrix_free(m_product);
    gsl_permutation_free(P);

    return 0;
}