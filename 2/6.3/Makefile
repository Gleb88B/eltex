calculator:
	gcc -fPIC sum.c -c
	gcc -fPIC diff.c -c
	gcc -fPIC mult.c -c
	gcc -fPIC divv.c -c
	gcc -shared sum.o diff.o mult.o divv.o -o libariph.so
	gcc calculator.c -ldl -o calculator