#La siguiente no es necesariamente requerida, se agrega para mostrar como funciona
#
#.SUFFIXES: .o .c
#.c.o:
#	$(CC) -c $(FLAGS) $<
#
#Macros

CC = gcc
CFLAGS = -D_POSIX_C_SOURCE=200112L -std=c99 -O0 -Wall -fsanitize=address
SRC = main.c server.o

#Reglas explicitas

install: main.c server.o
	$(CC) $(CFLAGS) -o main.elf $(SRC) 

debug: main.c server.o
	$(CC) $(CFLAGS) -g -o main.elf $(SRC) 

clean:
	$(RM) main.elf server.o

server.o: server.h server.c

