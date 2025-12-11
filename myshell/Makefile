CC = gcc
CFLAGS = -Wall -g

all: myshell

myshell: main.o parser.o executor.o
	$(CC) $(CFLAGS) -o myshell main.o parser.o executor.o

main.o: main.c shell.h
parser.o: parser.c shell.h
executor.o: executor.c shell.h

clean:
	rm -f *.o myshell
