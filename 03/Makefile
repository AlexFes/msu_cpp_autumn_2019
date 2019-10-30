CC = g++

all: matrix.cpp
	$(CC) matrix.cpp -o matrix

run: test.cpp
	./test

test: test.cpp
	$(CC) test.cpp matrix.cpp -o test
