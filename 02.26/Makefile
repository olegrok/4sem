CFLAGS=-c -Wall -g

all: list

list: main.o list.o container.o
	gcc main.o list.o container.o -o list -g -Wextra

main.o: main.c
	gcc -c main.c -Wextra -g
	
list.o: list.c
	gcc -c list.c -Wextra -g

container.o: container.c
	gcc -c container.c -Wextra -g

clean:
	rm -rf *.o list
