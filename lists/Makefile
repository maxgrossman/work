CC = gcc # the gnu compiler baby
CFLAGS = -g -Wall # we'll want debug and warnings

test: test.o vector.o
	$(CC) $(CFLAGS) -o test test.o vector.o -lstdc++
test.o: test.cpp vector.h
	$(CC) $(CFLAGS) -c test.cpp
vector.o: vector.h
