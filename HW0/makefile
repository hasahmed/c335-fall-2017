CC = gcc -std=c99

all : rpn

grind : rpn
	valgrind --tool=memcheck --leak-check=full --track-origins=yes ./rpn

rpn : rpn.o node.o rpnlib.o
	$(CC) -o rpn rpn.o node.o rpnlib.o 

debug : rpn
	gdb -tui rpn

clean : 
	rm -f rpn *.o

rpn.o : rpn.c
	$(CC) -g -c rpn.c -o rpn.o

rpnlib.o : rpnlib.c rpnlib.h
	$(CC) -g -c rpnlib.c -o rpnlib.o

node.o : node.c node.h
	$(CC) -g -c node.c -o node.o
