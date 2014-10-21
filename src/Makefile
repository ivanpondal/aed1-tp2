all: clean tests main

clean:
	rm -f pixel.o imagen.o main tests

tests: pixel.o imagen.o
	g++ -g -o tests tests.cpp pixel.o imagen.o
	./tests

main: pixel.o imagen.o
	g++ -g -o main main.cpp pixel.o imagen.o

pixel.o:
	g++ -g -c pixel.cpp

imagen.o:
	g++ -g -c imagen.cpp
