CC = g++

all: bigint.h main.cpp bigint.cpp
	$(CC) main.cpp bigint.cpp -o bigint

test: bigint.h test.cpp bigint.cpp
	$(CC) test.cpp bigint.cpp -o test

run: bigint.h main.cpp bigint.cpp
	./bigint

runtest: bigint.h test.cpp bigint.cpp
	./test
