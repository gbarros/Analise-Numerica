#include "poly.h"


Sample * Chebyshev (int n, double a, double b, double (*f) (double x)){

	int i,beta;
	double  *X, *Y;
	double fat1, fat2; 
	Sample * answer = malloc(sizeof(Sample));
	answer->n=n;
	answer->x = malloc(sizeof(double)*n);
	answer->y = malloc(sizeof(double)*n);
	Y = answer->y;
	X = answer->x;
	
	i=0;
	fat1 = (b-a)/2;
	fat2 = (b+a)/2;
	beta = 1; 

	while(i<n){
		
		X[i] = fat1* cos((beta*M_PI)/(2*n)) + fat2;
		Y[i] = f(X[i]);

		i++;
		beta +=2;
	}


	return answer;
}



double * LagrangeCompute (Sample * s){

	double * den = (double *) malloc (sizeof(double));
	double den_temp =1, *X =s->x ;
	int i,j;

	for (i=0;i<s->n;i++){
		den_temp = 1;
		for(j=0;j<s->n;j++){
			if( i != j)
				den_temp = den_temp * (X[i] - X[j]);
		}
		den[i] = den_temp;
	}

	return den;
}

double LagrangeEval(Sample* s, double* den, double x){


	return 0;
}

double* NewtonCompute(Sample *s){

	return NULL;

}

double NewtonEval (Sample *s, double * coef, double x){

	return 0;
}