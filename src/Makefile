all:
	gcc -Wall key.c encrypt.c -o encrypt -O2
	gcc  key.c brute.c -lm -o brute -g -O2
	gcc  key.c simbolos.c -lm -o decrypt -g -O2
	gcc  key.c simbolos2.c -lm -o decrypt2 -g -O2

enc:
	gcc -Wall key.c encrypt.c -o encrypt

brute:
	gcc key.c brute.c -lm -o brute -g

dec: #AINDA NÃO IMPLEMENTADO
	gcc key.c decrypt.c -o descrypt -g

clean:
	rm -f *.o a.out encrypt gmon.out prof
