#include "simpson.h"

double first(double x){

	return x/sqrt(x*x + 9);
}

double second(double x){

	return (x*x)*log(x);
}

double third (double x){
	return (x*x)*sin(x);
}


int main(){
	double result, teto,base, real;
	double tol = 0.5e-5;

	teto = 1+tol; //100% + tol 
	base = 1-tol; //100% - tol 

	result = AdaptiveSimpson(0,4,first,tol);
	real = 2.0;

	printf("[%s] the result was: %0.15f\n",((result<real*teto)&&(result>real*base))?"Success":"Fail",result );
	

	result = AdaptiveSimpson(1,3,second,tol);
	real = 6.9986217091241;

	printf("[%s] the result was: %0.15f\n",((result<real*teto)&&(result>real*base))?"Success":"Fail",result );

	result = AdaptiveSimpson(0,M_PI,third,tol);
	real = 5.8696044010894;

	printf("[%s] the result was: %0.15f\n",((result<real*teto)&&(result>real*base))?"Success":"Fail",result );

	return 0;
}