#include <stdio.h>
#include <stdlib.h>
#include "matriz.h"


//assert: m * n will not be as greater to an overflow
double** mat_cria(int m, int n) 
{
    
	double** mat = calloc(sizeof(double*), m);
	for (m -= 1; m+1; m--) {
	    mat[m] = calloc(sizeof(double), n);
	}
	
	return mat;
}

//assert: A is a valid pointer to a double**
//assert: let i:=0...m,  A[i] is a valid pointer to a double*
void mat_libera(int m, double** A)
{
    for (m-=1;m+1;m--) {
        free(A[m]);
    }
    free(A);
}

//assert: A and T are allocated and same size;
void mat_transposta(int m, int n, double** A, double** T)
{
    int i,j;

    for (i = 0; i < m; i++) {
        for (j = 0; j < n; j++) {
            T[j][i] = A[i][j];
        }
    }
}


//assert: A is a valid pointer to (double**)
//assert: A is a allocated m x n matrix (double**)
//assert: v is a allocated vector of size n
//assert: w is a allocated vector of size m
void mat_multv_spc(int n, Matriz*** A, double* v, double* w) 
{
    int i,j,linha;
    
    for (i = 0; i < m; i++) {
        w[i] = 0.0;
        linha = 0;
        while(A[i][linha]!= NULL){
            j = A[i][linha]->j;
            w[i] += A[i][linha]->ele * v[j];
            linha++;
        }

    }
     
}

void mat_multv(int m, int n, double** A, double* v, double* w) 
{
    int i,j;
    
    for (i = 0; i < m; i++) {
        w[i] = 0.0;
        for (j = 0; j < n; j++) {
            w[i] += A[i][j] * v[j];
        }
    }
    
     
}

//assert: A and B are valid pointers to some double**
//assert: let i:=0...m,  A[i] is a valid pointer to a double*
//assert: let i:=0...n,  B[i] is a valid pointer to a double*
void mat_multm(int m, int n,int q, double** A, double** B, double** C) 
{
    int i,jA,jB;
    int colunaA, colunaB;
    double temp;

    C = mat_cria(n,n);
    //Itera por linha de C
    for (i = 0; i < n; i++) {

        k = 0;
        //Itera por coluna de C
        colunaB =0;
        while(k < n){ //A[i][colunaA] != NULL && A[i][colunaA] != NULL
            
            temp = 0;
            colunaA =0;

            //todas as colunas de A 
            while(A[i][colunaA] != NULL){
                
                jA =  A[i][colunaA]->j;
                //jB =  B[jA][colunaB]->j;

                // Acha a coluna de B que é compativel com elemento C[i][k]
                while(B[jA][colunaB++]->j <= k);

                if(B[jA][--colunaB]->j == k){
                    temp += A[i][colunaA]->ele * B[jA][colunaB]->ele;
                }

                colunaA++;
            }

            //colunaA++;
            if(temp != 0){
                add(C,i,k,temp)
             }
        }
    }
         
}

double mat_modulo(int n, double * x){
    double sum =0; 
    for (int i = 0; i < n; ++i){
        sum += x[i];
    }
    return fabs(sum);
}


void teste_imprimi (int m, int n, double** A)
{
	int i,j;

	printf ("\nMATRIZ\n\n");

	for (i=0; i<3;i++)
	{
		for (j=0; j<1;j++)
		{
			printf("%g %g %g\n",A[i][j],A[i][j+1],A[i][j+2]);

		}

	}

		printf ("\n\n\n\n\n");

}


void copiaM(int m,int n,double ** d,double s[m][n]){
    int i, j;

    for(i=0;i<m;i++)
        for(j=0;j<n;j++){
            d[i][j] = s[i][j];
        }
}
void copiaV(int size,double * d,double s[size]){
    int i;
    for(i=0;i<size;i++)
            d[i] = s[i];
}
void printM (int m, int n, double** A,char * name){
    int i=0,j=0;

    puts("-----");
    printf("Matriz %s:\n",name );
    for (i=0; i<m;i++){
        for (j=0; j<n;j++){
            printf("%0.3f\t",A[i][j]);

        }
        puts("");
    }
    puts("-----"); 
}

void printV(int size, double* x,char* name){
    int i;
    puts("-----");
    printf("Vetor %s:\n",name );
    for(i=0;i<size;i++)
        printf("[%d]:%0.3f \t",i,x[i]);    
    puts("");//\n-----");
}