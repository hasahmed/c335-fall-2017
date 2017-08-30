CC = gcc
CFLAGS = -g
all : rpn

rpn : rpn.o node.o rpnlib.o
	$(CC) $(CFLAGS) -o rpn rpn.o node.o rpnlib.o

debug : rpn
	gdb -tui rpn

clean : 
	rm -f rpn rpn.o node.o

rpn.o : rpn.c

rpnlib.o : rpnlib.c rpnlib.h

node.o : node.c node.h
