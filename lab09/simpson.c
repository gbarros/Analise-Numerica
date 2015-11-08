#include "simpson.h"

double Simpson (double a, double b, double (*f) (double x)){

	double fa, fb, fc,c;
	fa =  f(a);
	fb = f(b);
	c = (a+b)/2;
	fc = f(c);

	fa += fb;
	fa += 4*fc; 
	return ((b-a)/6)*fa;

}

double DoubleSimpson (double a, double b, double (*f) (double x)){
	double sac, c;
	c = (a+b)/2;
	sac = Simpson(a,c,f);
	sac += Simpson(c,b,f);

	return sac;
}

double AdaptiveSimpson (double a, double b, double (*f) (double x), double tol){

	double sab, sacb, c;
	if(tol == 0){
		puts("[Warning] Machine Precision has been reached");
		return DoubleSimpson(a,b,f);
	}
	sab = Simpson(a,b,f);
	sacb = DoubleSimpson(a,b,f);

	if(fabs(sab -sacb) < tol*15 ){
		//printf("\t dif: %0.7f 15*tol: %0.7f\n",sab-sacb,15*tol);
		return sacb;
	}
	c = (a+b)/2;

	sacb = AdaptiveSimpson(a,c,f,tol/2);
	sacb += AdaptiveSimpson(c,b,f,tol/2);

	return sacb;

}