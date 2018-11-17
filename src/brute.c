#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "key.h"
#include "brute.h"

struct sums {
  int lines[N];
  int lastline;
  Key sum;
};

// INICIALIZA UMA POSIÇÃO DO VETOR DE SOMAS.
Sums VALUE (Key T[N], int i) {
  Sums x;
  x.sum = T[i];
  x.lines[0] = i;
  x.lastline = 0;
  return x;
}

// FAZ A SOMA DE X COM O VALOR NA TABELA T NO ÍNDICE I, ALÉM DE ACRESCER A LASTLINE E TAMBÉM INSERE A LINHA
Sums SUM (Sums X, Key T[N], int i) {
  Sums Y = X;
  Y.sum = add (Y.sum , T[i]);
  Y.lastline++;
//  printf("Lines: ");
//  for (int k = 0; k < Y.lastline; k++) {
//    printf("%2d  ", Y.lines[k]);
//  }
  Y.lines[Y.lastline] = i;
//  printf("Line: %2d\n", i);
  return Y;
}

// RETORNA A PRIMEIRA LINHA
int FIRSTLINE (Sums sum) {
  return sum.lines[0];
}

// RETORNA A ÚLTIMA LINHA
int LASTLINE (Sums sum) {
  return sum.lines[sum.lastline];
}

// FAZ TODAS AS POSSÍVEIS COMBINAÇÕES DE SOMAS E AS ARMAZENA EM 'sumsVector'
Sums* SUM_BRUTE_FORCE (Key T[N]) {
  Sums* sumsVector = malloc (MAXPOS * sizeof * sumsVector);
  for (int i = 0; i < MAXLINE; i++) {
    sumsVector[i] = VALUE (T, i);
    //print_key_char(sumsVector[i].sum);
  }
  int k = 0;
  int pos = MAXLINE;
  int i = 1;
  while (pos < MAXPOS) {
    sumsVector[pos] = SUM (sumsVector[k], T, i);
    pos++;
    i++;
    while (i == MAXLINE) {
      k++;
      i = LASTLINE (sumsVector[k]);
      i++;
    }
  }

  return sumsVector;
}
/* FAIL
Sums* SUM_BRUTE_FORCE (Key T[N]) {
  Sums* sumsVector = malloc (MAXPOS * sizeof * sumsVector);

  sumsVector[0] = VALUE (T, 0);
  int k = 0;
  int pos = 1;
  int i = 1;
  while (pos < MAXPOS) {
    sumsVector[pos] = SUM (sumsVector[k], T, i);
    pos++;
    i++;
    if (i == MAXLINE) {
      k++;
      i = LASTLINE (sumsVector[k]);
      if (i >= MAXLINE) {
        sumsVector[pos] = VALUE (T, FIRSTLINE (sumsVector[pos-1]));
        k = pos;
        pos++;
        i  = LASTLINE (sumsVector[k]);
      }
    }
  }

  return sumsVector;
}
*/

// COMPARA DUAS KEYS, RETORNANDO TRUE SE IGUAIS OU FALSE SE DIFERENTES
bool COMPARE (Key a, Sums b) {
  int breaked = 0;
  for (int i = 0; i < C; i++) {
    if(a.digit[i] != b.sum.digit[i]) {
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
int bin_to_dec (int* v, int i, int j) {
  int dec = 0;
  for (int k = j; k >= i; k--) {
    dec += (pow(2, (j-k))*v[k]);
  }
  return dec;
}

// IMPRIME A POSSÍVEL SENHA
void PRINT (Sums a) {
  int E = B-1; // ESPAÇO DE POSIÇÕES ENTRE BITS A SEREM TRANSFORMADOS EM DECIMAL
  int v[N] = {0};
  for (int i = 0; i <= a.lastline; i++) {
    v[a.lines[i]] = 1;
  }
  Key possible = {{0}};
  for (int i = 0; i < C; i++) {
    int intervalo = (i*E)+i;
    possible.digit[i] = bin_to_dec(v, intervalo, intervalo+E);
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
  //reaproveitamento de código
  unsigned char buffer[C+1];
  for (int i = 0; i < N; i++) {
    scanf ("%s", buffer);
    T[i] = init_key (buffer);
  }
  Sums* sumsVector = SUM_BRUTE_FORCE(T);
  COMPARE_AND_PRINT (cript, sumsVector);

  free (sumsVector);

  return 0;
}
