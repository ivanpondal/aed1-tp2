all: clean tests main

clean:
	rm -f pixel.o imagen.o main tests

pixel.o:
	g++ -c pixel.cpp

imagen.o:
	g++ -c imagen.cpp

main: pixel.o imagen.o
	g++ -o main main.cpp pixel.o imagen.o

tests: pixel.o imagen.o
	g++ -o tests tests.cpp pixel.o imagen.o
	./tests
