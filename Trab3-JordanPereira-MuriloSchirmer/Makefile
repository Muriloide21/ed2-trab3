all:
	gcc -Wall key.c encrypt.c -o encrypt
	gcc key.c brute.c -lm -o brute -g -O2
	gcc key.c decrypt.c -lm o decrypt -g -O2

enc:
	gcc -Wall key.c encrypt.c -o encrypt

brute:
	gcc key.c brute.c -lm -o brute -g

dec:
	gcc key.c decrypt.c --lm o decrypt -g -O2

clean:
	rm -f *.o a.out encrypt gmon.out prof
