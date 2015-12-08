#include <math.h>
#include <stdio.h>
#include <stdlib.h>



double **mat_cria (int m, int n);

void mat_libera(int m, double** A);

void mat_transposta(int m, int n, double** A, double** T);

void mat_multv (int m, int n, double** A, double* v, double* w);

void mat_multm (int m, int n, int q, double** A, double** B, double** C);

double mat_modulo(int n, double * x);

void teste_imprimi (int m, int n, double** A);

void copiaM(int m,int n,double ** d,double s[m][n]);

void copiaV(int size,double * d,double s[size]);

void printM (int m, int n, double** A,char * name);

void printV(int size, double* x,char* name);