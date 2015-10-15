#include "mmq.h"




double* gauss(int n, double **A, double *b){
	
	double ** P = fatoracao(n,A);
	
	double * result = substituicao(n,A,P,b);

	mat_libera(n,P) ;

	return result;


}



double* mmq ( int m, int n, double** A, double* b){

	double ** AtA,*x;
	// calcula a transposta
	double ** At = mat_cria(n,m);

	mat_transposta(m, n, A, At);

	// multiplica At.A
	AtA = mat_cria(n,n);
	mat_multm(n,m,n,At,A,AtA);

	// passa o gauss 


	puts("uhum");

	x = gauss(n,AtA,b);


	puts("uhum");
	
	// retorna x

	mat_libera(n,At);
	mat_libera(n,AtA);



	return x;
}

double norma2 (int m, int n, double** A, double* b, double* x){

	double * Ax = (double *) malloc (m* sizeof(double));
	double r, temp;
	int i;

	// multiplica A por x
	mat_multv(m,n,A,x,Ax);
	// subtrai b[i] de Ax[i]
	r =0;
	for (i=0;i<m;i++){
		// guarda o quadrado do resultado
		temp = b[i] - Ax[i];
		r += pow(temp,2);
	}
	//tira sqrt 
	return sqrt(r);

}
