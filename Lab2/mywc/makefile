#Hasan Y Ahmed
#Lab2: mywc
CC = gcc
CFLAGS = -g
LDFLAGS = -g

mywc: mywc.o
	$(CC) $(LDFLAGS) -o mywc mywc.o

clean:
	rm *.o mywc

mywc.o: mywc.c
	$(CC) $(CFLAGS) -c mywc.c
