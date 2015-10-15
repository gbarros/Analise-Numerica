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

void log_v(int size, double* amostra, double*b){

	b = (double*) malloc( sizeof(double)*size);

	for (int i = 0; i < size; i++){
		b[i] = log(amostra	[i]) - log(i+1);
	}

}
void am_mat(int m,double ** A ){
	for (int i = 0; i < m; i++){
		A[i][0] = 1;
		A[i][1] = i+1;
	}
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
	log_v(8,amostra,log_vetorb );
	A = mat_cria(8,2);
	am_mat(8,A);
	printM(8,2,A,"A");

	puts("coisa");
	x = mmq ( 8, 2, A, log_vetorb);
	puts("aaaaa");
	//n_residuo = norma2 (8, 2, A, log_vetorb, x);
	printf(" A norma 2 do residuo é:%g\n",n_residuo);


	printV(2,x,"solução parcial"); // Solucao em funcao de k +bt

	x[0] = exp(x[0]);
	printf("a = %g, b = %g\n", x[0],x[1]);




	return 0;
}