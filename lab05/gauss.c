
#include <stdio.h>
#include "matriz.h"
#include "gauss.h"
#include <stdlib.h>

//void troca
void swap(int* a, int *b){
 *a ^= *b;
 *b ^= *a;
 *a ^= *b;
}
double ** fatoracao(int n, double** A){

	double ** P = mat_cria(n,n);
	double fator;
	int i,j,k;
	puts("___fatoração___\n\n");

	/*  PRODUZ IDENTIDADE */
	for(i=0;i<n;i++){
		for(j=0;j<n;j++)
			P[i][j] = 0;
		P[i][i] = 1;
	}
	/*  FATORA L U */
	//processar cada coluna
	for(j=0;j<n;j++){
		 //printf("_LINHA:%d\n",__LINE__ );

		//processar cada elemento da coluna; e
		//atualizar valores da mesma linha que o elemento processado
		for(i=j+1;i<n;i++){
			//printf("+_LINHA:%d\n",__LINE__ );
			//printf("Aij:%g  ",A[0][0] );
			//printf("Ajj:%g\n",A[j][j] );
			fator = A[i][j]/A[j][j];
			//parte onde atualizamos toda linha processada
			for(k=j;k<n;k++){
				//printf("i:%d j:%d k:%d A[i][k]:%g fator:%g A[j][k]:%g mul:%g\n",i,j,k,A[i][k],fator,A[j][k],fator * A[j][k] );
				A[i][k] -= fator * A[j][k];
				

			}
			A[i][j] = fator;
		}
	}
	puts("fim da fatoração \n\n");
	return P;
} 

double * substituicao(int n, double ** A, double** P, double * b){
	double soma,*x,*y = malloc(sizeof(double)*n);
	int i,j,k;
	puts("___subtituição___\n\n");

	// for(i=0;i<n;i++)
	// 	printf("[%d]:%g ",i,b[i]);	
	// puts(" __");
	/*---------------------------------------------
			Atualiza b; b = Pb
	---------------------------------------------*/

	//swap((void*)&y,(void*)&b);
	/*---------------------------------------------
			Encontra Y
	---------------------------------------------*/
	/*ZERA Y*/
	for(i=0;i<n;i++)
		y[i]=0;		
	//Linha a linha
	for(i=0;i<n;i++){
		soma = 0;
		for(j=0;j<=i;j++){
			if(i==j){
				y[i]= b[i] - soma;
			}
			soma += A[i][j]*y[j];
		}
	}
	puts("Y:");
	for(i=0;i<n;i++)
		printf("[%d]:%g ",i,y[i]);	
	puts("");

	/*---------------------------------------------
			Calcula X
	---------------------------------------------*/
	x = malloc(sizeof(double)*n);
	/*ZERA X*/
	for(i=0;i<n;i++)
		x[i]=0;		
	//Linha a Linha
	for(i=n-1;i>=0;i--){
		soma = 0;
		for(j=n-1;j>=0;j--){
			if(i==j){
				x[i] = (y[i] - soma)/A[i][i];
			}
			soma += A[i][j]* x[j];
		}
	}

	puts("x:");
	for(i=0;i<n;i++)
		printf("[%d]:%g ",i,x[i]);	
	puts("");

	free(y);
	puts("fim da substituicao \n\n");
	return x;
}