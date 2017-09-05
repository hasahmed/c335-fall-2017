CC = gcc
CFLAGS = -I/Users/hasankatie/CUnit/include -L/Users/hasankatie/CUnit/lib
all : basicTests

basicTests : CUnit_Basic_Tests.o
	$(CC) $(CFLAGS) -o basicTests CUnit_Basic_Tests.o -lcunit

clean : 
	rm -f basicTests *.o

CUnit_Basic_Tests.o : CUnit_Basic_Tests.c
