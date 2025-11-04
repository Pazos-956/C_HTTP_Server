#La siguiente no es necesariamente requerida, se agrega para mostrar como funciona
#
#.SUFFIXES: .o .c
#.c.o:
#	$(CC) -c $(FLAGS) $<
#
#Macros

CC = clang
CFLAGS = -std=c99 -O2 -Wall -fsanitize=address
SRC = main.c

#Reglas explicitas

install: 
	$(CC) $(CFLAGS) -o main.elf $(SRC) 

clean:
	$(RM) main.elf
