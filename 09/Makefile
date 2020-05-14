CC = g++
CFLAGS = -std=c++14 -O2
default: run

run: gen sort tests
	./tests

gen: generate_test.cpp
	g++ generate_test.cpp $(CFLAGS) -o gen
	./gen

sort: sort.cpp
	g++ sort.cpp $(CFLAGS) -o sort
	./sort

tests:
	g++ tests.cpp $(CFLAGS) -o tests

clean:
	rm -f gen
	rm -f sort
	rm -f tests
	rm -f test
	rm -f output