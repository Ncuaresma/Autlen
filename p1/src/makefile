CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
CFLAGS2 = -g
OBJ = *.o

all: ejemplo0 ejemplo1 ejemplo2 ejemplo3 ejemplo4 ejemplo_clase ejemplo_nuevo ejemplo_nuevo2

ejemplo0: ejemplo0.o afnd.o transforma.o estado.o estructura.o
	$(CC) $(CFLAGS) -o ejemplo0 ejemplo0.o afnd.o transforma.o estado.o estructura.o

ejemplo1: ejemplo1.o afnd.o transforma.o estado.o estructura.o
	$(CC) $(CFLAGS) -o ejemplo1 ejemplo1.o afnd.o transforma.o estado.o estructura.o

ejemplo2: ejemplo2.o afnd.o transforma.o estado.o estructura.o
	$(CC) $(CFLAGS) -o ejemplo2 ejemplo2.o afnd.o transforma.o estado.o estructura.o

ejemplo3: ejemplo3.o afnd.o transforma.o estado.o estructura.o
	$(CC) $(CFLAGS) -o ejemplo3 ejemplo3.o afnd.o transforma.o estado.o estructura.o

ejemplo4: ejemplo4.o afnd.o transforma.o estado.o estructura.o
	$(CC) $(CFLAGS) -o ejemplo4 ejemplo4.o afnd.o transforma.o estado.o estructura.o

ejemplo_nuevo: ejemplo_nuevo.o afnd.o transforma.o estado.o estructura.o
	$(CC) $(CFLAGS) -o ejemplo_nuevo ejemplo_nuevo.o afnd.o transforma.o estado.o estructura.o

ejemplo_nuevo2: ejemplo_nuevo2.o afnd.o transforma.o estado.o estructura.o
	$(CC) $(CFLAGS) -o ejemplo_nuevo2 ejemplo_nuevo2.o afnd.o transforma.o estado.o estructura.o

ejemplo_clase: ejemplo_clase.o afnd.o transforma.o estado.o estructura.o
	$(CC) $(CFLAGS) -o ejemplo_clase ejemplo_clase.o afnd.o transforma.o estado.o estructura.o

transforma.o: transforma.c transforma.h
	$(CC) $(CFLAGS) -c transforma.c

estado.o: estado.c estado.h
	$(CC) $(CFLAGS) -c estado.c

estructura.o: estructura.c estructura.h
	$(CC) $(CFLAGS) -c estructura.c

afnd.o: afnd.c afnd.h
	$(CC) $(CFLAGS2) -c afnd.c

clean:
	rm -rf ejemplo0 ejemplo1 ejemplo2 ejemplo3 ejemplo4 ejemplo_clase ejemplo_nuevo ejemplo_nuevo2 $(OBJ) *.dot
