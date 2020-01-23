CC = g++

all: test.cpp sort.cpp sort.h
	$(CC) test.cpp sort.cpp -pthread -std=c++11 -o sort

run: test.cpp sort.cpp sort.h
	./sort
