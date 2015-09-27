#include<stdio.h>
#include<math.h>
#include "brent.h"

//4cos(x) -e^2*x 
double fa(double x){
	return 4*cos(x)-exp(2*x);
}
//x/2 - tanx
double fb(double x){
	return x/2 * tan(x);
}
//1-xlog(x+20)
double fc(double x){
	return 1-(x*log10(x+20));
}
//2^x -3*x
double fd(double x){
	return pow(2,x) - 3*x;
}
//x^3 +x -1
double fe(double x){
	return pow(x,3) + x -1;
}

int main (){

	printf("A raiz de_4cos(x) -e^2*x _ eh: %g\n\n",brent(-1,1,6,fa));
	//getchar();

	printf("A raiz de_x/2 - tanx_ eh: %g\n\n",brent(-1,1,6,fb));
	//getchar();
	printf("A raiz de_1-xlog(x+20)_ eh: %g\n\n",brent(-1,1,6,fc));
	//getchar();
	
	printf("A raiz de_2^x -3*x_ eh: %g\n\n",brent(-1,1,6,fd));
	//getchar();
	printf("A raiz de_x^3 +x -1_ eh: %g\n\n",brent(-1,1,6,fe));
	//getchar();


}