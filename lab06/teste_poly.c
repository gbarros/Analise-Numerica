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

int main(){

	Sample *test = Chebyshev(6,0.0,M_PI/2,cos);
	double *denominadores = LagrangeCompute(test);
	int i;

	print_sample(test);

	puts("");
	for (i = 0; i < test->n; i++){
		printf("den[%d]: %g  ",i,denominadores[i]);
	}
	puts("");

	return 0;
}