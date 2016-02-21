
CFLAGS=-c -Wall

all: sh

sh: main.o shape.o
	gcc main.o shape.o -o sh

main.o: main.c
	gcc -c main.c
	
shape.o: shape.c
	gcc -c shape.c

clean:
	rm -rf *.o sh

