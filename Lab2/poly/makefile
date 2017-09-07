#Hasan Y Ahmed && Mitchel Thomas
#Lab2: mywc
CC = gcc
CFLAGS = -std=c99
poly: poly.o dump.o
	$(CC) $(CFLAGS) -o poly poly.o dump.o
debug:
	$(CC) $(CFLAGS) -g poly.c dump.c -o poly
clean:
	rm *.o poly

poly.o : poly.c
dump.o : dump.c
