#include <stdio.h>
#include <math.h>
#include <stdlib.h>




#define Emaq 2.220446049250313e-16


double fx(double x){

	return 1/(1+x);

}

double derivada(double x, double h, double (*f) (double)){

	return (f(x+h)-f(x-h))/(2*h);
}

double erro_teo(double h, double x){


	return ((pow(h,2)/6)*(-6/pow((x+1),4))) + Emaq/h;

}


int main (){

	double dev, dev_analitica, h, erro, teorico;
	int i;
	h = 0.1;

	dev_analitica = -0.25;
	puts("    h\t\t  aproximada\tanalitica\terr_econtrado\terr_teorico");
	for( i=1; i<13;i++){
		dev = derivada(1, h, fx);
		teorico = erro_teo(h, 1);
		erro = dev - dev_analitica; 

		printf(" 1*10^(-%d)\t %0.10f\t %f\t",i, dev,dev_analitica);
		printf("%0.10f\t: %0.10f\n\n",erro,teorico );

		///////IMPRIMIR A MELHOR RESPOSTA

		h = h/10;
	} 
	
	puts("O h que minimiza ambos os erros é 1*10^(-5)");

	return 0;
}