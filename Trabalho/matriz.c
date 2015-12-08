#include "matriz.h"

///////////////////////////////
//
//    Funcoes Axiliares
//
///////////////////////////////


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


void printComZeros(Matriz ***A,int n){ 
    
    int i,j, colunaA,jA;

    for (i = IDX; i < n +IDX; i++){

        colunaA = IDX;
        jA=IDX;

        for(j =IDX; j<n+IDX; j++){
            
            if(A[i][colunaA]!= NULL)
                jA = A[i][colunaA]->j;
            
            if(jA == j){
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

Matriz *** mat_simples(int n){ 

    Matriz*** mat = mat_cria(n, n);

    for (int i = IDX; i < n+IDX; 
    i++){
        for (int j = IDX; j < n+IDX; j++){
            add(mat,i,j,i+j);
        }
    }
    return mat;
}

Matriz *** mat_id(int n){

    Matriz*** mat = mat_cria(n, n);

    for (int i = IDX; i < n + IDX; ++i){
        add(mat,i,i,1.0);
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

Matriz*** mat_esparsa(int n){ 

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

Matriz*** mat_esparsa_extend(int n){ 

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
        if(i<(n/2)) add(mat,i,2*i,0.5);
        add(mat,i+1,i,0.5);
        add(mat,i+2,i,0.5);
        if(i<(n/2)) add(mat,2*i,i,0.5);
        
    }
    add(mat,i,i,i);
    add(mat,i,i+1,0.5);
    add(mat,i+1,i,0.5);
    add(mat,i+1,i+1,i+1);
    
    return mat;
    
}
////////////////////////////////
//
//    Funcoes principais
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

double mat_escalar_vu(int n, double *v, double *u){ //
    double sum = 0;
    n = n +IDX;
    while(n--){
        sum += v[n]*u[n];
    }
    return sum;
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

// Usado para calcular o modulo do residuo, condicao de parada
double mat_modulo(int n, double * x){ //
    double sum =0; 
    for (int i = IDX; i < n + IDX; ++i){
        sum += x[i];
    }
    return fabs(sum);
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
