CC = gcc
CFLAGS = -Wall
EXES = unit_test
OBJS = unit_test.o hash_table.o

# make
all: unit_test

# make test
test: unit_test
	./unit_test

unit_test: unit_test.o hash_table.o
	$(CC) -o $@ $^

hash_table.o: hash_table.c hash_table.h
	$(CC) $(CFLAGS) -c $<

unit_test.o: unit_test.c
	$(CC) -c $<

.PHONY: clean

clean:
	$(RM) $(OBJS) $(EXES) a.out
