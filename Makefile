#La siguiente no es necesariamente requerida, se agrega para mostrar como funciona
#
#.SUFFIXES: .o .c
#.c.o:
#	$(CC) -c $(FLAGS) $<
#
#Macros

CC = gcc
flags = -g -D_POSIX_C_SOURCE=200112L -std=c99 -O0 -Wall -fsanitize=address
sources = src/routing.c \
		  src/render.c \
		  src/server.c 
objects = $(sources:.c=.o)
exec = main.elf

#Reglas explicitas

$(exec): $(objects)
	gcc  $(flags) -g -o $@ src/main.c $^

%.o: %.c %.h
	gcc -c $(flags) $< -o $@


clean:
	-rm *.out
	-rm *.o
	-rm *.a
	-rm src/*.a
	-rm src/*.o
