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



int main(){

	Sample *test = Chebyshev(6,0.0,M_PI/2,cos);
	double *denominadores = LagrangeCompute(test);
	double *valoresTeste = criaValordeTeste(6,0.0,M_PI/2);
	int i;

	print_sample(test);

	puts("");
	for (i = 0; i < test->n; i++){
		printf("den[%d]: %g  ",i,denominadores[i]);
	}
	puts("");

	for (i = 0; i < test->n; i++){
		printf("ValorX: %g\t Y_real: %g\tY_Lagrange: %g\n", valoresTeste[i],cos(valoresTeste[i]), LagrangeEval(test, denominadores, valoresTeste[i]) );
	}


	return 0;
}