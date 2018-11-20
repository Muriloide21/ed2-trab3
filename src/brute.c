#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include "key.h"
#include "brute.h"

#define MAXPOS (int)((pow(2, N))-1)

bool is_equal (Key a, Key b) {
  for (int i = 0; i < C; i++) {
    if (a.digit[i] != b.digit[i]) {
      return FALSE;
    }
  }
	return TRUE;
}

int main (int argc, char *argv[]) {
  Key cript = init_key ((unsigned char *) argv[1]);
  Key T[N];

  unsigned char initialTest[C] = "aaaaa";
  unsigned char incrementTest[C] = "aaaab";

  // REUSO DE CÓDIGO PARA LER A TABELA
  unsigned char buffer[C+1];
  for (int i = 0; i < N; i++) {
    scanf ("%s", buffer);
    T[i] = init_key (buffer);
  }

	Key actualTest = init_key(initialTest);
	Key increment = init_key(incrementTest);

	int i = 0;
	while(i <= MAXPOS){
		Key sumTest = subset_sum(actualTest, T);
		if(is_equal(cript, sumTest)){
			print_key_char(actualTest);
		}
		actualTest = add(actualTest, increment);
		i++;
	}

	return 0;
}  