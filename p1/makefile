CC = gcc
CFLAGS = -g
OBJ = *.o

all: main

main: main.o transforma.o afnd.o
	$(CC) $(CFLAGS) -o main main.o transforma.o afnd.o

transforma.o: transforma.c transforma.h estado.o estructura.o
	$(CC) $(CFLAGS) -c transforma.c  -o estado.o estructura.o

estado.o: estado.c estado.h estructura.o
	$(CC) $(CFLAGS) -c estado.c -o estado.o

estructura.o: estructura.c estructura.h
	$(CC) $(CFLAGS) -c estructura.c

afnd.o: afnd.c afnd.h
	$(CC) $(CFLAGS) -c afnd.c

clean:
	rm -rf main $(OBJ) *.dot
