CC = g++

all: calc.cpp
	$(CC) calc.cpp -o calc

run: calc.cpp
	./calc "5 + 6 + -1"

test: test.py
	python test.py
