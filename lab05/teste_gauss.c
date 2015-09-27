#include <string.h>
#include <stdio.h>
#include "matriz.h"
#include <stdlib.h>
#include "gauss.h"


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
int main(){
	int i,j,n=3;
	double **P,** B, ** A = mat_cria(3,3);
	double *bA, *bB;

    /*---------------------------------------
				RESOLVE A
    ---------------------------------------*/
    copiaM(3,A,A1);

    bA = malloc(sizeof(double)*3);
    copiaV(3,bA,bA1);

    printf("Areas de Mem Usadas A:%p_ A1:%p ",A,A1);

	teste_imprimi (3,3,A);

	printf("_LINHA:%d\n",__LINE__ );

	P = fatoracao(3, A);

	printf("_LINHA:%d\n",__LINE__ );

	teste_imprimi (3,3,A);

	printf("_LINHA:%d\n",__LINE__ );

	substituicao(3, A, P, bA);


	printf("_LINHA:%d\n",__LINE__ );

	mat_libera(3,A);
	/*---------------------------------------
				RESOLVE B
    ---------------------------------------*/
	B = mat_cria(6,6);

	copiaM(6,B,B1);

    printf("Areas de Mem Usadas B:%p_ B1:%p ",B,B1);

	teste_imprimi (6,6,B);

	printf("_LINHA:%d\n",__LINE__ );

	fatoracao(6, B);

	printf("_LINHA:%d\n",__LINE__ );

	teste_imprimi (6,6,B);

	printf("_LINHA:%d\n",__LINE__ );



	return 0;
}