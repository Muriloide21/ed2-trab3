#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "simbolos.h"
#include "key.h"

#define MAXPOSTABELA (int)((pow(2, N/2)))

bool IS_EQUAL (Key a, Key b) {
  for (int i = 0; i < C; i++) {
    if (a.digit[i] != b.digit[i]) {
      return FALSE;
    }
  }
	return TRUE;
}

struct simbolo {
    Key key; // KEY UTILIZADA
    Key soma; // SOMA REPRESENTADA PELA KEY
};

typedef struct simbolo Simbolo;

int main (int argc, char *argv[]) {
    Key cript = init_key ((unsigned char *) argv[1]);
    Key T[N];

    // REUSO DE CÓDIGO PARA LER A TABELA
    unsigned char buffer[C+1];
    for (int i = 0; i < N; i++) {
        scanf ("%s", buffer);
        T[i] = init_key (buffer);
    }

    int metBitsSenha = C/2;

    Simbolo* tabelinha = malloc(MAXPOSTABELA*sizeof(Simbolo));

    unsigned char initial[C];
    unsigned char incrementString[C];
    for (int i = 0; i < C; i++) {
      initial[i] = incrementString[i] = ALPHABET[0];
    }
    incrementString[metBitsSenha-1] = ALPHABET[1];


    // CALCULA TODAS AS POSSÍVEIS SOMAS PARA TODAS AS POSSÍVEIS STRINGS
    // NA PRIMEIRA METADE STRING
    Key actual = init_key(initial);
    Key increment = init_key(incrementString);
    for (int i = 0; i < MAXPOSTABELA; i++) {
        tabelinha[i].key = actual;
        tabelinha[i].soma = subset_sum(actual, T);
        actual = add(actual, increment);
    }

    unsigned char secActualString[C];
    unsigned char secIncrementString[C];
    for (int i = 0; i < C; i++) {
      secActualString[i] = secIncrementString[i] = ALPHABET[0];
    }
    incrementString[C-1] = ALPHABET[1];

    //FAZ A SOMA DAS SOMAS JÁ REALIZADAS COM AS SOMAS DA SEGUNDA METADE DAS STRINGS
    for (int i = 0; i < MAXPOSTABELA; i++) {
        Key secActual = init_key(secActualString);
        Key secIncrement = init_key(secIncrementString);

        Key ActualCrypted;
        Key testCrypted;
        for (int j = 0; j < MAXPOSTABELA; j++) {
          ActualCrypted = subset_sum (secActual, T);
          testCrypted = add (tabelinha[i].soma, ActualCrypted);
          //ActualCrypted = add (tabelinha[i].key, secActual);
          //testCrypted = subset_sum (ActualCrypted, T);
          if (IS_EQUAL(cript, testCrypted)) {
            print_key_char(ActualCrypted);
          }
          secActual = add (secActual, secIncrement);
        }
    }

    return 0;
}
