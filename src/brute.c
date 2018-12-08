#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include "key.h"
#include "brute.h"

#define MAXPOS (int)((pow(2, N))-1)

bool IS_EQUAL (Key a, Key b) {
  for (int i = 0; i < C; i++) {
    if (a.digit[i] != b.digit[i]) {
      return FALSE;
    }
  }
	return TRUE;
}



int main (int argc, char *argv[]) {
  clock_t start, stop;
  start = clock();


  Key cript = init_key ((unsigned char *) argv[1]);
  Key T[N];

  // REUSO DE CÓDIGO PARA LER A TABELA
  unsigned char buffer[C+1];
  for (int i = 0; i < N; i++) {
    scanf ("%s", buffer);
    T[i] = init_key (buffer);
  }

  // GERA AS STRINGS PARA TESTE INICIAL (TUDO 'A') E A STRING PARA INCREMENTO (TUDO 'A', EXCETO A ÚLTIMA QUE É 'B')
  unsigned char initialTest[C];
  unsigned char incrementTest[C];
  for (int i = 0; i < C; i++) {
    initialTest[i] = incrementTest[i] = ALPHABET[0];
  }
  incrementTest[C-1] = ALPHABET[1];

	Key actualTest = init_key(initialTest);
	Key increment = init_key(incrementTest);

  // FAZ COMPARAÇÕES DA ENTRADA COM A ENCRIPTAÇÃO DE TODAS AS CHAVES POSSÍVEIS DE C CARACTERES
	int i = 0;
	while (i <= MAXPOS) {
		Key sumTest = subset_sum(actualTest, T);
		if (IS_EQUAL(cript, sumTest)) {
			print_key_char(actualTest);
		}
		actualTest = add(actualTest, increment);
		i++;
	}



  stop = clock();
  double time_taken = ((double) stop - start) / CLOCKS_PER_SEC;
  printf("\nElapsed time: %.3f\n", time_taken);

	return 0;
}
