#include "matriz.h"





double A0[][3] = {{1,-1,0},{-1,2,1},{0,1,2}};
double A1[][3] = {{1,-1,0},{-1,2,1},{0,1,5}};

double b0[] = {0,2,3};
double b1[] = {3,-3,4};


double escalar_vu(int n, double *v, double *u){
	double sum = 0;
	while(n--){
		sum += v[n]*u[n];
	}
	return sum;
}


void sumV(int n, double mul, double *A, double *B, double *Result){
	while(n--){
		Result[n]= A[n] + mul*B[n];
	}
}

void Cholesky(int n, double**A){
	int i,j,k;
	double *uT,**uuT;

	uT = (double*) malloc (sizeof(double)*n);
	uuT = mat_cria(n,n);

	for (k=0;k<n;k++){
		A[k][k] = sqrt(A[k][k]);
		
		// uT = 1/Rkk *Ak,k+1..n
		for (i = k+1; i < n; ++i){

			uT[i] = A[k][i] / A[k][k];
			
		}
		// uuT  = u * uT
		for (i = k+1; i < n; ++i){
			for (j = k+1; j < n; ++j){
				uuT[i][j] = uT[i] * uT[j];
			}
		}
		// A = A-u ; k+1:n,k+1:n
		for(i=k+1;i<n;i++)
			for(j=k+1;j<n;j++)
				A[i][j] -= uuT[i][j];

	}
	for (i = 0; i < n; ++i){
		for (j = 0; j < i; ++j){
			A[i][j] = 0;
		}
	}
	mat_libera(n,uuT);
	free(uT);
}

void ConjugateGradient(int n, double **A, double* b, double *x){
	double * Rk, *Rk1, *Dk, *temp;
	double Alfa, Beta;

	Rk = (double*) malloc(sizeof(double)*n);
	Rk1 = (double*) malloc(sizeof(double)*n);
	Dk = (double*) malloc(sizeof(double)*n);
	temp = (double*) malloc(sizeof(double)*n);

	// D0 = R0= b - Ax;
	mat_multv(n,n,A,x,temp); sumV(n, -1, b, temp,Rk); copiaV(n,Dk,Rk);

	// For K= 0...n-1
	for (int i = 0; i < n; ++i){
		
		// if (Rk = 0) stop
		if(mat_modulo(n, Rk) == 0) break; 

		// Alfa = RkT*Rk / DkT * A *Dk
		mat_multv(n,n,A,Dk,temp); Alfa = escalar_vu(n,Rk,Rk)/ escalar_vu(n,temp,Dk);

		// Xk1 = Xk + Alfa*Dk
		sumV(n,Alfa,x,Dk,x);

		//Rk1 = Rk - Alfa * A* Dk ;; Obs: temp já contém A*Dk
		sumV(n, -1*Alfa,Rk,temp,Rk1);


		//Beta = Rk1T * Rk1 / RkT * Rk
		Beta = escalar_vu(n,Rk1,Rk1) / escalar_vu(n,Rk,Rk);

		//Dk1 = Rk1 + Beta*Dk
		sumV(n,Beta,Rk1,Dk,Dk);

		//Atualiza o Rk
		copiaV(n,Rk,Rk1);

	}

	free(Rk);
	free(Rk1);
	free(Dk);
	free(temp);
}
int main(){
	int n = 3;
	double ** A = mat_cria(n,n);
	double * b = (double*) malloc(sizeof(double)*n);
	double *x =(double*) malloc(sizeof(double)*n);

	/** SISTEMA 1***/
	puts("Sistema 1");
	for (int i = 0; i < n; ++i){
		x[i]=0;
	}

	copiaM(n,n,A,A0);
	copiaV(n,b,b0);

	Cholesky(n,A);

	printM(n,n,A,"R1");

	copiaM(n,n,A,A0);

	ConjugateGradient(n,A,b,x);

	printV(n,x,"Solucao 1");

	/** SISTEMA 2***/
	puts("\n\nSistema 2");


	copiaM(n,n,A,A1);
	copiaV(n,b,b1);

	Cholesky(n,A);

	printM(n,n,A,"R2");

	copiaM(n,n,A,A1);

	ConjugateGradient(n,A,b,x);

	printV(n,x,"Solucao 2");


	return 0;
}
