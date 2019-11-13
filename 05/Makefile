CC = g++

all: serializer.cpp test.cpp
	$(CC) serializer.cpp -o serializer

test: test.cpp matrix.cpp
	$(CC) test.cpp matrix.cpp -o test

run: serializer.cpp
	./serializer
