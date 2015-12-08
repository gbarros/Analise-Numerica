int main(){
	
	double *x,*b, *bbarra;
    int n =100, i, tol =5;
    Matriz*** A, ***M, ***N;

    for(n=100; n<=10000;n=n*10){
    	A = mat_esparsa(n);
    	x = (double*) calloc(n+IDX,sizeof(double));
    	b = (double*) calloc(n+IDX,sizeof(double));
    	bbarra = (double*) calloc(n+IDX,sizeof(double));
    
    	//Vetor solução
	    for(int i =IDX; i< n+IDX; i++)
	        x[i]=1;
	    
	    // Calculo do vetor b correto obtido atraves de Ax = b
	    mat_multv(n,A,x,b);


    	/*****SEM PRECOND*****/
	    //Redefinição de x[] para estimativa inicial vetor nulo
    	for(int i =IDX; i< n+IDX; i++) x[i]=0;

    	printf("\n\tMetodo gradiente Conjugado com pre condicionador de Sem PreCond , n= %d \n",n );
    	i = ConjugateGradient(n, A, bbarra, x,tol);
    	printf("\n\ti = %d \t\n",i );




    	/******Jacobi*********/
    	
		    	//Redefinição de x[] para estimativa inicial vetor nulo
		    	for(int i =IDX; i< n+IDX; i++) x[i]=0;
		    	
		    	// Matriz pre condicionador de Jacobi  
		    	M = pre_cond(A,n,-1);
		    	//Minv Ax = Minv b/
		    	N = mat_cria(n,n);
		    	mat_multm(n,M,A,N);
		    	mat_multv(n, M, b, bbarra);
		    	
		    	printf("\n\tMetodo gradiente Conjugado com pre condicionador de Jacobi , n= %d \n",n );


		    	// Metodo gradiente Conjugado com pre condicionador de Jacobi , n= 1000
		    	i = ConjugateGradient(1000, N, bbarra, x,5);
		    	printf("\n\ti = %d \t\n",i );


		    	mat_libera(n,M);
		    	mat_libera(n,N);



    	/******Gaus Seidel****/
    	
		    	//Redefinição de x[] para estimativa inicial vetor nulo
		    	for(int i =IDX; i< n+IDX; i++) x[i]=0;
		    	
		    	printf("\n\tMetodo gradiente Conjugado com pre condicionador de GaussSeidel , n= %d \n",n );
		    	
		    	M = pre_cond(A,n,1);

		    	i = ConjugateGradientPC(n, A, M, b, x, tol);
		    	printf("\n\ti = %d \t\n",i );

		    	mat_libera(n,M);


    	/*****  SSOR  *********/
    	//Redefinição de x[] para estimativa inicial vetor nulo
    	for(int i =IDX; i< n+IDX; i++) x[i]=0;
    	
    	printf("\n\tMetodo gradiente Conjugado com pre condicionador de SSOR , n= %d \n",n );
    	
    	M = pre_cond(A,n,1.5);

    	i = ConjugateGradientPC(n, A, M, b, x, tol);
    	printf("\n\ti = %d \t\n",i );

    	mat_libera(n,M);

    		//=======Fim do Loop======//

    	free(x);
    	free(b);
    	free(bbarra);
    	mat_libera(n,A);
    }



}