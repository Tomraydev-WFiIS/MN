#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "/opt/NR/numerical_recipes.c/nrutil.h"
#include "/opt/NR/numerical_recipes.c/nrutil.c"
#include "/opt/NR/numerical_recipes.c/gauleg.c"
#include "/opt/NR/numerical_recipes.c/gaulag.c"
#include "/opt/NR/numerical_recipes.c/gauher.c"
#include "/opt/NR/numerical_recipes.c/gammln.c"

// #include "../include/nrutil.h"
// #include "../include/nrutil.c"

int factorial(int x){
	if(x <= 0){
		return 1;
	}else {
		return x*factorial(x-1);
	}
}


float fun_1(float x){
	return (x)/(4*x*x+1);
}

float fun_2(float x, int k){
	return pow(x,k);
}

float fun_3(float x, float y){
	return pow(sin(x), 2) * pow(sin(y), 4);
}


// range: [x_a , x_b]
float integral_1(float x_a, float x_b){
	float val_a = (1.0F)/(2*pow(2,2))*log(fabs(pow(2,2)*x_a*x_a + 1.0));
	float val_b = (1.0F)/(2*pow(2,2))*log(fabs(pow(2,2)*x_b*x_b + 1.0));
	return val_b - val_a;
}

// range: [0 , inf]
float integral_2(int k){
	return factorial(k);
}

// range: [-inf , inf]
float integral_3(void){
	return 0.1919832644F;
}

int main(void) {
	float x1;
	float x2;
	int n;
	float * x;
	float * w;
	//************ Integral 1 ************
	x1 = 0.0;
	x2 = 2.0;
	n = 10;
	x = vector(1,n);
	w = vector(1,n);

	// wyznaczenia położenia węzłów i współczynników kwadratur
	gauleg(x1, x2, x, w,n);
	// for(int i = 1; i <= n; i++){
	// 	printf("x[%d] = %g\tw[%d] = %g\n", i, x[i], i, w[i]);
	// }
	float value_1 = 0;
	for(int k = 1; k <= n; k++){
		value_1 += w[k]*fun_1(x[k]);
	}
	printf("value_1 = %g\t value_1_a = %g\n", value_1, integral_1(x1, x2));
	free_vector(x,1,n);
	free_vector(w,1,n);

	//for plotting
	FILE *file1 = fopen("fun1", "w");
	float i = x1;
	while (i <= x2){
		fprintf(file1, "%g\t%g\n", i, fun_1(i));
		i += (x2-x1)/100.0;
	}
	fclose(file1);
	//************ Integral 2 ************
	x1 = 0.0;
	x2 = 20.0;
	n = 10;
	x = vector(1,n);
	w = vector(1,n);

	// wyznaczenia położenia węzłów i współczynników kwadratur
	gaulag(x, w, n, 0);
	// for(int i = 1; i <= n; i++){
	// 	printf("x[%d] = %g\tw[%d] = %g\n", i, x[i], i, w[i]);
	// }
	float value_2 = 0;
	for(int k = 1; k <= n; k++){
		value_2 += w[k]*fun_2(x[k], 5);
	}
	printf("value_2 = %g\t value_2_a = %g\n", value_2, integral_2(5));
	free_vector(x,1,n);
	free_vector(w,1,n);

	//************ Integral 3 ************
	x1 = 0.0;
	x2 = 30.0;
	n = 10;
	x = vector(1,n);
	w = vector(1,n);

	// wyznaczenia położenia węzłów i współczynników kwadratur
	gauher(x, w, n);

	float value_3 = 0;
	for(int k = 1; k <= n; k++){
		for(int l = 1; l <= n; l++){
			value_3 += w[l]*w[k]*fun_3(x[k], x[l]);
		}	
	}
	printf("value_3 = %g\t value_3_a = %g\n", value_3, integral_3());


	free_vector(x,1,n);
	free_vector(w,1,n);

	return 0;
}


/*

gauleg(float x1,float x2, float x[],float w[],int n)
	gdzie: x1-dolna granica całkowania, x2 - górna granica całkowania, x[] - wektor zawierający
	położenia węzłów kwadratury, w[] - współczynniki kwadratury, n - liczba wezłów kwadratury

gaulag(float x[],float w[],int n,float alfa)
	gdzie: x[] - wektor zawierający położenia węzłów kwadratury, w[] - współczynniki kwadratury,
	n - liczba wezłów kwadratury, alfa - parametr stowarzyszonego wielomianu Laguerre’a (przyjąć
	alfa=0)

gauher(float x[],float w[],int n)
	gdzie: x[] - wektor zawierający położenia węzłów kwadratury, w[] - współczynniki kwadratury, n
	- liczba wezłów kwadratury
*/