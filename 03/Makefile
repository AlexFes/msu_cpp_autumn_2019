CC = g++

all: matrix.cpp
	$(CC) matrix.cpp -o matrix

test: test.cpp matrix.cpp
	$(CC) test.cpp matrix.cpp -o test

run: test.cpp
	./test
