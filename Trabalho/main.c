
#include "matriz.h"

Matriz *** JacobiPC(Matriz***A, int n ){
    int i,colunaA, jA;
    Matriz*** M = mat_cria(n,n);         //Pre condicionador M

    for (i=IDX;i<n+IDX;i++){

        for(colunaA=IDX;A[i][colunaA] !=NULL; colunaA++){

            jA =  A[i][colunaA]->j;

            if(jA == i){
                add(M,i,jA, 1/A[i][colunaA]->ele);
                break;
            }
        }
    }
    return M;

}
 
Matriz *** pre_cond(Matriz*** A, int n, double w)
{
    int i;
    Matriz*** M = mat_cria(n,n);         //Pre condicionador M
    Matriz*** Mt = mat_cria(n,n);        //Matriz temporaria auxiliar
    Matriz*** L = mat_cria(n,n);         //Matriz triangular inferior
    Matriz*** U = mat_cria(n,n);         //Matriz triangular superior
    Matriz*** D = mat_cria(n,n);         //Matriz diagonal
    Matriz*** DwL = mat_cria(n,n);      //D + wL
    Matriz*** DwU = mat_cria(n,n);      //D + wU
    
        
    //SSOR e GAUSS SEIDEL

    mat_fatora(n,A, L, U, D); 
        
    // Calcula (D+wL) e (D+wU)
   
   //D+ wL 
    mat_multescalar(n,L, w);
    mat_sumM(n, D, L, DwL);
   //D+ wU      
    mat_multescalar(n,U, w);
    mat_sumM(n, D, U, DwU);
                
    
    //Calcula D-1
    for (i=IDX;i<n+IDX;i++)
    {
        D[i][1]->ele = 1.0/D[i][1]->ele;
       
    }            
              
    //D-1(D+wU)     
    mat_multm(n, DwL, D, Mt);
    
    ////(D+wL)[D-1(D+wU)]
    mat_multm(n,Mt, DwU, M);
    
                  
    mat_libera(n, D);
    mat_libera(n, L);
    mat_libera(n, U);       
          
    return M;       
            
}

int ConjugateGradient(int n, Matriz ***A, double* b, double *x, double tol){
    double * Rk, *Rk1, *Dk, *temp;
    double Alfa, Beta;
    int i;

    Rk = (double*) calloc(n+IDX,sizeof(double));
    Rk1 = (double*) calloc(n+IDX,sizeof(double));
    Dk = (double*) calloc(n+IDX,sizeof(double));
    temp = (double*) calloc(n+IDX,sizeof(double));

    // D0 = R0= b - Ax;
    mat_multv(n,A,x,temp); mat_sumV(n, -1, b, temp,Rk); copiaV(n,Dk,Rk);

    // For K= 0...n-1
    for (i = IDX; i < n+IDX; ++i){
        
        // if (Rk = 0) stop
        if(mat_modulo(n, Rk) < 0.5*pow(10,-tol)) break; 

        // Alfa = RkT*Rk / DkT * A *Dk
        mat_multv(n,A,Dk,temp); Alfa = mat_escalar_vu(n,Rk,Rk)/ mat_escalar_vu(n,temp,Dk);

        // Xk1 = Xk + Alfa*Dk
        mat_sumV(n,Alfa,x,Dk,x);

        //Rk1 = Rk - Alfa * A* Dk ;; Obs: temp já contém A*Dk
        mat_sumV(n, -1*Alfa,Rk,temp,Rk1);


        //Beta = Rk1T * Rk1 / RkT * Rk
        Beta = mat_escalar_vu(n,Rk1,Rk1) / mat_escalar_vu(n,Rk,Rk);

        //Dk1 = Rk1 + Beta*Dk
        mat_sumV(n,Beta,Rk1,Dk,Dk);

        //Atualiza o Rk
        copiaV(n,Rk,Rk1);

    }

    free(Rk);
    free(Rk1);
    free(Dk);
    free(temp);
    return i-IDX;
}

int ConjugateGradientPC(int n, Matriz ***A,Matriz ***M, double *b, double *x, double tol){

    double * Rk, *Rk1, *Dk, *temp, *w;
    double Alfa, Beta,y;
    int i;

    Rk = (double*) calloc(n+IDX,sizeof(double));
    Rk1 = (double*) calloc(n+IDX,sizeof(double));
    Dk = (double*) calloc(n+IDX,sizeof(double));
    temp = (double*) calloc(n+IDX,sizeof(double));
    w = (double*) calloc(n+IDX,sizeof(double));

    //R0= b - Ax;
    mat_multv(n,A,x,temp); mat_sumV(n, -1, b, temp,Rk);

    //D0 = M_inv * R0 ou M*D0 = R0
    ConjugateGradient(n,M,Rk,Dk,tol+1);

    ///Para a 1a vez o y eh diferente, muda o calculo de alpha
    y = mat_escalar_vu(n,Rk,Dk);

    // For K= 0...n-1
    for (i = IDX; i < n+IDX; ++i){
        
       // puts("A1");
        // if (Rk = 0) stop
        if(mat_modulo(n, Rk) < 0.5*pow(10,-tol)) break; 
       // puts("A2");
        // Alfa = RkT*(Dk ou W) / DkT * A *Dk
        mat_multv(n,A,Dk,temp); Alfa = y/ mat_escalar_vu(n,temp,Dk);

        // Xk1 = Xk + Alfa*Dk
        mat_sumV(n,Alfa,x,Dk,x);

        //Rk1 = Rk - Alfa * A* Dk ;; Obs: temp já contém A*Dk
        mat_sumV(n, -1*Alfa,Rk,temp,Rk1);

        ////w = M_inv * R0 ou M*w = R0
        ConjugateGradient(n,M,Rk,w,tol+1);
        
        ///
        y = mat_escalar_vu(n,Rk1,w);

        //Beta = Rk1T * w / RkT * Rk
        Beta = y / mat_escalar_vu(n,Rk,Rk);

        //Dk1 = w + Beta*Dk
        mat_sumV(n,Beta,w,Dk,Dk);

        //Atualiza o Rk
        copiaV(n,Rk,Rk1);

    }

    free(Rk);
    free(Rk1);
    free(Dk);
    free(temp);
    free(w);
    return i-IDX;

}

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
        i = ConjugateGradient(n, A, b, x,tol);
        printf("\n\ti = %d \t\n",i );




        /******Jacobi*********/
        
                //Redefinição de x[] para estimativa inicial vetor nulo
                for(int i =IDX; i< n+IDX; i++) x[i]=0;
                
                // Matriz pre condicionador de Jacobi  
                M = JacobiPC(A, n);
                //Minv Ax = Minv b/
                N = mat_cria(n,n);
                mat_multm(n,M,A,N);
                mat_multv(n, M, b, bbarra);
                
                printf("\n\tMetodo gradiente Conjugado com pre condicionador de Jacobi , n= %d \n",n );


                // Metodo gradiente Conjugado com pre condicionador de Jacobi , n= 1000
                i = ConjugateGradient(n, N, bbarra, x,tol);
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

    for(n=100; n<=10000;n=n*10){
        A = mat_esparsa_extend(n);
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
        i = ConjugateGradient(n, A, b, x,tol);
        printf("\n\ti = %d \t\n",i );




        /******Jacobi*********/
        
                //Redefinição de x[] para estimativa inicial vetor nulo
                for(int i =IDX; i< n+IDX; i++) x[i]=0;
                
                // Matriz pre condicionador de Jacobi  
                M = JacobiPC(A, n);
                //Minv Ax = Minv b/
                N = mat_cria(n,n);
                mat_multm(n,M,A,N);
                mat_multv(n, M, b, bbarra);
                
                printf("\n\tMetodo gradiente Conjugado com pre condicionador de Jacobi , n= %d \n",n );


                // Metodo gradiente Conjugado com pre condicionador de Jacobi , n= 1000
                i = ConjugateGradient(n, N, bbarra, x,tol);
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

