CC = gcc
CFLAGS = -g -Wall -ansi -pedantic
CFLAGS2 = -g
OBJ = *.o

all: ejemplo0 ejemplo1 ejemplo2 ejemplo3 ejemplo4

ejemplo0: ejemplo0.o afnd.o
	$(CC) $(CFLAGS) -o ejemplo0 ejemplo0.o afnd.o

ejemplo1: ejemplo1.o afnd.o
	$(CC) $(CFLAGS) -o ejemplo1 ejemplo1.o afnd.o

ejemplo2: ejemplo2.o afnd.o
	$(CC) $(CFLAGS) -o ejemplo2 ejemplo2.o afnd.o

ejemplo3: ejemplo3.o afnd.o
	$(CC) $(CFLAGS) -o ejemplo3 ejemplo3.o afnd.o

ejemplo4: ejemplo4.o afnd.o
				$(CC) $(CFLAGS) -o ejemplo4 ejemplo4.o afnd.o

afnd.o: afnd.c afnd.h
	$(CC) $(CFLAGS2) -c afnd.c

clean:
	rm -rf ejemplo0 ejemplo1 ejemplo2 ejemplo3 ejemplo4 $(OBJ) *.dot
