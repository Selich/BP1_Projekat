main: main.o
	gcc main.o -o main

main.o: main.c
	gcc main.c file.c constraints.c baket.c options.c util.c -o main.o 

clean:
	rm -f main.o main