#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/* files at taurus.fis.agh.edu.pl
#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/gaussj.c"
*/

#include "../include/nrutil.h"
#include "../include/nrutil.c"
#include "../include/gaussj.c"

#define N 400 // rozmiar macierzy A: NxN

int main(void) {
	double omega = 1;
	double v0 = 0;
	double h = 0.1;
	double aa = 1;
	double val = omega*omega*h*h - 2;

	float **A,**b;
//	Alokacja macierzy
	A = matrix(1, N, 1, N);
	b = matrix(1, N, 1, 1);
	
// 	Wypelnienie macierzy A i wektora b
	for(int i=1; i<=N; ++i){
		b[i][1] = 0.0;
		for(int j=1; j<=N; ++j)
			A[i][j] = 0.0;
	}
	b[1][1] = aa;
	b[2][1] = v0*h;

	for(int i = 1; i <=N; ++i){
		A[i][i] = 1.0;
	}
	A[2][1] = -1.0;
	for(int i = 3; i <=N; ++i){
		A[i][i-1] = val;
	}
	for(int i = 3; i <=N; ++i){
		A[i][i-2] = 1;
	}
/*
	// printing A matrix
	for(int i = 1; i <= N; ++i){
		for(int j = 1; j <= N; ++j){
			printf( " %.2lf ", A[i][j]);
		}
		printf("\n");
	}
*/
//	Rozwiazanie ukladu rownan Ax=b - wywolanie procedury:
	gaussj(A,N,b,1);

//	Wypisanie rozwiazania, ktore procedura gaussj(A,N,b,1); zapisala w wektorze b.
FILE *f = fopen("out.dat","w");
for(int i=1; i<=N; ++i){
	printf("%g\n",  b[i][1]); 
	fprintf(f, "%lf %lf\n", (double)(i)/10, b[i][1]);
}
fclose(f);

//	Zwolnienie pamieci
	free_matrix(A,1,N,1,N);
	free_matrix(b,1,N,1,1);    
	
	return 0;
}

