#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "brent.h"

#define numerador(x0,fx1,fm) x0*fx1*fxm
#define denominador(fx0,fx1,fxm) (fx0 - fx1 )*( fx0 - fxm )
#define parcela(x0,fx0,fx1,fxm) numerador(x0,fx1,fxm)/denominador(fx0,fx1,fxm)
#define calc_inv(fx0,fx1,fxm,x0,x1,xm)	(parcela(x0,fx0,fx1,fxm) + parcela(x1,fx1,fx0,fxm) +parcela(xm,fxm,fx0,fx1))
#define secante(a,b,fa,fb) (b-(fb*((b-a)/(fb-fa))))

double brent (double x0, double x1, int p, double(*f) (double x)){

	double precision = 5 * pow((double)10,-p);
	double xm =0,fx0,fx1,fxm,x2,fx2,erro,modulo,mod1,trap;
	int usou = 0;
	xm = (x0 +x1)/2;
	fxm = f(xm);
	trap = fabs(fxm);
	while(fabs(fxm) > precision ){

		//printf("__fxm:%g___precision:%g\n",fabs(fxm),precision);
		
		if(usou && (fabs(trap - fabs(fxm)) < precision) ){
			//Não convergirá
			printf("Nao convergiu a f(x)=0\n");
			break;
		}
		else{
			trap = fxm;
		}
		fx0 = f(x0);
		fx1 = f(x1);
		usou = 0;
		/////IQI
		x2 =(double) calc_inv(fx0,fxm,fx1,x0,xm,x1) ;
		erro = fabs(f(xm));
		fx2= f(x2);
		//Testando f(IQI)
		if (fabs(f(x2)) < erro){
			modulo = fabs((x0-x1));
			if(fx0 *fx2 < 0){
				mod1 = fabs((x0-x2));	
				if(mod1/modulo <=0.5){
					x0 = x2;
					usou =1;

				}
			}
			else{
				mod1 = fabs(x1-x2);
				if(mod1/modulo <=0.5){
					x1=x2;
					usou = 1;

				}
			}
		}

		if (!usou){
			x2 = (double) secante(x0,x1,fx0,fx1); 
			//Testando f(secante)
			if (f(x2) < erro){
			modulo = fabs((x0-x1));
			if(fx0 *fx2 < 0){
				mod1 = fabs((x0-x2));
				if(mod1/modulo <=0.5){
					x1 = x2;
					usou =1;
				}
			}
			else{
				mod1 = fabs(x1-x2);
				if(mod1/modulo <=0.5){
					x0=x2;
					usou = 1;
				}
			}
		}

		}
		if(!usou){
			//usa xm
			if(fx0 *fxm < 0){
				x1=xm;
				usou = 1;
			}
			else{
				x0=xm;
				usou = 1;
			}

		}

		xm = (x0 +x1)/2;
		fxm = f(xm);
	}
//printf("__fxm:%g___precision:%g\n",fxm,precision);
//printf("__x1:%g___x2:%g___fxm:%g\n",x0,x1,fxm);
return xm;
}