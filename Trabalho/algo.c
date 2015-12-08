#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#define IDX 1
///ISSO TEM QUE ENTRAR NA MATRIZ.H

typedef struct Mat{

    int j;
    double ele;
}Matriz ;
 
/**************************

 AS FUNCOES ABAIXO JA ESTAO CORRIGIDAS
  PARA O NOVO MODELO DE DADOS

**************************/


///////////////////////////////
//
//    Funcoes internas AUX
//
///////////////////////////////
Matriz*** mat_cria(int m, int n)  //
{
    int size_linha;
    Matriz*** mat = (Matriz***) calloc(n+1,sizeof(Matriz**));
    
    if(n >100){
        size_linha = 100;
    }else{
        size_linha =n;
    }

    for (int i = IDX; i< n+IDX; i++) {
        mat[i] = (Matriz**) calloc(size_linha,sizeof(Matriz*));
    }
    
    return mat;
}
void copiaV(int size,double * d,double s[size]){
    int i;
    for(i=IDX;i<size+IDX;i++)
            d[i] = s[i];
}
void printV(int size, double* x,char* name){
    int i;
    puts("-----");
    printf("Vetor %s:\n",name );
    for(i=IDX;i<size+IDX;i++)
        printf("[%d]:%0.3f \t",i,x[i]);    
    puts("");//\n-----");
}
void add(Matriz*** A, int i, int j, double value){

    int linha = IDX;
    if(value == 0)
        return;

    while(A[i][linha]!= NULL)
        linha++;
    A[i][linha] = (Matriz*) malloc(sizeof(Matriz));
    A[i][linha]->j=j;
    A[i][linha]->ele = value;

}
Matriz *** mat_simples(int n){ //

    Matriz*** mat = mat_cria(n, n);

    for (int i = IDX; i < n+IDX; 
    i++){
        for (int j = IDX; j < n+IDX; j++){
            add(mat,i,j,i+j);
        }
    }
    return mat;
}
Matriz *** mat_um(int n){

    Matriz*** mat = mat_cria(n, n);

    for (int i = IDX; i < n+IDX; i++){
        for (int j = IDX; j < n+IDX; j++){
            add(mat,i,j,1.0);
        }
    }
    return mat;
}
void printComZeros(Matriz ***A,int n){ //
    
    int i,j, colunaA,jA;

    for (i = IDX; i < n +IDX; i++){

        colunaA = IDX;
        jA=IDX;

        for(j =IDX; j<n+IDX; j++){
            
            if(A[i][colunaA]!= NULL)
                jA = A[i][colunaA]->j;
            
            if((A[i][colunaA]!= NULL)&& jA == j){
                printf("%.2f, ",A[i][colunaA]->ele);
                colunaA++;

            }else
            printf("%.2f, ",0.0);
        }

        puts("");
    }

 }

void printSemZeros(Matriz*** A,int n)
 {
    int colunaA;
    for (int i = IDX; i < n + IDX; ++i){
        colunaA =IDX;
        while(A[i][colunaA] != NULL){
            printf("[%d]%g, ",A[i][colunaA]->j,A[i][colunaA]->ele);
            colunaA++;
        }
        puts("");
    }
 }

void printEspacos(Matriz ***A,int n){
    int i,j;

    for (i = IDX; i < n+IDX; i++){
        for(j =IDX; j<n + IDX; j++){
            
            if(A[i][j] == NULL){
                printf("%d, ",0);
            }else
            printf("%d, ",1);
        }
        puts("");
    }
}
Matriz *** mat_id(int n){

    Matriz*** mat = mat_cria(n, n);

    for (int i = IDX; i < n + IDX; ++i){
        add(mat,i,i,1.0);
    }
    return mat;
}

////////////////////////////////
//
//    Funcoes principais
//
///////////////////////////////

//Salva o resultado na propria matriz
void mat_multescalar(int n, Matriz*** A, double escalar){//
    int colunaA;

    for (int i = IDX; i < n + IDX; i++){
        colunaA = IDX;
        while(A[i][colunaA] != NULL){
            A[i][colunaA]->ele = A[i][colunaA]->ele *escalar;
            colunaA++;
        }
    }

}

void mat_sumM(int n, Matriz*** A, Matriz*** B, Matriz ***C){//
    int i,jA,jB, colunaA,colunaB;

    for (i = IDX; i < n + IDX; i++){
        colunaA = IDX;
        colunaB = IDX;
        while( (A[i][colunaA] != NULL) && (B[i][colunaB] != NULL) ){
            jA = A[i][colunaA]->j;  
            jB = B[i][colunaB]->j;

            if( jA < jB){
                add(C,i,jA,A[i][colunaA]->ele);
                colunaA++;

            }else if(jA == jB){
                
                add(C,i,jA,A[i][colunaA]->ele + B[i][colunaB]->ele);
                colunaA++;
                colunaB++;

            }else{
                add(C,i,jB,B[i][colunaB]->ele);
                colunaB++;
            }

        }
        if(A[i][colunaA] == NULL){
            while(B[i][colunaB] != NULL){
                jB = B[i][colunaB]->j;
                add(C,i,jB,B[i][colunaB]->ele);
                colunaB++;
            }

        }else if(B[i][colunaB] == NULL){
            while(A[i][colunaA] != NULL){
                jA = A[i][colunaA]->j;
                add(C,i,jA,A[i][colunaA]->ele);
                colunaA++;
            }

        }
        
    }

}


Matriz*** mat_esparsa(int n){ //

    Matriz*** mat =  mat_cria(n, n);

    int i = IDX;
    //A = mat; 
    // A é um pointer para um vetor de 
    // A* vetor de pointer para um vetor de 
    // A** pointer para elemento Matriz
    // Creio que o uso correto é A[i][i]->j ou ->ele
    for(i =IDX; i<n-2 + IDX;i++){
        add(mat,i,i,i);
        add(mat,i,i+1,0.5);
        add(mat,i,i+2,0.5);
        add(mat,i+1,i,0.5);
        add(mat,i+2,i,0.5);
    }
    add(mat,i,i,i);
    add(mat,i,i+1,0.5);
    add(mat,i+1,i,0.5);
    add(mat,i+1,i+1,i+1);
    
    return mat;
    
}

// Usado para calcular o modulo do residuo, condicao de parada
double mat_modulo(int n, double * x){ //
    double sum =0; 
    for (int i = IDX; i < n + IDX; ++i){
        sum += x[i];
    }
    return fabs(sum);
}

double mat_escalar_vu(int n, double *v, double *u){ //
    double sum = 0;
    n = n +IDX;
    while(n--){
        sum += v[n]*u[n];
    }
    return sum;
}

void mat_sumV(int n, double mul, double *A, double *B, double *Result){ //
    n = n +IDX;
    while(n--){
        Result[n]= A[n] + mul*B[n];
    }
}

void mat_multv(int n, Matriz*** A, double* v, double* w) //
{
    int i,j,linha;
    
    for (i = IDX; i < n +IDX; i++) {
        w[i] = 0.0;
        linha = IDX;
        while(A[i][linha]!= NULL){
            j = A[i][linha]->j;
            w[i] += A[i][linha]->ele * v[j];
            linha++;
        }

    }   
}

void mat_fatora (int n, Matriz *** A, Matriz *** L, Matriz *** U, Matriz *** D)
{
    int i,colunaA, jA;
    //D = mat_cria(n,n);
    //L = mat_cria(n,n);
    //U = mat_cria(n,n);

    for (i=IDX;i<n+IDX;i++)
    {
        for(colunaA=IDX;A[i][colunaA] !=NULL; colunaA++){

            jA =  A[i][colunaA]->j;

            if(jA < i){
                add(L,i,jA, A[i][colunaA]->ele);

            }else if(jA == i){
                add(D,i,jA, A[i][colunaA]->ele);

            }else{
                add(U,i,jA, A[i][colunaA]->ele);
            }
        }
    }
}



void mat_libera(int n, Matriz*** A) //
{
    int linha =IDX, size_linha;
    
    if(n >100){
        size_linha = 100;
    }else{
        size_linha =n;
    }

    n = n+IDX;

    while(n-- > IDX){
        linha=IDX;
        while((linha<size_linha)&&(A[n][linha]!= NULL)){
            free(A[n][linha]);
            linha++;
        }
        //free(A[n]);
    }
    free(A);
}


void mat_multm(int n, Matriz *** A, Matriz*** B, Matriz*** C) {
    int i,jA,k;
    int colunaA, colunaB;
    double temp;


    //Itera por linha de C (como é linha de A)
    for (i = IDX; i < n+IDX; i++) {
    
        //Itera por coluna de C ( como é coluna de B)
        for(k = IDX;k < n+IDX;k++){ //A[i][colunaA] != NULL && A[i][colunaA] != NULL
            
            temp = 0;
            colunaA =IDX;


            //todas as colunas de A 
            while(A[i][colunaA] != NULL){
                
                jA =  A[i][colunaA]->j;
                colunaB = IDX;
                // Acha a coluna de B que é compativel com elemento C[i][k]
                while((B[jA][colunaB] != NULL) && (B[jA][colunaB]->j < k))
                    colunaB++;

                if((B[jA][colunaB] != NULL) && (B[jA][colunaB]->j == k)){
                    temp += A[i][colunaA]->ele * B[jA][colunaB]->ele;
                }

                colunaA++;
            }

            //colunaA++;
            if(temp != 0){
                add(C,i,k,temp);
             }
        }
    }
         
}

void mat_inv(int n, Matriz*** D,Matriz*** Dinv){

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
    
    
    if(w == -1){ //Jacobi
        mat_fatora(n,A,L,U,D);          
        
        for (i=IDX;i<n+IDX;i++)
        {
            D[i][1]->ele = 1.0/D[i][1]->ele;
           
        }
        return D;
        
        //return M;
    }
        
    //SSOR e GAUSS SEIDEL
    else 
    {
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
        // puts("\nPRINT DA DwL\n");
        // printComZeros(DwL,n);
        // puts("\nPRINT DA DwU\n");
        // printComZeros(DwU,n);
        // puts("\nPRINT DA Dinv\n");
        // printComZeros(D,n);
        
                             
                  
        //D-1(D+wU)     
        mat_multm(n, DwL, D, Mt);
        
        // puts("\nPRINT DA Mt\n");
        // printComZeros(Mt,n);
        ////(D+wL)[D-1(D+wU)]
        mat_multm(n,Mt, DwU, M);


        }
               
               
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
	int n =10000, i;
    Matriz*** A = mat_esparsa(n);
  //  printf("++%d\n",__LINE__ );
   // puts("\nPRINT DA A\n");
    //printComZeros(A,n);
 //    Matriz*** L = mat_cria(n,n);
 //    Matriz*** D = mat_cria(n,n);
 //    Matriz*** U = mat_cria(n,n);

 //    puts("PRINT DA A\n");
	// printComZeros(A,n);
 //    mat_fatora(n, A, L, U, D);
 //    puts("PRINT DA L\n");
	// printComZeros(L,n);

	// puts("PRINT DA D\n");
	// printComZeros(D,n);

	// puts("PRINT DA U\n");
	// printComZeros(U,n);

    x = (double*) calloc(n+IDX,sizeof(double));
    b = (double*) calloc(n+IDX,sizeof(double));
    bbarra = (double*) calloc(n+IDX,sizeof(double));
   // printf("++%d\n",__LINE__ );
    
    for(int i =IDX; i< n+IDX; i++)
        x[i]=1;
    
	//printV(n, x,"x");

  //  printf("++%d\n",__LINE__ );

    mat_multv(n,A,x,b); //Calcula o b correto

	//printV(n, b,"b");
   // printf("++%d\n",__LINE__ );

    for(int i =IDX; i< n+IDX; i++) // Ajusta para a solução inicial
        x[i]=0;
    
	//////////////////////////

    Matriz*** M = pre_cond(A,n,1.8);
    //printf("++%d\n",__LINE__ );

    //puts("\nPRINT DA M\n");
	//printComZeros(M,n);

    //Matriz*** N = mat_cria(n,n);

   // mat_multm(n,M,A,N);

    //mat_multv(n, M, b, bbarra);
    //printV(n, bbarra,"bbarra");

    ////////PRECONDICONADOR em A e b
    i = ConjugateGradientPC(n, A,M, b, x,7);
   // printf("++%d\n",__LINE__ );
    
    printf("\n+++i = %d ++++\n",i );
	//printV(n, x,"Xbarra");
    //printf("++%d\n",__LINE__ );
    mat_libera(n,A);
    mat_libera(n,M);
    free(x);
    free(b);
    free(bbarra);

    getchar();
    return 0;





	// Matriz ***A, ***B, ***C;
	// int n = 3;
	// A = mat_esparsa(n);
	// //B = mat_esparsa(n);
	// B = mat_simples(n);
	// C = mat_cria(n,n);
	// puts("PRINT DA A\n");
	// printComZeros(A,n);

	// puts("\nPRINT DA B\n");
	// printComZeros(B,n);

	// //getchar();
	// mat_multm(n,A,B,C);
	// mat_sumM(n,A,B,C);
	// //getchar();

	// puts("\nPRINT DA C\n");
	// printComZeros(C,n);
	// puts("");

	// //double *b = mat_vet_simples(n);
	// //double *c = calloc(n,sizeof(double));

	// //printV(n, b,"b");

	// //mat_multv(n,A,b,c);

	// //printV(n, c,"c");



}