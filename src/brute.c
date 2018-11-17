#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
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
  X.sum = add (X.sum , T[i]);
  X.lastline++;
  X.lines[X.lastline] = i;
  return X;
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
  //Sums* sumsVector = malloc (MAXPOS * sizeof(Sums*));
  Sums* sumsVector = malloc (MAXPOS * sizeof * sumsVector);

  sumsVector[0] = VALUE (T, 0);
  //print_key_char (sumsVector[0].sum);
  int k = 0;
  int pos = 1;
  int i = 1;
  printf("%d\n", N);
  printf("%d\n", MAXPOS);
  while (pos != MAXPOS) {
  //  printf("%d\n", pos);
    sumsVector[pos] = SUM (sumsVector[k], T, i);
    //print_key_char (sumsVector[pos].sum);
    pos++;
    i++;
    if (i == MAXLINE) {
      k++;
      i = LASTLINE (sumsVector[k]);
      if (i == MAXLINE) {
        sumsVector[pos] = VALUE (T, FIRSTLINE (sumsVector[pos-1]));
        k = pos;
        pos++;
        i  = LASTLINE (sumsVector[k]);
      }
    }
  }

  return sumsVector;
}

// COMPARA DUAS KEYS, RETORNANDO TRUE SE IGUAIS OU FALSE SE DIFERENTES
bool COMPARE (Key a, Sums b) {
  //print_key_char (a); printf(" - "); print_key_char(b.sum);printf("\n");
  for (int i = 0; i < C; i++) {
    if(a.digit[i] != b.sum.digit[i]) {
      return FALSE;
    }
  }
  return TRUE;
}

// TESTA AI ;P
// TENTATIVA DE TRANSFORMAR BINARIO PARA DECIMAL
#include <math.h>
int bin_to_dec(int* v, int i, int j) {
  int dec = 0;
  for (int k = j; k != i; k--) {
    dec += (pow(2, (j-i))*v[k]);
  }
  return dec;
}

// IMPRIME A POSSÍVEL SENHA
void PRINT (Sums a) {
  int v[N] = {0};
  for (int i = 0; i < a.lastline; i++) {
    v[a.lines[i]] = 1;
  }
  Key possible = {{0}};
  for (int i = 0; i < C; i++) {
    possible.digit[i] = bin_to_dec(v, i*4, (i*4)+4);
  }
  /*
  Key possible = {{0}};
  for (int i = 0; i < a.lastline; i++) {
    possible.digit[a.lines[i]] = 1;
  }*/
  print_key(possible);

  print_key_char (possible);
}

// FAZ A COMPARAÇÃO DE TODAS AS POSSÍVEIS SENHAS E AS IMPRIME
void COMPARE_AND_PRINT (Key crypt, Sums* sumsVector) {
  for (int i = 0; i < MAXPOS; i++) {
    if(COMPARE(crypt, sumsVector[i])){
      PRINT(sumsVector[i]);
    }
  }
}

int main (int argc, char *argv[]) {
  Key cript = init_key((unsigned char *) argv[1]);
  Key T[N];
  //reaproveitamento de código
  unsigned char buffer[C+1];
  for (int i = 0; i < N; i++) {
    scanf ("%s", buffer);
    T[i] = init_key(buffer);
  }
  Sums* sumsVector = SUM_BRUTE_FORCE(T);
  COMPARE_AND_PRINT (cript, sumsVector);

  free (sumsVector);

  return 0;
}
