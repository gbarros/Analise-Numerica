#include "poly.h"

void print_sample(Sample* a){
	int i,n;

	puts("=======\n");

	printf("Printing Sample of size:%d\n",a->n );

	n = a->n; 
	for(i=0;i<n;i++){

		printf("X(%d):[%g] Y(%d):[%g] \n",i, a->x[i],i,a->y[i] );
	}
	puts("=======\n\n");
}
double xy(double a){
	return a;
}

double * criaValordeTeste(int num_amostras, double menor, double maior){

	double * resposta = (double*) malloc(sizeof(double)*num_amostras), inc, base;
	int i;
	inc = fabs(maior - menor)/num_amostras;
	base = menor;

	for(i=0; i<num_amostras;i++){
		resposta[i] = base;
		base += inc;
	}


	return resposta;
}

int fat(int n){
	if (n ==1)
		return 1;
	return n*fat(n-1);
}

double calcErroChebyshev(int n, int menor, int maior, double varlor){
	double temp;
	temp = (maior - menor)/2;
	temp = pow(temp, n) / pow(2, n-1);
	

}


int main(){

	Sample *test = Chebyshev(6,0.0,M_PI/2,cos);
	double *denominadores = LagrangeCompute(test);
	double *valoresTeste = criaValordeTeste(6,0.0,M_PI/2);
	double *coeficientes = NewtonCompute(test);;
	int i; 


	print_sample(test);

	puts("");
	for (i = 0; i < test->n; i++){
		printf("den[%d]: %g  ",i,denominadores[i]);
	}
	puts("");
	for (i = 0; i < test->n; i++){
		printf("coeficientes[%d]: %g  ",i,coeficientes[i]);
	}

	puts("\n\n");


	for (i = 0; i < test->n; i++){
		printf("ValorX: %g  \tY_real: %g\tY_Newton: %g\n", valoresTeste[i],cos(valoresTeste[i]), NewtonEval(test, coeficientes, valoresTeste[i]) );
	}

 //LagrangeEval(test, denominadores, valoresTeste[i])
	return 0;
}