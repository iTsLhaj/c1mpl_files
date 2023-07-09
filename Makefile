
CC=@gcc

all:

	$(CC) -c lib.c lib.h
	$(CC) main.c lib.o -o game

main: 

	$(CC) main.c
	./a.out