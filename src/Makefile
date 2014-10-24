all: clean conv tests reconv main

clean:
	rm -f pixel.o imagen.o main tests

tests: pixel.o imagen.o conv
	g++ -g -o tests tests.cpp pixel.o imagen.o
	./tests

main: pixel.o imagen.o
	g++ -g -o main main.cpp pixel.o imagen.o

pixel.o:
	g++ -g -c pixel.cpp

imagen.o:
	g++ -g -c imagen.cpp

conv:
	cd ../res && make

reconv:
	cd ../res && python2 ../tools/algo1converter.py hermione.nuestroblur.k6.specimg filtered/hermione.nuestroblur.k6.png 1
	cd ../res && python2 ../tools/algo1converter.py hermione.nuestroacuarela.k6.specimg filtered/hermione.nuestroacuarela.k6.png 1
