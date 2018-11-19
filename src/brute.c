#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "key.h"
#include "brute.h"

// STRUCT PARA TODAS AS POSSÍVEIS SOMAS
struct sums {
  int lines[N]; // REPOSITORIO PARA AS LINHAS SOMADAS
  int lastline; // INDICE A ÚLTIMA POSIÇÃO DE LINES
  Key sum; // KEY COM A SOMA
};

// INICIALIZA UMA POSIÇÃO DO VETOR DE SOMAS
// SENDO ESTA A POSIÇÃO SOLITÁRIA (A LINHA NÃO SOMADA COM OUTRA)
Sums VALUE (Key T[N], int i) {
  Sums x;
  x.sum = T[i];
  x.lines[0] = i;
  x.lastline = 0;
  return x;
}

// FAZ A SOMA DE X COM O VALOR NA TABELA T NO ÍNDICE I (QUE É UMA LINHA)
// ACRESCE O VALOR DE LASTLINE E INSERE A LINHA NO REPOSITORIO DE LINHAS SOMADAS
Sums SUM (Sums X, Key T[N], int i) {
  X.sum = add (X.sum , T[i]);
  X.lastline++;
//  printf("Lines: ");
//  for (int k = 0; k < Y.lastline; k++) {
//    printf("%2d  ", Y.lines[k]);
//  }
  X.lines[X.lastline] = i;
//  printf("Line: %2d\n", i);
  return X;
} // RETIRAR O PRINT DEPOIS, ELE SERVE PARA VER AS COMBINAÇÕES DE SOMAS :P RETIRAR TBM EM SUM BRUTE FORCE

// RETORNA A PRIMEIRA LINHA (INDICE DE T)
int FIRSTLINE (Sums sum) {
  return sum.lines[0];
}

// RETORNA A ÚLTIMA LINHA (INDICE DE T)
int LASTLINE (Sums sum) {
  return sum.lines[sum.lastline];
}

// FAZ TODAS AS POSSÍVEIS COMBINAÇÕES DE SOMAS E AS ARMAZENA EM 'sumsVector'
Sums* SUM_BRUTE_FORCE (Key T[N]) {
  // ALOCAÇÃO DO VETOR COM AS SOMAS
  Sums* sumsVector = malloc (MAXPOS * sizeof * sumsVector);

  // INICIALIZAÇÃO DOS VALORES SOLITARIOS (QUE NÃO SÃO SOMADOS)
  for (int i = 0; i < MAXLINE; i++) {
    sumsVector[i] = VALUE (T, i);
    //printf("Lines: %2d\n, i); // TIRA AQ E EM SUMS SE QUISER VER AS COMBINAÇÔES
    //print_key_char(sumsVector[i].sum);
  }

  // INICIALIZAÇÃO DAS VARIÁVEIS AUXILIARES
  int k = 0;
  int pos = MAXLINE;
  int i = 1;

  // LOOP PARA A SOMA
  while (pos < MAXPOS) {
    sumsVector[pos] = SUM (sumsVector[k], T, i);
    pos++;
    i++;
    while (i == MAXLINE) {
      k++; if (k == pos) { break; }
      i = LASTLINE (sumsVector[k]);
      i++;
    }
  }

  return sumsVector;
}

// COMPARA DUAS KEYS, RETORNANDO TRUE SE IGUAIS OU FALSE SE DIFERENTES
bool COMPARE (Key a, Sums b) {
  int breaked = 0;

  for (int i = 0; i < C; i++) {
    if (a.digit[i] != b.sum.digit[i]) {
      breaked = 1;
      break;
    }
  }

  if (breaked) {
    return FALSE;
  } else {
    return TRUE;
  }
}

// TRANSFORMA UM VETOR DA POSIÇÃO I ATÉ A POSIÇÃO J EM UM NÚMERO DECIMAL
int BIN_TO_DEC (int* v, int i, int j) {
  int dec = 0;
  for (int k = j; k >= i; k--) {
    dec += (pow (2, (j-k)) * v[k]);
  }

  return dec;
}

// IMPRIME A POSSÍVEL SENHA
void PRINT (Sums a) {
  int E = B-1; // ESPAÇO DE POSIÇÕES ENTRE BITS A SEREM TRANSFORMADOS EM DECIMAL

  int v[N] = {0}; // VETOR "BINÁRIO" INICIALIZADO TOTALMENTE COM ZEROS
  // FOR PARA CRIAÇÃO DO "NÚMERO BINÁRIO" NO VETOR
  // CASO A LINHA X TENHA SIDO SOMADA, A SUA POSIÇÃO NO VETOR SERÁ UM
  for (int i = 0; i <= a.lastline; i++) {
    v[a.lines[i]] = 1;
  }

  // TRANSFORMAÇÃO DO "NÚMERO BINÁRIO" EM DECIMAL
  Key possible = {{0}};
  for (int i = 0; i < C; i++) {
    int intervalo = (i*E)+i;
    possible.digit[i] = BIN_TO_DEC (v, intervalo, intervalo+E);
  }

  print_key_char (possible);
}

// FAZ A COMPARAÇÃO DE TODAS AS POSSÍVEIS SENHAS E AS IMPRIME
void COMPARE_AND_PRINT (Key crypt, Sums* sumsVector) {
  for (int i = 0; i < MAXPOS; i++) {
    if (COMPARE (crypt, sumsVector[i])) {
      PRINT(sumsVector[i]);
    }
  }
}

int main (int argc, char *argv[]) {
  Key cript = init_key ((unsigned char *) argv[1]);
  Key T[N];

  // REUSO DE CÓDIGO
  unsigned char buffer[C+1];
  for (int i = 0; i < N; i++) {
    scanf ("%s", buffer);
    T[i] = init_key (buffer);
  }

  // FAZ TODAS AS POSSÍVEIS SOMAS
  Sums* sumsVector = SUM_BRUTE_FORCE(T);
  // COMPARA E IMPRIME
  COMPARE_AND_PRINT (cript, sumsVector);

  // LIBERAÇÃO DE MEMÓRIA ALOCADA
  free (sumsVector);

  return 0;
}
