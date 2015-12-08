#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "matriz.h"


double A0[][2] = {{3,1},{1,2}};
double A1[][6] = {{3,-1,0,0,0,0.5},{-1,3,-1,0,0.5,0},{0,-1,3,-1,0,0},{0,0,-1,3,-1,0},{0,0.5,0,-1,3,-1},{0.5,0,0,0,-1,3}};

double b0[] = {5,5};
double b1[] = {2.5,1.5,1,1,1.5,2.5};


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
			printf("%.3g\t",A[i][j]);

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
		printf("[%d]:%g \n",i,x[i]);	
	puts("-----");
}

double norma2(int size, double *x0, double* x1){
	double sum = 0, dif;

	while(size--){
		dif = fabs(x0[size] - x1[size]);
		sum += dif * dif;
	}
	return sqrt(sum);
}

void extract_LpU(int n, double ** A, double ** LpU){
	int i, j;

	for(i=0;i<n;i++)
		for(j=0;j<n;j++){
			if(i==j){
				LpU[i][j] = 0;
			}else{
				LpU[i][j] = A[i][j];
			}
		}
} 

void mat_Dinv (int n, double **A, double **Dinv){

	while(n--){
		Dinv[n][n] = 1/(A[n][n]);
	}
}
// temp = x - temp;
void subV(int n, double *x, double *temp ){
	while(n--)
		temp[n]= x[n] - temp[n];
}


int Jacobi(int n, double** A, double* b, double* x, double tol){
	int ite =0;
	double * x0 = (double *) malloc(n*sizeof(double));
	double * temp = (double *) malloc(n*sizeof(double));
	double ** LpU = mat_cria(n,n);
	double ** Dinv = mat_cria(n,n);

	/*inicializa*/
	extract_LpU(n,A,LpU);
	mat_Dinv (n, A, Dinv);

	do{
		copiaV(n, x0,x);
		mat_multv(n,n,LpU,x0,temp);
		subV(n,b,temp);
		mat_multv(n,n,Dinv,temp,x);
		ite++;
	}while (norma2(n,x0,x) > tol);

	free(x0);
	free(temp);
	mat_libera(n,LpU);
	mat_libera(n,Dinv);

	return ite; // numero de iterações efetuado
}

int GaussSeidel(int n, double** A, double* b, double* x, double tol){
	int ite =0,i,j;
	double * x0 = (double *) malloc(n*sizeof(double));
	double sum1, sum2;

	do{
		copiaV(n, x0,x);
		for (i = 0; i < n; i++){
			sum1 = 0;
			sum2 = 0;
			for (j = 0; j <= i-1; j++){
				sum1+= A[i][j]*x[j];
			}
			for (j = i+1; j < n; j++){
				sum2+= A[i][j]*x0[j];
			}

			sum1 = b[i] -sum1 -sum2;
			x[i]= sum1/A[i][i];
		}
		ite++;
	}while(norma2(n,x0,x) > tol);

	free(x0);
	return ite; // numero de iterações efetuado
}

 
int SOR(int n, double** A, double* b, double* x, double tol, double w){
	int ite =0,i,j;
	double * x0 = (double *) malloc(n*sizeof(double));
	double sum1, sum2;

	do{
		copiaV(n, x0,x);
		for (i = 0; i < n; i++){
			sum1 = 0;
			sum2 = 0;
			for (j = 0; j <= i-1; j++){
				sum1+= A[i][j]*x[j];
			}
			for (j = i+1; j < n; j++){
				sum2+= A[i][j]*x0[j];
			}

			sum1 = b[i] -sum1 -sum2;
			x[i]= sum1/A[i][i];
		}
		//relaxamento
		for(int j=0;j<n;j++)
			x[j]= w*x[j] +(1-w)*x0[j];
		ite++;
	}while(norma2(n,x0,x) > tol);

	free(x0);
	return ite; // numero de iterações efetuado
}

 
 

int main(){
	double ** A = mat_cria(2,2);
	double * b = (double*) malloc(2*sizeof(double));
	double * x = (double*) malloc(2*sizeof(double));
	double tol = 10e-7;
	int ite;


	/*Teste com o 1º exemplo*/
	puts("Primeiro Sistema\n");
	x[0] = 0;
	x[1] = 0;
	copiaM(2,2,A,A0);
	copiaV(2,b,b0);
	
	ite = Jacobi(2,A,b,x,tol);
	printf("==Jacobi iterações:%d\n",ite);
	printV(2,x,"Solucao");

	x[0] = 0;
	x[1] = 0;
	ite = GaussSeidel(2,A,b,x,tol);
	printf("==GaussSeidel iterações:%d\n",ite);
	printV(2,x,"Solucao");

	x[0] = 0;
	x[1] = 0;
	ite = SOR(2,A,b,x,tol,1.1);
	printf("==SOR iterações:%d\n",ite);
	printV(2,x,"Solucao");

	free(b);
	free(x);
	mat_libera(2,A);  


	/**Teste com o 2º exemplo*/
	A = mat_cria(6,6);
	b = (double*) malloc(6*sizeof(double));
	x = (double*) malloc(6*sizeof(double));

	copiaM(6,6,A,A1);
	copiaV(6,b,b1);

	puts("Segundo Sistema\n");

	for(int i=0;i<6;i++) x[i]=0;
	ite = Jacobi(6,A,b,x,tol);
	printf("==Jacobi iterações:%d\n",ite);
	printV(6,x,"Solucao");

	for(int i=0;i<6;i++) x[i]=0;
	ite = GaussSeidel(6,A,b,x,tol);
	printf("==GaussSeidel iterações:%d\n",ite);
	printV(6,x,"Solucao");

	for(int i=0;i<6;i++) x[i]=0;
	ite = SOR(6,A,b,x,tol,1.1);
	printf("==SOR iterações:%d\n",ite);
	printV(6,x,"Solucao");


	free(b);
	free(x);
	mat_libera(6,A);  
	return 0;
}