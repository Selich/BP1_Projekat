main: main.c file.c util.c
	gcc -o main main.c file.c util.c -lm && ./main

clean:
	rm -f main main.o file.o util.o


