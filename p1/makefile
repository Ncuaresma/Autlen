CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
CFLAGS2 = -g
OBJ = *.o

all: main

main: main.o transforma.o afnd.o estado.o estructura.o
	$(CC) $(CFLAGS) -o main main.o transforma.o afnd.o estado.o estructura.o

transforma.o: transforma.c transforma.h
	$(CC) $(CFLAGS) -c transforma.c

estado.o: estado.c estado.h
	$(CC) $(CFLAGS) -c estado.c

estructura.o: estructura.c estructura.h
	$(CC) $(CFLAGS) -c estructura.c

afnd.o: afnd.c afnd.h
	$(CC) $(CFLAGS2) -c afnd.c

clean:
	rm -rf main $(OBJ) *.dot
