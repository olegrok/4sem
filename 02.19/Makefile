CFLAGS=-c -Wall -g

all: list

list: main.o list.o
	gcc main.o list.o -o list -g -Wall

main.o: main.c
	gcc -c main.c -Wall -g
	
list.o: list.c
	gcc -c list.c -Wall -g

clean:
	rm -rf *.o list
