CC = gcc -std=c99
all : rpn

rpn : rpn.o node.o rpnlib.o
	$(CC) -o rpn rpn.o node.o rpnlib.o 

debug : rpn
	gdb -tui rpn

clean : 
	rm -f rpn *.o

rpn.o : rpn.c

rpnlib.o : rpnlib.c rpnlib.h

node.o : node.c node.h
