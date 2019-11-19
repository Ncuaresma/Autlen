CC = gcc
CFLAGS = -g -Wall
OBJ = *.o

all: main

eje: main.o transforma.o afnd.o estado.o estructura.o
	$(CC) $(CFLAGS) -o main main.o transforma.o afnd.o estado.o estructura.o

main.o:

transforma.o: transforma.c transforma.h estado.o estructura.o
	$(CC) $(CFLAGS) -c transforma.c  -o estado.o estructura.o

estado.o: estado.c estado.h
	$(CC) $(CFLAGS) -c estado.c

estructura.o: estructura.c estructura.h estado.o
	$(CC) $(CFLAGS) -c estructura.c -o estado.o

afnd.o: afnd.c afnd.h
	$(CC) $(CFLAGS) -c afnd.c

clean:
	rm -rf main $(OBJ) *.dot
