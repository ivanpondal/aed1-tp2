all: clean conv tests main

clean:
	rm -f pixel.o imagen.o galeria_imagenes.o main tests

tests: pixel.o imagen.o galeria_imagenes.o conv
	g++ -g -o tests tests.cpp pixel.o imagen.o galeria_imagenes.o
	./tests

main: pixel.o imagen.o galeria_imagenes.o
	g++ -g -o main main.cpp pixel.o imagen.o galeria_imagenes.o

pixel.o:
	g++ -g -c pixel.cpp

imagen.o:
	g++ -g -c imagen.cpp

galeria_imagenes.o:
	g++ -g -c galeria_imagenes.cpp

conv:
	cd ../res && make
