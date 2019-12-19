CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
CFLAGS2 = -g
OBJ = *.o

all: ejemplo ejemplo1 ejemplo2 ejemplo3 ejemplo4 ejemplo5

ejemplo: ejemplo.o afnd.o minimiza.o par.o estru.o estado.o
	$(CC) $(CFLAGS) -o ejemplo ejemplo.o afnd.o minimiza.o par.o estru.o estado.o

ejemplo1: ejemplo1.o afnd.o minimiza.o par.o estru.o estado.o
	$(CC) $(CFLAGS) -o ejemplo1 ejemplo1.o afnd.o minimiza.o par.o estru.o estado.o

ejemplo2: ejemplo2.o afnd.o minimiza.o par.o estru.o estado.o
	$(CC) $(CFLAGS) -o ejemplo2 ejemplo2.o afnd.o minimiza.o par.o estru.o estado.o

ejemplo3: ejemplo3.o afnd.o minimiza.o par.o estru.o estado.o
	$(CC) $(CFLAGS) -o ejemplo3 ejemplo3.o afnd.o minimiza.o par.o estru.o estado.o

ejemplo4: ejemplo4.o afnd.o minimiza.o par.o estru.o estado.o
	$(CC) $(CFLAGS) -o ejemplo4 ejemplo4.o afnd.o minimiza.o par.o estru.o estado.o

ejemplo5: ejemplo5.o afnd.o minimiza.o par.o estru.o estado.o
	$(CC) $(CFLAGS) -o ejemplo5 ejemplo5.o afnd.o minimiza.o par.o estru.o estado.o

minimiza.o: minimiza.c minimiza.h
	$(CC) $(CFLAGS) -c minimiza.c

estado.o: estado.c estado.h
	$(CC) $(CFLAGS) -c estado.c

afnd.o: afnd.c afnd.h
	$(CC) $(CFLAGS2) -c afnd.c

par.o: par.c par.h
	$(CC) $(CFLAGS) -c par.c

estru.o: estru.c estru.h
	$(CC) $(CFLAGS) -c estru.c


clean:
	rm -rf ejemplo ejemplo1 ejemplo2 ejemplo3 ejemplo4 ejemplo5 $(OBJ) *.dot
