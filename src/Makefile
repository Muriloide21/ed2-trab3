all:
	gcc -Wall key.c encrypt.c -o encrypt
	gcc key.c brute.c -lm -o brute -g

enc:
	gcc -Wall key.c encrypt.c -o encrypt

brute:
	gcc key.c brute.c -lm -o brute -g

desc: #AINDA NÃO IMPLEMENTADO
	gcc key.c descrypt.c -o descrypt -g

clean:
	rm -f *.o a.out encrypt gmon.out prof
