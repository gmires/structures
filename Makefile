all: structures

structures: structures.o vector.o vector.h
	gcc -o structures structures.o vector.o

structures.o: structures.c
	gcc -c structures.c

vector.o: vector.c
	gcc -c vector.c

clean:
	rm -f structures *.o