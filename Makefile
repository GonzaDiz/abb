EXEC = abb
CC = gcc
CFLAGS = -g -std=c99 -Wall -Wconversion -Wno-sign-conversion -Werror 

all: 
	$(CC) $(CFLAGS) -o $(EXEC) main.c abb.c pila.c testing.c pruebas_alumno.c

clean: 
		rm $(EXEC) *.o

run: all

	valgrind --leak-check=full --track-origins=yes --show-reachable=yes --error-exitcode=2 ./abb
