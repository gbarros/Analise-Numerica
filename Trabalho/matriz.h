#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define IDX 1         //Inicio da indexação da Matriz A


typedef struct Mat{

    int j;
    double ele;
}Matriz ;
 

/////////////////////////////////////////////////////////////////////////////////
//
//    Funcoes internas AUX
//
/////////////////////////////////////////////////////////////////////////////////

/*************************************
 Retorno: Vetor de ponteiros tipo Matriz*** 
 de tamamnho NxM
*************************************/
Matriz*** mat_cria(int m, int n);


/*************************************
 Copia o vetor '(double) s[]' de tamanho 
 '(int) size' para o vetor ' (double) d[]' 
 do mesmo tamanho
*************************************/
void copiaV(int size,double * d,double s[size]);


/*************************************
 Imprimi o conteudo de um vetor '(double) x[],
 de tamanho '(int) size' e o nome 'char* name' 
 atribuido ao vetor 
*************************************/
void printV(int size, double* x,char* name);


/*************************************
 Adiciona o elemento 'double value' na posição
 A[i][j], para 'int i', 'int j', na Matriz*** A 
*************************************/
void add(Matriz*** A, int i, int j, double value);


/*************************************
 Retorna uma 'Matriz*** A', de tamanho  
 'int n', preenchida de acordo com a 
 regra: A(i, i) = i,A(i,i+1) = 0.5 
 A(i+1,i) = 0.5, A(i, i+ 2) = 0.5 
 A(i+ 2, i) = 0.5 extendida para itens
 A(i,2i) = A(2i,i) = 0.5
*************************************/
Matriz*** mat_esparsa_extend(int n);

/*************************************
 Retorno: Matriz***  de tamanho
 'int n' com todos os elementos A[i][j]
 iguais 'i+j'
*************************************/
Matriz *** mat_simples(int n);


/*************************************
 Retorno: Matriz***  de tamanho
 'int n' com todos os elementos iguais
 a '1'
*************************************/
Matriz *** mat_um(int n);


/*************************************
 Imprimi o conteudo de uma matriz 'Matriz ***A',
 de tamanho '(int) n', preenchendo com '0' os
 elementos nulos (elementos originalmente '0' 
 na matriz esparsa) 
*************************************/
void printComZeros(Matriz ***A,int n);


/*************************************
 Imprimi conteudo de uma matriz 'Matriz ***A',
 de tamanho '(int) n'; Apenas os elementos 
 nao nulos são representados
*************************************/
void printSemZeros(Matriz*** A,int n);


/*************************************
 Imprimi o conteudo de uma matriz 'Matriz ***A',
 de tamanho '(int) n', preenchendo com ''(espaços) 
 os elementos cujo ponnteiro é null (elementos 
 nulos na matriz esparsa) 
*************************************/
void printEspacos(Matriz ***A,int n);


/*************************************
 Retorno: Matriz*** identidade de tamanho
 'int n'.
*************************************/
Matriz *** mat_id(int n);




//////////////////////////////////////////////////////////////////////////////////
//
//    Funcoes principais
//
/////////////////////////////////////////////////////////////////////////////////

/*************************************
 Realiza a multiplicação de uma 'Matriz*** A' 
 por um valor escalar 'double escalar', salvando
 o resultado na própria Matriz*** A.
*************************************/
void mat_multescalar(int n, Matriz*** A, double escalar);

/*************************************
 Realiza a multiplicação de dois vetores.
*************************************/

double mat_escalar_vu(int n, double *v, double *u);


/*************************************
 Raliza a soma de uma 'Matriz*** A', de 
 tamanho max 'int n', com uma 'Matriz*** B', 
 tamamnho max 'int n', salvando o resultado 
 na  Matriz*** C, de tamanho max 'int n'
*************************************/
void mat_sumM(int n, Matriz*** A, Matriz*** B, Matriz ***C);


/*************************************
 Retorna uma 'Matriz*** A', de tamanho  
 'int n', preenchida de acordo com a 
 regra: A(i, i) = i,A(i,i+1) = 0.5 
 A(i+1,i) = 0.5, A(i, i+ 2) = 0.5 
 A(i+ 2, i) = 0.5
*************************************/
Matriz*** mat_esparsa(int n);


/*************************************
 Retorna o modulo de um vetor 'double * x'
 de tamanho 'int n'. Usado para avaliação
 da condicao de parada do metodo Gradiente 
 Conujgado
*************************************/
double mat_modulo(int n, double * x);


/*************************************
 Retorna a soma de dois vetores 
 double *A, double *B, de tamanho n, 
 de acordo com a formula: 
 Result[n]= A[n] + mul*B[n]. O resultado
 é alocado em 'double *Result'.
*************************************/
void mat_sumV(int n, double mul, double *A, double *B, double *Result);


/*************************************
 Raliza a multiplicação de uma 'Matriz*** A', de 
 tamanho max 'int n', por um vetor vertical 
 'double* v', tamamnho 'int n', salvando o resultado 
 no vetor  'double* w', de tamanho 'int n'
*************************************/
void mat_multv(int n, Matriz*** A, double* v, double* w);


/*************************************
Preenche a matriz inferior, 'Matriz*** L',
a matriz superior, 'Matriz*** U',  e a matriz 
diagonal, 'Matriz*** D', para uma dada 
'Matriz *** A' de tamanho max 'int n', 
*************************************/
void mat_fatora (int n, Matriz *** A, Matriz *** L, Matriz *** U, Matriz *** D);


/*************************************
 Libera o espaço alocado em uma 'Matriz*** A'
 de tamanho max 'int n'
*************************************/
void mat_libera(int n, Matriz*** A);


/*************************************
 Raliza a multiplicação de uma 'Matriz*** A', de 
 tamanho max 'int n', uma 'Matriz*** B', de 
 tamanho max 'int n',, salvando o resultado 
 uma 'Matriz*** C', de tamanho max 'int n',
*************************************/
void mat_multm(int n, Matriz *** A, Matriz*** B, Matriz*** C);


/*************************************
Preenche a inversa da quadrada'Matriz*** A', 
de tamanho  max 'int n', na Matriz*** Dinv
*************************************/
void mat_inv(int n, Matriz*** D,Matriz*** Dinv);