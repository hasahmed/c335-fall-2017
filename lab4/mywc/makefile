#Hasan Y Ahmed
#Lab2: mywc
CC = gcc
CFLAGS = -std=c99 
LDFLAGS = -g

mywc: mywc.o
	$(CC) $(LDFLAGS) -o mywc mywc.o

clean:
	rm *.o mywc

mywc.o: mywc.c mywc.h
	$(CC) $(CFLAGS) -c mywc.c
