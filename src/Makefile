#La siguiente no es necesariamente requerida, se agrega para mostrar como funciona
#
#.SUFFIXES: .o .c
#.c.o:
#	$(CC) -c $(FLAGS) $<
#
#Macros

CC = gcc
CFLAGS = -D_POSIX_C_SOURCE=200112L -std=c99 -O0 -Wall -fsanitize=address
SRC = main.c routing.o server.o render.o

#Reglas explicitas

install: server.o routing.o
	$(CC) $(CFLAGS) -o main.elf $(SRC) 

debug:
	$(CC) -c -g routing.h routing.c 
	$(CC) -c -g server.h server.c 
	$(CC) -c -g render.h render.c 
	$(CC) $(CFLAGS) -g -o main.elf $(SRC) 

clean:
	$(RM) main.elf *.o *.h.gch

server.o: server.c routing.o
	$(CC) -c server.h server.c 

routing.o: routing.c
	$(CC) -c routing.h routing.c 

render.o: render.c
	$(CC) -c render.h render.c 
