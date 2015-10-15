#include <string.h>
#include <stdio.h>
#include "matriz.h"
#include <stdlib.h>
#include "gauss.h"


char Vetor[] = "X";
double A1[][3] = {{1,2,-1},{2,1,-2},{-3,1,1}};
int a_size = 3;
double bA1[3] = {3,3,-6};

double B1[][6] = {{3,-1,0,0,0,0.5},{-1,3,-1,0,0.5,0},{0,-1,3,-1,0,0},{0,0,-1,3,-1,0},{0,0.5,0,-1,3,-1},{0.5,0,0,0,-1,3}};
int b_size =6;
double bB1[6] = {2.5,1.5,1,1,1.5,2.5};


void copiaM(int size,double ** d,double s[size][size]){
	int i, j;
	for(i=0;i<size;i++)
		for(j=0;j<size;j++){
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
	for (i=0; i<n;i++){
		for (j=0; j<n;j++){
			printf("%.3g\t",A[i][j]);

		}
        puts("");
	}
	puts("-----"); 
}
void printV(int size, double* x,char* name){
	int i;
	if(name == NULL){
		name = Vetor;
	}
	puts("-----");
	printf("Vetor %s:\n",name );
	for(i=0;i<size;i++)
		printf("[%d]:%g \n",i,x[i]);	
	puts("-----");
}
int main(){
	int i,j,n=3;
	double **P,** B, ** A;
	double *bA, *bB, *x;

    /*---------------------------------------
				RESOLVE A
    ---------------------------------------*/
	puts("========RESOLVE A=======");

	//SETUP
	A = mat_cria(3,3);
    bA = malloc(sizeof(double)*3);
    copiaM(3,A,A1);
    copiaV(3,bA,bA1);

    // Vizualiza Dados
	printM(3,3,A,"A");
	printV(3,bA,"b");


	P = fatoracao(3, A);

	printM(3,3,A,"LU");

	x = substituicao(3, A, P, bA);

	printV(3,x,"Solução de A");


	/*LIMPA*/
	mat_libera(3,A);
	mat_libera(3,P);
	free(bA);
	free(x);


	/*---------------------------------------
				RESOLVE B
    ---------------------------------------*/
	puts("========RESOLVE B=======");
	//SETUP				
	B = mat_cria(6,6);
	bB = malloc(sizeof(double)*6);
	copiaM(6,B,B1);
    copiaV(6,bB,bB1);

    // Vizualiza Dados
	printM(6,6,B,"B");
	printV(6,bB,"b");

	P = fatoracao(6, B);

	printM(6,6,B,"LU");


	x = substituicao(6, B, P, bB);


	printV(6,x,"Solução de B");

	/*LIMPA*/
	mat_libera(3,B);
	mat_libera(3,P);
	free(bB);
	free(x);

	return 0;
}