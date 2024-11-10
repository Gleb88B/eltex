calculator:
	gcc -fPIC newsum.c -c
	gcc -fPIC diff.c -c
	gcc -fPIC mult.c -c
	gcc -fPIC divv.c -c
	gcc -shared newsum.o diff.o mult.o divv.o -o libariph.so
	gcc calculator.c -ldl -o calculator