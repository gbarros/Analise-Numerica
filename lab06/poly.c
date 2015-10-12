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

	double numerador = 1, resposta=0,
	*X, *Y;
	int i,j;
	X =s->x ;
	Y =s->y ;

	for (i=0;i<s->n;i++){
		
		for(j=0;j<s->n;j++){
			if( i != j)
				numerador = numerador * (x-X[j]);
		}
		//Divide o numerador calculado pelo den[i]
		//Multiplica tal valor por Y[i]  e salva no resposta
		numerador = (numerador/den[i])*Y[i];
		resposta += numerador;
		numerador = 1;
	}
	return resposta;
}

/* programacao dinamica para resolver em menos passos*/
double f_calc(double** f, char** setF, Sample* s, int inicio, int fim){
 	double partA, partB;
	if(inicio == fim )
		return s->y[inicio];

	if(setF[inicio][fim] == 1)
		return f[inicio][fim];
	partA = f_calc(f, setF, s, inicio+1, fim);
	partB = f_calc(f, setF, s, inicio, fim-1);

	partA -= partB;
	partA = partA/ (s->x[fim] - s->x[inicio]);

	setF[inicio][fim] = 1;
	f[inicio][fim] = partA;
	return partA;


}

double* NewtonCompute(Sample *s){

	double * resposta = (double*) malloc(sizeof(double)* s->n);
	double ** f = (double**) malloc(sizeof(double)* s->n);
	char ** setF = (char**) malloc(sizeof(char)* s->n);
	double *X, *Y;
	int i, j;

	/*Cria e seta espacos da programacao dinamica*/
	for ( i = 0; i < s->n; i++){
		f[i] = (double*) malloc(sizeof(double)* s->n);
		setF[i] = (char**) malloc(sizeof(char)* s->n);
		for (j = 0; i < s->n; j++){
			setF[j] = 0;
		}
	}

	X =s->x ;
	Y =s->y ;

	for ( i = 0; i < s->size; i++){

		resposta[i] = f_calc(f, setF, s, 0, i);
	}

	return NULL;

}

double NewtonEval (Sample *s, double * coef, double x){

	return 0;
}