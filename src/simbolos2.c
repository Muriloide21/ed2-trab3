#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "key.h"

int main (int argc, char *argv[]) {
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
      unsigned char ICS;
      for (int j = 0; j < C; i++) {
        ICS[j] = ALPHABET[0];
      }
      ICS[i] = ALPHABET[1];
      Key ICK = init_key(ICS);
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
    Key testCrypted;
    symbolTable [i][j]
    for (int i = 0; i < (int)pow(32,C); i++) {
      while (vetorIndices[u] == 31) {
        testCrypted = SUB (testCrypted, symbolTable[u][31]);
        u--;
      }
      u = C;
    }


    return 0;
}
