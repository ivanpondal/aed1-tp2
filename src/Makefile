all: clean tests main

clean:
	rm -f pixel.o main tests

main: pixel.o
	g++ -o main main.cpp pixel.o

pixel.o:
	g++ -c pixel.cpp

tests: pixel.o
	g++ -o tests tests.cpp pixel.o
	./tests
