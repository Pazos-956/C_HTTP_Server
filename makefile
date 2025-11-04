#La siguiente no es necesariamente requerida, se agrega para mostrar como funciona
#
#.SUFFIXES: .o .c
#.c.o:
#	$(CC) -c $(FLAGS) $<
#
#Macros

CC = clang
CFLAGS = -std=c99 -O2 -Wall
SRC = main.c

#Reglas explicitas

all:
	$(CC) $(CFLAGS) -o main.elf # $(OBJ) */

clean:
	$(RM) main.elf
