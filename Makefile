all: structures

structures: structures.o vector.o vector.h
	gcc -o structures structures.o vector.o -Wno-implicit-int -Wno-incompatible-pointer-types 

structures.o: structures.c
	gcc -c structures.c -Wno-implicit-int -Wno-incompatible-pointer-types 

vector.o: vector.c
	gcc -c vector.c -Wno-implicit-int -Wno-incompatible-pointer-types 

clean:
	rm -f structures *.o
