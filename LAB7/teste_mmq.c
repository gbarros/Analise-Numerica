#include "mmq.h"


double A1[][3] = {{1,1,0},{0,1,1},{1,2,1},{1,0,1}};

double b[] = {2,2,3,4};

double amostra[]= {8.0,12.3,15.5,16.8,17.1,15.8,15.2,14.0};

void copiaM(int m,int n,double ** d,double s[m][n]){

	int i, j;

	for(i=0;i<m;i++)
		for(j=0;j<n;j++){
			d[i][j] = s[i][j];
		}
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

/*************************************\	
			Funcao auxiliar
	recebe vetor de valores e faz o calculo 
do vetor 'b' para o problema proposto, isto é,
 b[i] = log(amostra[t]) + log(t); i =t-1  
\************************************/

double * log_v(int size, double* amostra){

	double *b = (double*) malloc( sizeof(double)*size);

	for (int i = 0; i < size; i++){
		b[i] = log(amostra	[i]) - log(i+1);
	}
	return b;

}
void am_mat(int m,double ** A ){
	for (int i = 0; i < m; i++){
		A[i][0] = 1;
		A[i][1] = i+1;
	}
}

void print_lin(double start, double stop, double inc, double a, double b){

	printf("\n\nimprimindo os pares (ti,ci)\n");

	while (start <= stop){

		printf("(%g,%g)\n",start, (a*start*exp(b*start)));
		start += inc;
	}
	puts("\n");

}

int main(){
	double ** A, *x, n_residuo;
	double *log_vetorb = NULL;
/******************************/
	
	A = mat_cria(4,3);
	copiaM(4,3,A,A1);
	printM(4,3,A,"A");

	x = mmq ( 4, 3, A, b);
	printV(3,x,"solução");

	n_residuo = norma2 (4, 3, A, b, x);

	printf(" A norma 2 do residuo é:%g\n",n_residuo);
	
	mat_libera(4,A);

/******************************/
	puts("\n\nSegunda Parte\n");
	log_vetorb = log_v(8,amostra);
	A = mat_cria(8,2);
	am_mat(8,A);
	printM(8,2,A,"A");
	printV(8,amostra,"amostra");

	x = mmq ( 8, 2, A, log_vetorb);
	n_residuo = norma2 (8, 2, A, log_vetorb, x);
	printf(" A norma 2 do residuo é:%g\n",n_residuo);


	printV(2,x,"solução parcial"); // Solucao em funcao de k +bt

	x[0] = exp(x[0]);
	printf("a = %g, b = %g\n", x[0],x[1]);

	print_lin(0.0,16.0,0.1,x[0],x[1]);



	return 0;
}