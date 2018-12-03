#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "simbolos2.h"
#include "key.h"

bool IS_EQUAL (Key a, Key b) {
  for (int i = 0; i < C; i++) {
    if (a.digit[i] != b.digit[i]) {
      return FALSE;
    }
  }
	return TRUE;
}

Key sub (Key x, Key y) {
  Key c = {{0}};
  int carry = 0;
  for (int i = C-1; i >= 0; i--) {
    int sub = x.digit[i] - y.digit[i] + carry;
    c.digit[i] = sub % R;
    if (sub < 0) {
      carry = -1;
      c.digit[i] += R;
    } else {
      carry = 0;
    }
  }
  return c;
}

bool NOT_FINALIZED (int vetorIndices[C]) {
  for (int i = 0; i < C; i++) {
    if (vetorIndices[i] != 31) {
      return TRUE;
    }
  }
  return FALSE;
}

int main (int argc, char *argv[]) {
  clock_t start, stop;
  start = clock();


  Key crypted = init_key ((unsigned char *) argv[1]);
  Key T[N];

  // REUSO DE CÓDIGO PARA LER A TABELA
  unsigned char buffer[C+1];
  for (int i = 0; i < N; i++) {
    scanf ("%s", buffer);
    T[i] = init_key (buffer);
  }

  // ALOCA A TABELA DE SIMBOLOS
  Key** symbolTable = malloc (C * sizeof * symbolTable);
  for (int i = 0; i < C; i++) {
    symbolTable[i] = malloc (R * sizeof * symbolTable[i]);
  }

  // CRIA UMA STRING E KEY SÓ DE A'S
  unsigned char ACS[C];
  for (int i = 0; i < C; i++) {
    ACS[i] = ALPHABET[0];
  }
  Key ACK = init_key(ACS);

  // COLOCA A KEY DE A'S NA TABELA DE SIMBOLOS E INCREMENTOS (B), EM POSIÇÕES APROPRIADAS
  for (int i = 0; i < C; i++) {
    symbolTable[i][0] = ACK;
    unsigned char ICS[C];
    for (int j = 0; j < C; j++) {
      ICS[j] = ALPHABET[0];
    }
    ICS[i] = ALPHABET[1];
    Key ICK = init_key(ICS);
    symbolTable[i][1] = ICK;
  }

  // PREENCHE A TABELA
  for (int i = 0; i < C; i++) {
    for (int j = 2; j < R; j++) {
      symbolTable[i][j] = add(symbolTable[i][1], symbolTable[i][j-1]);
    }
  }

  // FAZ A ENCRIPTAÇÃO DA TABELA
  for (int i = 0; i < C; i++) {
    for (int j = 0; j < R; j++) {
      Key actual = subset_sum(symbolTable[i][j], T);
      symbolTable[i][j] = actual;
    }
  }

  int vetorIndices[C] = {0};
  Key testCrypted = {{0}};

  // FUNCIONAL
  int u = C-1;
  int FINALIZED = 0;
  while (FINALIZED == 0) {
    Key testCrypted = {{0}};
    for (int j = 0; j < C; j++) {
      testCrypted = add (testCrypted, symbolTable[j][vetorIndices[j]]);
    }
    if (IS_EQUAL(crypted, testCrypted)) {
      for (int k = 0; k < C; k++) {
        printf("%c", ALPHABET[vetorIndices[k]]);
      }
      printf("\n");
    }
    vetorIndices[u]++;
    while (vetorIndices[u] == 32) {
      // testCrypted = sub (testCrypted, symbolTable[u][31]);
      // testCrypted = add (testCrypted, symbolTable[u][0]);
      vetorIndices[u] = 0;
      u--;
      vetorIndices[u]++;
    }
    if (!NOT_FINALIZED (vetorIndices)) {
      FINALIZED = 1;
    }
    u = C-1;
  }

/*
  int u = C-1;
  for (int i = 0; i < C; i++) {
    testCrypted = add (testCrypted, symbolTable[i][vetorIndices[i]]);
  }
  int FINALIZED = 0;
  while (FINALIZED == 0) {
    testCrypted = add (testCrypted, symbolTable[u][vetorIndices[u]]);

    if (IS_EQUAL(crypted, testCrypted)) {
      for (int k = 0; k < C; k++) {
        printf("%c", ALPHABET[vetorIndices[k]]);
      }
      printf("\n");
    }

    testCrypted = sub (testCrypted, symbolTable[u][vetorIndices[u]]);
    vetorIndices[u]++;
    while (vetorIndices[u] == 32) {
      vetorIndices[u] = 0;
      u--;
      testCrypted = sub (testCrypted, symbolTable[u][vetorIndices[u]]);
      vetorIndices[u]++;
      if (vetorIndices[u] != 32) {
        testCrypted = add (testCrypted, symbolTable[u][vetorIndices[u]]);
      }
    }
    if (!NOT_FINALIZED (vetorIndices)) {
      FINALIZED = 1;
    }
    u = C-1;
  }
*/
  for (int i = 0; i < C; i++) {
    free (symbolTable[i]);
  }
  free (symbolTable);



  stop = clock();
  double time_taken = ((double) stop - start) / CLOCKS_PER_SEC;
  printf("\nElapsed time: %.3f\n", time_taken);

  return 0;
}
