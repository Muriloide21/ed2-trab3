#ifndef BRUTE_H_
#define BRUTE_H_

#include "key.h"
#include <math.h>

// TYPEDEF PARA STRUCT SUMS
typedef struct sums Sums;

#define FALSE false
#define TRUE true
// NÚMERO MÁXIMO DE POSIÇÕES
#define MAXPOS (int)((pow(2, N))-1)
// NÚMERO MÁXIMO DE LINHAS
#define MAXLINE N

// INICIALIZA UMA POSIÇÃO DO VETOR DE SOMAS.
Sums VALUE (Key T[N], int i);

// FAZ A SOMA DE X COM O VALOR NA TABELA T NO ÍNDICE I, ALÉM DE ACRESCER A LASTLINE E TAMBÉM INSERE A LINHA
Sums SUM (Sums X, Key T[N], int i);

// RETORNA A PRIMEIRA LINHA
int FIRSTLINE (Sums sum);

// RETORNA A ÚLTIMA LINHA
int LASTLINE (Sums sum);

// FAZ TODAS AS POSSÍVEIS COMBINAÇÕES DE SOMAS E AS ARMAZENA EM 'sumsVector'
Sums* SUM_BRUTE_FORCE (Key T[N]);

// COMPARA DUAS KEYS, RETORNANDO TRUE SE IGUAIS OU FALSE SE DIFERENTES
bool COMPARE (Key a, Sums b);

// TRANSFORMA UM VETOR DA POSIÇÃO I ATÉ A POSIÇÃO J EM UM NÚMERO DECIMAL
int bin_to_dec (int* v, int i, int j);

// IMPRIME A POSSÍVEL SENHA
void PRINT (Sums a);

// FAZ A COMPARAÇÃO DE TODAS AS POSSÍVEIS SENHAS E AS IMPRIME
void COMPARE_AND_PRINT (Key crypt, Sums* sumsVector);

#endif
