#include <stdio.h>
#include <math.h>
#include <stdlib.h>





double fa (double x){

	return x/sqrt(pow(x,2)+9);

}

double fb(double x){

	return x*x*log(x);

}

double fc(double x){

	return pow(x,2)*sin(x);

}

double simpson(double a, double b, double m, double (*f) (double)){

	double h = (b-a)/(2*m), resposta = 0, x;
	int i;

	resposta = f(a) + f(b);
	x = a;

	for( i = 1 ; i <= 2*m; i++ ){

		x += h;

		if(i%2){
			
			resposta += 4*f(x); 

		}
		else{

			resposta += 2*f(x);
		}
	}

	return resposta * h/3;
}

double pmedio(double a, double b, double m, double (*f) (double)){

	double h = (b-a)/(m), resposta = 0, x;
	int i;

	x = a;

	for( i = 1 ; i <= m; i++ ){

	
		resposta += f((2*x - h)/2) ; //f(x-(h/2))
		//printf("=====%0.6f___%0.6f\n",(2*x - h)/2,f((2*x - h)/2) );
		x += h;
	}

	return resposta * h;
}


int main(){

	puts("\tSimpson:    Ponto Medio:");
	puts("====1a integral =====");
	printf("S_16: %0.6f\t M_16: %0.6f\n",simpson(0,4,16,fa), pmedio(0,4,16,fa));
	printf("S_32: %0.6f\t M_32: %0.6f\n",simpson(0,4,32,fa), pmedio(0,4,32,fa));


	puts("====2a integral =====");
	printf("S_16: %0.6f\t M_16: %0.6f\n",simpson(1,3,16,fb), pmedio(1,3,16,fb));
	printf("S_32: %0.6f\t M_32: %0.6f\n",simpson(1,3,32,fb), pmedio(1,3,32,fb));

	puts("====3a integral =====");
	printf("S_16: %0.6f\t M_16: %0.6f\n",simpson(0,M_PI,16,fc), pmedio(0,M_PI,16,fc));
	printf("S_32: %0.6f\t M_32: %0.6f\n",simpson(0,M_PI,32,fc), pmedio(0,M_PI,32,fc));


	return 0;
}