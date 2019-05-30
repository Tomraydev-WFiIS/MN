#include<stdio.h>
#include<gsl/gsl_linalg.h>
#include<gsl/gsl_fft_complex.h>
#include<gsl/gsl_errno.h>
#include<math.h>


double get_f0(double t, double omega){
    return sin(omega * t) + sin(2*omega*t) + sin(3*omega*t);
}

double get_gauss(double t, double sigma){
    return (1.0 / (sigma * sqrt(2*M_PI) )) * pow(M_E, -(t*t) / (2*sigma*sigma) );
}

int main(void){
    double T = 1.0;
    double t_max = 3*T;
    double omega = 2*M_PI/T;
    double sigma = T / 20.0;

    FILE *file1 = fopen("niezaburzony.dat", "w");
    FILE *file2 = fopen("zaburzony.dat", "w");

    for(int k = 8; k <=12; k+=2){
        int N = pow(2,k);
        double dt = t_max / N;
        double f0[2*N];
        double f1[2*N];
        double f[2*N];
        double g1[2*N];
        double g2[2*N];
        double DELTA;
        for(int i = 0; i < N; i++){
            f0[2*i] = get_f0(i*dt, omega);
            f0[2*i+1] = 0;
            DELTA = (rand() / (RAND_MAX + 1.0)) - 0.5;
            f[2*i] = f0[2*i] + DELTA;
            f[2*i+1] = 0;
            f1[2*i] = f[2*i];
            f1[2*i+1] = 0;
            // printf("%g\t%g\n", f0[2*i], f[2*i]);
            g1[2*i] = get_gauss(i*dt, sigma);
            g1[2*i+1] = 0;
            g2[2*i] = get_gauss(i*dt, sigma);
            g2[2*i+1] = 0;
            // printf("%g\t%g\t%g\n", dt*i, g1[2*i], g2[2*i]);
        }
        //2. obliczyc transformaty
        gsl_fft_complex_radix2_forward(f, 1, N); //przyjmujemy stride = 1
        gsl_fft_complex_radix2_forward(g1, 1, N);
        gsl_fft_complex_radix2_backward(g2, 1, N);
        //3. obliczyc transformate splotu
        for(int i = 0; i <N; i++){
            double a1 = f[2*i];
            double b1 = f[2*i + 1];
            double a2 = g1[2*i] + g2[2*i];
            double b2 = g1[2*i + 1] + g2[2*i + 1];
            f[2*i] = a1*a2 - b1*b2;
            f[2*i+1] = a1*b2 + a2*b1;
        }
        //4. Dla tablicy f: wykonujemy odwrotną transformatę.
        gsl_fft_complex_radix2_backward(f, 1, N);
        //5.  Spośród rzeczywistych elementów tablicy f wyszukujemy elementu o maksymalnym module
        double f_max = abs(f[0]);
        for(int i = 0; i < N; i++){
            if(abs(f[2*i]) > f_max){ f_max = abs(f[2*i]);}
        }
        //6. Wypisujemy do pliku
        
        for(int i = 0 ; i < N; i++){
            fprintf(file1, "%g\t%g\t%g\n", i*dt, f0[2*i], f[2*i] * 2.5/f_max);
        }
        fprintf(file1,"\n\n");
        
        for(int i = 0 ; i < N; i++){
            fprintf(file2, "%g\t%g\t%g\n", i*dt, f1[2*i], f[2*i] * 2.5/f_max);
        }
        fprintf(file2,"\n\n");
     }

    fclose(file1);
    fclose(file2);
    return 0;
}